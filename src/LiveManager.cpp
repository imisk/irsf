
#include "LiveManager.h"
#include <sstream>
#include "qdatetime.h"

using namespace irsf;

SoundMixer LiveManager::soundMixer;

LiveManager::LiveManager(TrackDataManager* tdm,
                         FormulaDbManager* fdm,
                         SignalDbManager* sdm,
                         AppDbManager* adm)
    : trackDataManager(tdm),
      formulaDbManager(fdm),
      signalDbManager(sdm),
      appDbManager(adm),
      signalLivePlayer(std::make_unique<SignalLivePlayer>(trackDataManager,
                                                          formulaDbManager,
                                                          signalDbManager)) {}

void LiveManager::SetCurrentSignalSet(IrsfSignalSet* set) noexcept {
  signalSet = set;
}

void LiveManager::SetRecordingTelemetry(bool isRecording) noexcept {
  isRecordingTelemetry = isRecording;
}

void LiveManager::SetBrakeMarkerUsage(bool d, std::string bmName) noexcept {
  BrakeMarkersActive = d;
  BrakeMarkerSetName = bmName;
}

void LiveManager::RequestStop() {
  std::scoped_lock<std::mutex> lock(stopReq);

  stopRequested = true;
}

void LiveManager::InitializeAll() {
  variablesMonitored = GetVariableIdListForSignalSet(*signalSet);

  soundMixer.Initialize(
      static_cast<size_t>(appDbManager->GetAppConfig()->FrameCount),
      static_cast<size_t>(appDbManager->GetAppConfig()->ChannelCount));

  irsdkManager = std::make_unique<IrsdkManager>();

  if (!irsdkManager->Startup()) {
    throw IrsfException(IrsfError::IrsdkFailedToStart);
  } else {
    std::cout << "Connection to iRacing successful. \n";
  }

  // Initialize the inputVariables vectors
  std::vector<VariableId> varsVec;

  std::copy(variablesMonitored.begin(), variablesMonitored.end(),
            std::back_inserter(varsVec));

  irsdkManager->InitVariables(varsVec, inputVariables, inputVariablesNonFloat);

  void* retVal;
  irsdk_VarType retType;

  //... initialize signals - activeSignals

  // irsdk forces us to use reinterpret_cast and void* stuff... :(

  // Lap distance
  irsdkManager->GetIrsdkValuePointer("LapDist", retType, retVal);
  lapDistanceLive = reinterpret_cast<float*>(retVal);

  if (lapDistanceLive == nullptr)
    throw IrsfException(IrsfError::MissingInputVariable);

  // Lap
  irsdkManager->GetIrsdkValuePointer("Lap", retType, retVal);
  curLapLive = reinterpret_cast<int32_t*>(retVal);

  if (curLapLive == nullptr)
    throw IrsfException(IrsfError::MissingInputVariable);

  // OnPitRoad
  irsdkManager->GetIrsdkValuePointer("OnPitRoad", retType, retVal);
  onPitRoadLive = reinterpret_cast<bool*>(retVal);

  if (onPitRoadLive == nullptr)
    throw IrsfException(IrsfError::MissingInputVariable);

  if (isRecordingTelemetry)
    InitializeTelemetryRecording();

  if (BrakeMarkersActive) {
    bmm = std::make_unique<BrakeMarkerManager>();
    bmm->AddChannels(&soundMixer);

    auto bmSet = appDbManager->GetBrakeMarkerSet(BrakeMarkerSetName);

    if (bmSet != nullptr) {
      bmm->Init(lapDistanceLive, *bmSet);
      signalLivePlayer->bmm = bmm.get();

    } else {
      std::cout << "Error : brake marker set not found. \n";
      BrakeMarkersActive = false;
      throw IrsfException(IrsfError::ItemNotFound,
                          "Brake marker set not found");
    }
  }

  signalLivePlayer->BrakeMarkerManagerIsActive = BrakeMarkersActive;

  // SignalLivePlayer
  signalLivePlayer->Initialize(*signalSet, &soundMixer, lapDistanceLive,
                               curLapLive, onPitRoadLive, inputVariables);

  // Portaudio
  portaudioManager->Initialize(appDbManager->GetAppConfig()->ChannelCount,
                               appDbManager->GetAppConfig()->Wav_SampleRate);

  portaudioManager->BeginStream(callback_mixer);
}

void LiveManager::InitializeAudioOnly() {
  soundMixer.Initialize(
      static_cast<size_t>(appDbManager->GetAppConfig()->FrameCount),
      static_cast<size_t>(appDbManager->GetAppConfig()->ChannelCount));

  portaudioManager->Initialize(appDbManager->GetAppConfig()->ChannelCount,
                               appDbManager->GetAppConfig()->Wav_SampleRate);

  portaudioManager->BeginStream(callback_mixer);
}

void LiveManager::PlaySoundSample(float volumeMultiplier) {
  std::string sound1Path = "SOUNDS\\transfer_in.wav";

  auto sfr = std::make_unique<SoundFileReader>();

  playingSample = std::make_unique<SoundChannel>();

  playingSample->snd = std::make_unique<SoundData>();
  sfr->LoadSoundChannelFromFile(sound1Path, playingSample->snd.get(), 1024,
                                1.0f);

  playingSample->multiplier = volumeMultiplier;
  playingSample->offset = 0;

  soundMixer.activeChannels.push_back(playingSample.get());
}

void LiveManager::StopAudioOnly() {
  portaudioManager->EndStream();
  soundMixer.activeChannels.clear();
}

void LiveManager::MainLoop() {
  stopRequested = false;

  std::cout << "================ LiveManager::MainLoop() --- started "
               "============ \n";

  bool finished = false;
  while (!finished) {
    bool waitOk = irsdkManager->WaitForData();

    if (!waitOk) {
      qDebug() << "---- waitOk -------- FAIL -------- ";
    } else {
      if (isRecordingTelemetry)
        telemetryRecorder->Record();
    }

    ConvertFloats();

    //.... update signals logic ...
    signalLivePlayer->OnTickUpdate();

    if (BrakeMarkersActive) {
      bmm->CheckBrakingMarkerSignal();
    }

    {
      std::scoped_lock<std::mutex> lock(stopReq);

      if (stopRequested) {
        qDebug() << "Exiting loop.";
        finished = true;
      }
    }

    //------ debug force stop by pressing A on the keyboard ----
    // if (GetKeyState('A') & 0x8000)
    //        stopReq.lock();
    //        if (stopRequested)
    //        {
    //            qDebug() << "Exiting loop.";
    //           finished = true;
    //        }
    //        stopReq.unlock();
  }

  qDebug() << "-------------------------- MainLoop ------ end ";

  if (isRecordingTelemetry) {
    /*
     * write the remainder of the data to file if we quit the recording
     * all of a sudden
     */
    telemetryRecorder->SendToWriter();

    // end telemetry session
    telemetryDiskWriter->WriteEndOfFile();

    telemetryDiskWriter->CloseFile();
  }

  portaudioManager->EndStream();
}

void LiveManager::MainLoop_Testing() {
  signalLivePlayer->OnTickUpdate();
}

void LiveManager::GetTrackAndConfigName(const int32_t& trackId,
                                        const int32_t& configId,
                                        std::string& retName) noexcept {
  trackDataManager->GetTrackAndConfigName(trackId, configId, retName);
}

std::set<VariableId> LiveManager::GetVariableIdListForSignalSet(
    const IrsfSignalSet& set) {
  std::set<VariableId> retVariables;

  for (const auto& signalName : set.signalNames) {
    IrsfSignal* signal = signalDbManager->GetSignal(signalName);

    auto formula = formulaDbManager->GetFormulaWithName(signal->formulaName);

    for (const auto& operand : formula->operandsInList) {
      retVariables.insert(operand.GetVariableId());
    }
  }

  return retVariables;
}

void LiveManager::ConvertFloats() noexcept {
  for (auto& iv : inputVariablesNonFloat) {
    iv->ConvertToFloat();
  }
}

void LiveManager::InitializeTelemetryRecording() {
  if (irsdkManager == nullptr)
    throw IrsfException(IrsfError::IrsdkNotInitialized);

  if (signalSet == nullptr)
    throw IrsfException(IrsfError::SignalSetEmpty);

  std::string telFileName = "";

  QDateTime now = QDateTime::currentDateTime();

  int32_t dd = now.date().day();
  int32_t mm = now.date().month();
  int32_t yy = now.date().year();

  int32_t hr = now.time().hour();
  int32_t min = now.time().minute();

  std::stringstream ss;

  std::string trackName = "";

  trackDataManager->GetTrackName(signalSet->trackId, trackName);

  size_t si = 0;
  for (si = 0; si < trackName.size(); si++) {
    if (trackName[si] == ' ') {
      trackName[si] = '_';
    }
  }

  ss << trackName << "-" << dd << "-" << mm << "-" << yy << "-" << hr << "-"
     << min << ".itr";

  ss >> telFileName;

  std::cout << "Recording telemetry to file: " << telFileName << std::endl;

  //---------------

  std::vector<VariableId> varList;

  auto& vec = appDbManager->GetAppConfig()->TelemetryRecordingVariables;

  bool lapFound = false;

  for (auto& v : vec) {
    varList.push_back(v);

    if (v == VariableId::Lap)
      lapFound = true;
  }

  if (lapFound == false)
    throw IrsfException(IrsfError::LapDistanceVariableMissing);

  if (telemetryDiskWriter == nullptr)
    telemetryDiskWriter = std::make_unique<TelemetryDiskWriter>();

  if (telemetryRecorder == nullptr) {
    telemetryRecorder = std::make_unique<TelemetryRecorder>(
        telemetryDiskWriter.get(), irsdkManager.get(),
        appDbManager->GetAppConfig()->telemetry_MaxTicksInMemory);
  }

  telemetryRecorder->Init(telFileName, varList);
}

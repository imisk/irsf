#include "AppDbManager.h"
#include "BinaryReadWriteUtils.h"
#include "Utilities.h"

namespace irsf {

constexpr int32_t kCurrentAppDbFileVersion = 0;

AppDbManager::AppDbManager() {}

bool AppDbManager::BrakeMarkerSetExists(std::string& name) {
  for (auto& bs : brakeMarkerSets) {
    if (name == bs.name) {
      return true;
    }
  }

  return false;
}

BrakeMarkerSet* AppDbManager::CreateNewBrakeMarkerSet(std::string& name) {
  BrakeMarkerSet newSet;
  newSet.name = name;
  newSet.TrackConfigId = kIdNotSelected;
  newSet.TrackId = kTrackIdAllTracks;

  brakeMarkerSets.push_back(newSet);

  std::cout << "Set added. count = " << brakeMarkerSets.size() << std::endl;

  SaveDb();

  BrakeMarkerSet* ret = &brakeMarkerSets.back();

  return ret;
}

BrakeMarkerSet* AppDbManager::GetBrakeMarkerSet(std::string& name) {
  BrakeMarkerSet* ret = nullptr;

  auto foundObj =
      std::find(brakeMarkerSets.begin(), brakeMarkerSets.end(), name);

  if (foundObj != brakeMarkerSets.end()) {
    ret = &(*foundObj);
  }

  return ret;
}

std::vector<QString> AppDbManager::GetBrakeMarkerSetNameList() {
  std::vector<QString> ret;

  for (auto& b : brakeMarkerSets) {
    ret.push_back(QString(b.name.c_str()));
  }

  return ret;
}

void AppDbManager::LoadDb() {
  std::string fileName = "App.idb";

  fstream_raii_read reading(fileName);

  loadFile = reading.get();

  if (loadFile->good() != true)
    throw IrsfException(IrsfError::FileNotFound);

  int32_t readFileVersion;
  ReadBinary(loadFile, &readFileVersion);

  size_t setCount;
  ReadBinary(loadFile, &setCount);

  for (size_t si = 0; si < setCount; ++si) {
    BrakeMarkerSet bm;
    LoadBrakeMarkerSet(bm);
    brakeMarkerSets.push_back(bm);
  }

  //---- Load App Config
  LoadAppConfig();

  std::cout << "AppDb loaded. BrakeMarkerSet count = " << brakeMarkerSets.size()
            << std::endl;
}

void AppDbManager::RenameBakToMain() {
  int32_t status = 0;

  std::cout << "Renaming bak to main: App.idb \n";

  status = remove("App.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file App.idb \n";

  status = rename("App_bak.idb", "App.idb");
  if (status != 0)
    std::cout << "Warning : Could not rename file "
                 "App_bak.idb to App.idb \n";
}

void AppDbManager::DeleteBrakeMarkerSet(std::string& name) {
  size_t si = 0;
  bool found = false;
  size_t deleteIndex = 0;

  si = 0;
  bool finished = false;

  while (!finished) {
    if (brakeMarkerSets[si].name == name) {
      found = true;
      deleteIndex = si;
      finished = true;
    }
    ++si;
    if (si == brakeMarkerSets.size())
      finished = true;
  }

  if (found) {
    std::streamsize cIndex = static_cast<std::streamsize>(deleteIndex);
    brakeMarkerSets.erase(brakeMarkerSets.begin() + cIndex);
    std::cout << "Brake marker set " << name << " is deleted. \n";

    SaveDb();
  }
}

void AppDbManager::AddBrakeMarkerToBrakeMarkerSet(std::string& setName,
                                                  BrakeMarker& bm) {
  auto ptr = GetBrakeMarkerSet(setName);

  if (ptr == nullptr) {
    throw IrsfException(IrsfError::ItemNotFound,
                        "Brake marker set not selected");
  }

  ptr->bmList.push_back(bm);

  this->SaveDb();
}

void AppDbManager::DeleteBrakeMarkerFromBrakeMarkerSet(
    std::string& setName,
    std::string& brakeMarkerItemText) {
  auto ptr = GetBrakeMarkerSet(setName);

  if (ptr == nullptr) {
    throw IrsfException(IrsfError::ItemNotFound,
                        "Brake marker set not selected");
  }

  size_t si = 0;
  bool found = false;
  size_t deleteIndex = 0;
  bool finished = false;

  while (!finished) {
    std::string cName = BrakeMarkerToString(ptr->bmList[si]);

    if (cName == brakeMarkerItemText) {
      found = true;
      deleteIndex = si;
      finished = true;
    }

    ++si;
    if (si == ptr->bmList.size())
      finished = true;
  }

  if (found) {
    std::streamsize cIndex = static_cast<std::streamsize>(deleteIndex);
    ptr->bmList.erase(ptr->bmList.begin() + cIndex);
    std::cout << "Brake marker is deleted. \n";

    SaveDb();
  }
}

void AppDbManager::LoadAppConfig() {
  size_t count = 0;
  size_t si = 0;

  ReadBinary(loadFile, &count);
  for (si = 0; si < count; ++si) {
    VariableId v;
    ReadBinary(loadFile, &v);
    appConfig->TelemetryRecordingVariables.push_back(v);
  }

  ReadBinary(loadFile, &appConfig->telemetry_MaxTicksInMemory);
  ReadBinary(loadFile, &appConfig->bm_LoopLength);
  ReadBinary(loadFile, &appConfig->bm_ExpectedLatencyMs);
  ReadBinary(loadFile, &appConfig->bm_DelayBetweenBeeps);
  ReadBinary(loadFile, &appConfig->bm_NextLapMinDistance);
  ReadBinary(loadFile, &appConfig->bm_SoundVolume);

  ReadBinary(loadFile, &count);
  appConfig->Marker_fileName = std::string(count, ' ');
  ReadBinaryCharArray(loadFile, &appConfig->Marker_fileName[0], count);

  ReadBinary(loadFile, &count);
  appConfig->PreMarker_fileName = std::string(count, ' ');
  ReadBinaryCharArray(loadFile, &appConfig->PreMarker_fileName[0], count);

  ReadBinary(loadFile, &appConfig->FrameCount);
  ReadBinary(loadFile, &appConfig->ChannelCount);
  ReadBinary(loadFile, &appConfig->Wav_SampleRate);
}

void AppDbManager::SaveAppConfig() {
  size_t count = appConfig->TelemetryRecordingVariables.size();
  WriteBinary(*saveFile, &count);
  for (auto& v : appConfig->TelemetryRecordingVariables) {
    WriteBinary(*saveFile, &v);
  }

  WriteBinary(*saveFile, &appConfig->telemetry_MaxTicksInMemory);
  WriteBinary(*saveFile, &appConfig->bm_LoopLength);
  WriteBinary(*saveFile, &appConfig->bm_ExpectedLatencyMs);
  WriteBinary(*saveFile, &appConfig->bm_DelayBetweenBeeps);
  WriteBinary(*saveFile, &appConfig->bm_NextLapMinDistance);
  WriteBinary(*saveFile, &appConfig->bm_SoundVolume);

  //
  count = appConfig->Marker_fileName.size();
  WriteBinary(*saveFile, &count);
  WriteBinaryCharArray(*saveFile, appConfig->Marker_fileName.c_str(), count);
  //
  count = appConfig->PreMarker_fileName.size();
  WriteBinary(*saveFile, &count);
  WriteBinaryCharArray(*saveFile, appConfig->PreMarker_fileName.c_str(), count);

  WriteBinary(*saveFile, &appConfig->FrameCount);
  WriteBinary(*saveFile, &appConfig->ChannelCount);
  WriteBinary(*saveFile, &appConfig->Wav_SampleRate);
}

void AppDbManager::ResetTelemetryVariablesToDefault() {
  appConfig->TelemetryRecordingVariables.clear();

  appConfig->TelemetryRecordingVariables.push_back(VariableId::Speed);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::RPM);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::Brake);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::Throttle);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::Yaw);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::YawNorth);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::Pitch);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::Roll);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::VelocityZ);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::VelocityY);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::VelocityX);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::YawRate);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::PitchRate);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::RollRate);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::VertAccel);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::LatAccel);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::LongAccel);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::WindVel);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::WindDir);
  appConfig->TelemetryRecordingVariables.push_back(
      VariableId::SteeringWheelAngle);
  appConfig->TelemetryRecordingVariables.push_back(VariableId::LapDist);

  appConfig->TelemetryRecordingVariables.push_back(VariableId::Lap);
}

void AppDbManager::ResetAppConfigToDefault() {
  ResetTelemetryVariablesToDefault();

  appConfig->bm_LoopLength = 15;
  appConfig->bm_ExpectedLatencyMs = 15;
  appConfig->bm_DelayBetweenBeeps = 400;
  appConfig->bm_NextLapMinDistance = 10;
  appConfig->bm_SoundVolume = 0.7f;

  appConfig->Marker_fileName = "marker.wav";
  appConfig->PreMarker_fileName = "premarker.wav";

  appConfig->FrameCount = 64;
  appConfig->ChannelCount = 2;
  appConfig->Wav_SampleRate = 44100;

  appConfig->telemetry_MaxTicksInMemory = 600;
}

void AppDbManager::AddVariableIdToTelemetryRecording(VariableId varId) {
  if (std::find(appConfig->TelemetryRecordingVariables.begin(),
                appConfig->TelemetryRecordingVariables.end(),
                varId) == appConfig->TelemetryRecordingVariables.end()) {
    appConfig->TelemetryRecordingVariables.push_back(varId);
  } else {
    std::cout << "VariablaId is already added.\n";
    return;
  }

  SaveDb();
}

void AppDbManager::DeleteVariableIdFromTelemetryRecording(VariableId varId) {
  size_t si = 0;
  bool found = false;
  bool finished = false;
  size_t deleteIndex = 0;

  while (!finished) {
    if (appConfig->TelemetryRecordingVariables[si] == varId) {
      found = true;
      deleteIndex = si;
      finished = true;
    }

    ++si;
    if (si == appConfig->TelemetryRecordingVariables.size())
      finished = true;
  }

  if (found) {
    std::streamsize cIndex = static_cast<std::streamsize>(deleteIndex);

    appConfig->TelemetryRecordingVariables.erase(
        appConfig->TelemetryRecordingVariables.begin() + cIndex);

    std::cout << "Variable is deleted from recording list. \n";

    SaveDb();
  }
}

void AppDbManager::SaveDb() {
  int32_t status = 0;

  status = remove("App_bak.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file App_bak.idb \n";

  status = rename("App.idb", "App_bak.idb");
  if (status != 0)
    std::cout << "Warning : Could not rename file "
                 "App.idb to App_bak.idb \n";

  std::string fileName = "App.idb";
  auto f = fstream_raii_write(fileName);
  saveFile = f.get();

  if (saveFile->is_open() == false) {
    std::cout << "error saving App data. ----------------- \n";
    throw IrsfException(IrsfError::CannotOpenFile);
  }

  // file version
  int32_t ver = kCurrentAppDbFileVersion;
  WriteBinary(*saveFile, &ver);

  size_t setCount = brakeMarkerSets.size();
  WriteBinary(*saveFile, &setCount);

  for (auto& b : brakeMarkerSets) {
    SaveBrakeMarkerSet(b);
  }

  SaveAppConfig();

  std::cout << "AppDb updated. \n";
}

AppConfig* AppDbManager::GetAppConfig() {
  return appConfig.get();
}

void AppDbManager::SaveBrakeMarkerSet(BrakeMarkerSet& set) {
  std::cout << "save bms \n";
  size_t nameSize = set.name.size();
  WriteBinary(*saveFile, &nameSize);

  WriteBinaryCharArray(*saveFile, set.name.c_str(), set.name.size());

  WriteBinary(*saveFile, &set.TrackId);

  WriteBinary(*saveFile, &set.TrackConfigId);

  size_t markerCount = set.bmList.size();
  WriteBinary(*saveFile, &markerCount);

  for (auto& bm : set.bmList) {
    WriteBinary(*saveFile, &bm.distancePosition);
    WriteBinary(*saveFile, &bm.speedAtMarker);
  }
}

void AppDbManager::LoadBrakeMarkerSet(BrakeMarkerSet& set) {
  size_t nameSize = 0;
  ReadBinary(loadFile, &nameSize);

  set.name = std::string(nameSize, ' ');
  ReadBinaryCharArray(loadFile, &set.name[0], nameSize);
  std::cout << "set.name = >" << set.name << "<" << std::endl;

  ReadBinary(loadFile, &set.TrackId);

  ReadBinary(loadFile, &set.TrackConfigId);

  size_t markerCount;
  ReadBinary(loadFile, &markerCount);

  for (size_t si = 0; si < markerCount; ++si) {
    BrakeMarker bm;
    ReadBinary(loadFile, &bm.distancePosition);
    ReadBinary(loadFile, &bm.speedAtMarker);
    set.bmList.push_back(bm);
  }
}

}  // namespace irsf

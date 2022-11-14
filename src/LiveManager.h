#ifndef LIVEMANAGER_H
#define LIVEMANAGER_H

#include <memory>
#include <mutex>
#include <set>
#include "AppDbManager.h"
#include "BreakMarkerManager.h"
#include "FormulaDbManager.h"
#include "PortaudioManager.h"
#include "SignalDbManager.h"
#include "SignalLivePlayer.h"
#include "SoundMixer.h"
#include "TelemetryDiskWriter.h"
#include "TelemetryRecorder.h"
#include "TrackDataManager.h"
#include "irsdkmanager.h"

namespace irsf {
// using namespace irsf;
using namespace irsf::irsdk;

/*
Coordinates iRacing SDK, signal player and audio player to produce audio from
signals.

*/

class LiveManager {
 public:
  explicit LiveManager(TrackDataManager* tdm,
                       FormulaDbManager* fdm,
                       SignalDbManager* sdm,
                       AppDbManager* adm);

  /*
   * Mixes all active channels to produce single audio output.
   * This function signature is required by portaudio, cannot be changed.
   */
  static int callback_mixer(const void* input,
                            void* output,
                            unsigned long frameCount,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void* userData1) {
    float* out = nullptr;

    // Variables are unused, but signature is forced by portaudio
    Q_UNUSED(input)
    Q_UNUSED(output)
    Q_UNUSED(frameCount)
    Q_UNUSED(timeInfo)
    Q_UNUSED(statusFlags)
    Q_UNUSED(userData1)

    out = reinterpret_cast<float*>(output);

    soundMixer.PerformMix(out);

    return paContinue;
  }

  void SetCurrentSignalSet(IrsfSignalSet* set) noexcept;

  void SetRecordingTelemetry(bool isRecording) noexcept;

  void SetBrakeMarkerUsage(bool d, std::string bmName = "") noexcept;

  void RequestStop();

  /*
   * Starts portaudio, and begins the stream which will call callback_mixer.
   * Now the callback and soundMixer are being constantly called.
   * Connects to iRacing with IRSDK.
   * Sets lapDistanceLive to track live data.
   *
   * */
  void InitializeAll();

  void InitializeAudioOnly();

  void PlaySoundSample(float volumeMultiplier);

  void StopAudioOnly();

  /*
    Main loop of the application
  */
  void MainLoop();

  void MainLoop_Testing();

  void GetTrackAndConfigName(const int& trackId,
                             const int& configId,
                             std::string& retName) noexcept;

 private:
  std::set<VariableId> GetVariableIdListForSignalSet(const IrsfSignalSet& set);

  void ConvertFloats() noexcept;

  void InitializeTelemetryRecording();

  std::unique_ptr<PortaudioManager> portaudioManager{
      std::make_unique<PortaudioManager>()};

  static SoundMixer soundMixer;

  std::unique_ptr<IrsdkManager> irsdkManager{nullptr};

  TrackDataManager* trackDataManager;

  FormulaDbManager* formulaDbManager;

  SignalDbManager* signalDbManager;

  AppDbManager* appDbManager;

  std::unique_ptr<SignalLivePlayer> signalLivePlayer;

  std::unique_ptr<TelemetryDiskWriter> telemetryDiskWriter{nullptr};

  std::unique_ptr<TelemetryRecorder> telemetryRecorder{nullptr};

  std::unique_ptr<BrakeMarkerManager> bmm;

  IrsfSignalSet* signalSet;

  std::set<VariableId> variablesMonitored;

  // All input variables
  std::vector<iVarInterface_sp> inputVariables;

  // Only the input variables which need to be converted to Float
  std::vector<iVarRawInterface_sp> inputVariablesNonFloat;

  bool isRecordingTelemetry{false};
  bool stopRequested{false};
  std::mutex stopReq;
  bool BrakeMarkersActive{false};
  std::string BrakeMarkerSetName;
  float* lapDistanceLive{nullptr};
  int32_t* curLapLive{nullptr};
  bool* onPitRoadLive{nullptr};

  std::unique_ptr<SoundChannel> playingSample;
};
}  // namespace irsf
#endif  // LIVEMANAGER_H

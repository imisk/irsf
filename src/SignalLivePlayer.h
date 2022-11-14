#ifndef SIGNALLIVEPLAYER_H
#define SIGNALLIVEPLAYER_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include "BreakMarkerManager.h"
#include "FormulaDbManager.h"
#include "FormulaEvaluator.h"
#include "IrsfCommon.h"
#include "SignalDbManager.h"
#include "SoundFileReader.h"
#include "TrackDataManager.h"
namespace irsf {
/*
 * If lap distance changes by less than this value, we have detected a new lap
 */
constexpr float kNextLapSwitchActivationDistance = -10.0f;

/*SignalLivePlayer
 *
 * activates/deactivates signals, and calculates the related
 * multipliers for channels which are later used for audio
 * */
class SignalLivePlayer {
 public:
  SignalLivePlayer(TrackDataManager* tdm,
                   FormulaDbManager* fdm,
                   SignalDbManager* sdm) noexcept;

  // Populate the events vector based on SignalSet
  void Initialize(const IrsfSignalSet& set,
                  SoundMixer* soundMixer,
                  float*& lapDist,
                  int32_t*& curLap,
                  bool*& onPitRoad,
                  std::vector<iVarInterface_sp>& inputVars);

  // OnTickUpdate should be called each time LapDistance is updated.
  void OnTickUpdate();

  BrakeMarkerManager* bmm{nullptr};

  bool BrakeMarkerManagerIsActive{false};

 private:
  // Add a new signal and create the start and stop events for it
  void RegisterSignal(IrsfSignal* signal);

  // Create a SoundChannel for the given signal event
  std::shared_ptr<SoundChannel> CreateChannelForSignalActivationEvent(
      const SignalActivationEvent& event);

  std::vector<std::unique_ptr<SignalActivationEvent>> events;
  TrackDataManager* trackDataManager;

  // Index of event in events vector which is next in line to be triggered
  size_t nextEventIndex{0};

  bool waitingForNextLap{false};

  int32_t nextEventPairId{kIdNotSelected};

  /*
   * activeChannels which belongs to SoundMixer (sound channels
   * currently active)
   */
  std::vector<SoundChannel*>* activeChannels{nullptr};

  std::vector<SignalActivationEvent*> activeEvents;

  std::unique_ptr<FormulaEvaluator> evaluator;

  FormulaDbManager* formulaDbManager;

  SignalDbManager* signalDbManager;

  std::unique_ptr<SoundFileReader> soundFileReader;

  /*
   * Lap distance on previous tick
   */
  float lapDistancePreviousTick{-1.0f};

  /*
   * Lap Distance on current tick (live data)
   **/
  float* lapDistLive{nullptr};

  // What lap are we really on currently?
  int32_t* curLapLive{nullptr};

  // What lap do we think we are on currently? (from last tick)
  int32_t currentLap{-1};

  bool* onPitRoadLive{nullptr};

  // Were we in the pits on the last tick?
  bool currentOnPitRoad{false};

  void AddActiveChannel(SoundChannel* channel);

  void RemoveActiveChannel(const SoundChannel* channel) noexcept;

  void RemoveAllChannels();

  void AddActiveEvent(SignalActivationEvent* event);

  void RemoveActiveEvent(SignalActivationEvent* event);

  /*
   * update/evaluate all active formulas, and calculate
   * sound channel multipliers
   */
  void UpdateMultipliers();

  std::vector<iVarInterface_sp>* inputVariables{nullptr};

  void StopAllActiveEvents();

  mutable std::mutex rMutex;
};
}  // namespace irsf
#endif  // SIGNALLIVEPLAYER_H

#ifndef BREAKMARKERMANAGER_H
#define BREAKMARKERMANAGER_H

#include <vector>
#include "QDebug"

#include "SoundMixer.h"

namespace irsf {

struct BrakeMarkerSet;
class SoundMixer;
struct BrakeMarkerActive;
struct SoundChannel;

constexpr float kSecondsInOneHour = 3600.0f;

class BrakeMarkerManager {
 public:
  BrakeMarkerManager();

  void Init(float* lapDistanceVar, BrakeMarkerSet set);

  void CheckBrakingMarkerSignal();

  void SetFirstMarkerAsNext() noexcept;

  void AddChannels(SoundMixer* soundMixer);

  //------

 private:
  /*
   * create the PreMarkers and adjust the input ones for latency
   */
  void CreateAndAdjustMarkers();

  float* distVar{nullptr};

  bool Marker_WaitingNextLap{false};
  size_t NextMarkerIndex{0};

  /*
   * how many loops to have the sound active before muting it (ie 2,3, etc)
   */
  int32_t Options_LoopLength{15};

  /*
   *latency between actually hitting the mark and hearing the sound
   *(milliseconds)
   */
  float Options_ExpectedLatencyMs{15};

  /*
   *milliseconds delay between the two warning and final beep
   */
  float Options_DelayBetweenBeeps{400};

  /*
   * if distance < this value, mark as start of next lap
   */
  float Options_NextLapMinDistance{10};
  float Options_SoundVolume{0.7f};

  std::vector<BrakeMarkerActive> InputMarkers;

  /*
   * currently active sounds
   */
  std::vector<BrakeMarkerActive> PlayingMarkers;

  std::vector<BrakeMarkerActive> Markers;
  std::unique_ptr<SoundChannel> soundChannelPreMarker;
  std::unique_ptr<SoundChannel> soundChannelMarker;

  BrakeMarkerSet activeSet;
};

}  // namespace irsf
#endif  // BREAKMARKERMANAGER_H

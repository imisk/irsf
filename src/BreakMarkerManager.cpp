#include "BreakMarkerManager.h"
#include "SoundFileReader.h"

namespace irsf {

BrakeMarkerManager::BrakeMarkerManager() {}

void BrakeMarkerManager::Init(float* lapDistanceVar, BrakeMarkerSet set) {
  qDebug() << "----------------------------------------------------------------"
              "---- Init";
  Options_LoopLength = 15;
  Options_ExpectedLatencyMs = 15;
  Options_DelayBetweenBeeps = 400;
  Options_NextLapMinDistance = 10;
  Options_SoundVolume = 0.7f;

  activeSet = set;

  for (auto& b : set.bmList) {
    BrakeMarkerActive act(soundChannelMarker.get(), b);
    InputMarkers.push_back(act);
  }

  std::sort(InputMarkers.begin(), InputMarkers.end());

  for (size_t i = 0; i < InputMarkers.size(); i++) {
    BrakeMarkerActive bm = InputMarkers[i];

    qDebug() << "i = " << i;
    qDebug() << "bm.distancePosition = " << bm.bm.distancePosition;
    qDebug() << "bm.speedAtMarker = " << bm.bm.speedAtMarker;
  }

  CreateAndAdjustMarkers();

  Marker_WaitingNextLap = false;
  NextMarkerIndex = 0;

  distVar = lapDistanceVar;

  soundChannelMarker->multiplier = 0.0f;
  soundChannelPreMarker->multiplier = 0.0f;
}

void BrakeMarkerManager::CheckBrakingMarkerSignal() {
  // Decrement loops remaining for playing markers
  if (PlayingMarkers.size() > 0) {
    int32_t playingCount = 0;

    for (size_t i = 0; i < PlayingMarkers.size(); i++) {
      --PlayingMarkers[i].loopsRemaining;

      if (PlayingMarkers[i].loopsRemaining <= 0)
        PlayingMarkers[i].sc->multiplier = 0.0;  // Stops the sound
      else
        ++playingCount;
    }

    if (playingCount == 0)
      PlayingMarkers.clear();
  }

  // See if we should be checking for the next lap
  if (Marker_WaitingNextLap) {
    if (*distVar > 0 && *distVar < Options_NextLapMinDistance) {
      Marker_WaitingNextLap = false;
      NextMarkerIndex = 0;
    } else {
      return;
    }
  }

  // See if we have passed the distance of activation for the next marker
  if (*distVar > Markers[NextMarkerIndex].bm.distancePosition) {
    Markers[NextMarkerIndex].loopsRemaining = Options_LoopLength;
    Markers[NextMarkerIndex].sc->offset = 0.0;

    // This is what actually gets the sound to start playing
    Markers[NextMarkerIndex].sc->multiplier = Options_SoundVolume;

    PlayingMarkers.push_back(Markers[NextMarkerIndex]);

    ++NextMarkerIndex;
  }

  // Reached the last marker
  if (NextMarkerIndex == Markers.size()) {
    Marker_WaitingNextLap = true;
    NextMarkerIndex = 0;
  }
}

void BrakeMarkerManager::SetFirstMarkerAsNext() noexcept {
  qDebug() << "----------------------------------------";
  qDebug() << "-------- ### SETTING MARKER TO 0 ### ---";
  qDebug() << "----------------------------------------";

  Marker_WaitingNextLap = false;
  NextMarkerIndex = 0;
}

void BrakeMarkerManager::AddChannels(SoundMixer* soundMixer) {
  std::string sound1Path = "C:\\Dev\\IRSF\\SOUNDS\\PreMarker.wav";

  auto sfr = std::make_unique<SoundFileReader>();

  soundChannelPreMarker = std::make_unique<SoundChannel>();

  soundChannelPreMarker->snd = std::make_unique<SoundData>();
  sfr->LoadSoundChannelFromFile(sound1Path, soundChannelPreMarker->snd.get(),
                                kSoundChannelLoadBufferOverrun, 1.0f);

  soundChannelPreMarker->multiplier = 1.0;
  soundChannelPreMarker->offset = 0;

  //---- add second channel

  std::string sound2Path = "C:\\Dev\\IRSF\\SOUNDS\\Marker.wav";

  soundChannelMarker = std::make_unique<SoundChannel>();
  soundChannelMarker->snd = std::make_unique<SoundData>();
  sfr->LoadSoundChannelFromFile(sound2Path, soundChannelMarker->snd.get(),
                                kSoundChannelLoadBufferOverrun, 1.0f);
  soundChannelMarker->multiplier = 1.0;
  soundChannelMarker->offset = 0;

  soundMixer->activeChannels.push_back(soundChannelPreMarker.get());
  soundMixer->activeChannels.push_back(soundChannelMarker.get());
}

void BrakeMarkerManager::CreateAndAdjustMarkers() {
  for (size_t i = 0; i < InputMarkers.size(); i++) {
    // Adjust for latency
    BrakeMarkerActive bm = InputMarkers[i];
    float metersPerMillisecond = bm.bm.speedAtMarker / kSecondsInOneHour;

    float adjustmentInMeters = metersPerMillisecond * Options_ExpectedLatencyMs;

    bm.bm.distancePosition -= adjustmentInMeters;

    Markers.push_back(bm);

    // Add the two pre-markers
    float distPreMarker1 =
        bm.bm.distancePosition -
        (metersPerMillisecond * Options_DelayBetweenBeeps * 2);
    float distPreMarker2 = bm.bm.distancePosition -
                           (metersPerMillisecond * Options_DelayBetweenBeeps);

    BrakeMarker bmd1 = {distPreMarker1, 0};
    BrakeMarker bmd2 = {distPreMarker2, 0};

    BrakeMarkerActive bma1(soundChannelPreMarker.get(), bmd1);
    BrakeMarkerActive bma2(soundChannelPreMarker.get(), bmd2);

    Markers.push_back(bma1);
    Markers.push_back(bma2);
  }

  std::sort(Markers.begin(), Markers.end());

  for (size_t i = 0; i < Markers.size(); i++) {
    BrakeMarkerActive bm = Markers[i];

    qDebug() << "i _ m = " << i;
    qDebug() << "bm.distancePosition = " << bm.bm.distancePosition;
    qDebug() << "bm.speedAtMarker = " << bm.bm.speedAtMarker;
  }
}
}  // namespace irsf

#ifndef SOUNDMIXER_H
#define SOUNDMIXER_H

#include "IrsfCommon.h"  //
#include "portaudio.h"
namespace irsf {

/*
Mixes multiple audio sources into a signle audio output
*/
class SoundMixer {
 public:
  explicit SoundMixer() noexcept;

  /*
  add all the sounds in activeChannels into a single output "nOut"
  nOut is a buffer chunk of N samples which will be played to the
  device via callback_mixer
  */
  void PerformMix(float* nOut);

  /*
   * @param frameCount Frames per buffer (number of samples per buffer)
   * */
  void Initialize(size_t FrameCount, size_t ChannelCount) noexcept;

  callback_data_s data1;
  callback_data_s data2;

  size_t frameCount = 0;
  size_t channelCount = 0;  // 2 for stereo
  size_t bufferSize = 0;
  float* outCombined{nullptr};
  float* out1{nullptr};
  float* out2{nullptr};

  int32_t callbackCounter = 0;

  void* inOutput{nullptr};
  unsigned long inFrameCount{0};
  PaStreamCallbackTimeInfo* inTimeInfo{nullptr};
  PaStreamCallbackFlags inStatusFlags;
  void* inUserData1{nullptr};

  std::vector<SoundChannel*> activeChannels;
};
}  // namespace irsf
#endif  // SOUNDMIXER_H

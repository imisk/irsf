#ifndef PORTAUDIOMANAGER_H
#define PORTAUDIOMANAGER_H

#include <cstdint>
#define FRAMES_PER_BUFFER (64)

/*
Functions in this class are largely copied from the portaudio github
*/

constexpr size_t kDefaultWaveSampleRate = 44100;

#include "pa_win_wasapi.h"
#include "portaudio.h"
namespace irsf {
/*
 * Wrapper class that manages portaudio (audio playback lib)
 */
class PortaudioManager {
 public:
  explicit PortaudioManager() noexcept;

  void Initialize(int32_t channelCount, int32_t sampleRate);

  void BeginStream(PaStreamCallback* streamCallback);

  void EndStream();

 private:
  void OnError(PaStream* stream, PaError err);

  PaStream* stream{nullptr};
  PaStreamParameters outputParameters;

  int32_t Wav_Samplerate{kDefaultWaveSampleRate};

  struct PaWasapiStreamInfo* wasapiInfo{nullptr};
};
}  // namespace irsf
#endif  // PORTAUDIOMANAGER_H

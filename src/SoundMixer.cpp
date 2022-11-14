
#include "SoundMixer.h"

#include <fstream>
#include <iostream>

using namespace irsf;

SoundMixer::SoundMixer() noexcept {}

void SoundMixer::PerformMix(float* nOut) {
  for (size_t si = 0; si < bufferSize; si++) {
    nOut[si] = 0.0f;
  }

  for (const auto& currentChannel : activeChannels) {
    size_t cOffset = currentChannel->offset;

    for (size_t i = 0; i < bufferSize; i++) {
      nOut[i] +=
          currentChannel->multiplier * currentChannel->snd->data[cOffset];

      ++cOffset;
    }

    currentChannel->offset += bufferSize;

    if (currentChannel->offset > currentChannel->snd->sampleLength) {
      currentChannel->offset -= currentChannel->snd->sampleLength;
    }
  }
}

void SoundMixer::Initialize(size_t FrameCount, size_t ChannelCount) noexcept {
  frameCount = FrameCount;
  channelCount = ChannelCount;

  bufferSize = frameCount * channelCount;
}

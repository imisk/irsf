#ifndef SOUNDFILEREADER_H
#define SOUNDFILEREADER_H

#include <string>
#include <vector>
#include "IrsfCommon.h"
#include "QDebug"
namespace irsf {

// How much additional data (sample count) to load for looping safety
constexpr size_t kSoundChannelLoadBufferOverrun = 1024;

// Note: default settings for IRSF is to load 44100 WAVs with 32bit per sample!

/*
 * Wrapper class for libsnd, reads audio files from disk.
 */

class SoundFileReader {
 public:
  SoundFileReader() noexcept;

  /*bufferOverrun: how much to copy the loop sample beginning
   * after the end of the sample so we can easily move the
   * reading point without hitting the end
   */
  void LoadSoundChannelFromFile(const std::string& fileName,
                                SoundData* retData,
                                size_t bufferOverrun,
                                float multiplier) const;

 private:
  /*bufferOverrun: how much to copy the loop sample beginning
   * after the end of the sample so we can easily move the
   * reading point without hitting the end
   */
  void CreateSoundData(std::vector<float>& inData,
                       SoundData* retData,
                       size_t bufferOverrun) const;
};
}  // namespace irsf
#endif  // SOUNDFILEREADER_H

#ifndef TRACKDATAIO_H
#define TRACKDATAIO_H

#include <fstream>
#include "IrsfCommon.h"
namespace irsf {
constexpr int32_t kCurrentTrackDataFileVersion = 1;

/*
 * Utility class.
 * Reads and writes track data to disk (track names, configurations, ids,
 * Track Sectors, etc)
 */
class TrackDataIO {
 public:
  TrackDataIO() noexcept = default;

  // Save all data to disk
  void Save(TrackDataAll& data);

  // Load from disk
  void Load(TrackDataAll& data);

 private:
  std::fstream* fileOutput;

  std::ifstream* fileInput;

  int32_t versionOfInputFile;

  void WriteTrack(Track& track);

  void ReadTrack(TrackDataAll& data);

  void WriteTrackLayoutConfiguration(TrackLayoutConfiguration& trackConfig);

  void ReadTrackLayoutConfiguration(Track& data);

  void WriteTrackSector(TrackSector& ts);

  void ReadTrackSector(TrackDataAll& data);
};
}  // namespace irsf
#endif  // TRACKDATAIO_H

#ifndef TRACKSECTORMANAGER_H
#define TRACKSECTORMANAGER_H

#include <mutex>
#include "TrackDataManager.h"
namespace irsf {
/*
 * Adds, removes, finds Track Sectors (manages data)
 */
class TrackSectorManager {
 public:
  explicit TrackSectorManager(TrackDataManager* tdm) noexcept;

  void GetTrackAndTrackConfigName(
      int32_t trackId,
      int32_t configId,
      std::string& retTrackAndConfigName) const noexcept;

  void SetCurrentTrack(int32_t trackId, int32_t configId) noexcept;

  std::tuple<int32_t, int32_t> GetCurrentTrack();

  void GetListOfSectorsForCurrentTrack(std::vector<TrackSector>& retSectors);

  void AddTrackSector(TrackSector& ts);

  void RemoveTrackSector(const std::string& tsName);

  int32_t GetTrackSectorId(const std::string& tsName) const;

  TrackSector GetTrackSector(const int32_t& trackSectorId) const;

 private:
  TrackDataManager* trackDataManager;

  int32_t currentTrackId{kIdNotSelected};

  int32_t currentTrackConfigId{kIdNotSelected};

  mutable std::mutex rMutex;
};
}  // namespace irsf
#endif  // TRACKSECTORMANAGER_H

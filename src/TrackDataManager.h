#ifndef TRACKDATAMANAGER_H
#define TRACKDATAMANAGER_H

#include <optional>
#include "IrsfCommon.h"
#include "TrackDataIO.h"
namespace irsf {
/*
Class responsible for holding and managing the data about user created
track data.

to-do : this class no longer respects the single responsibility principle
*/
class TrackDataManager {
 public:
  explicit TrackDataManager();

  void AddNewTrack(const std::string& trackName);

  void RemoveTrack(const int32_t& trackId);

  void AddNewTrackConfig(const int32_t& parentTrackId,
                         const std::string& configName,
                         const float& trackLengthMeters);

  void RemoveTrackConfig(const int32_t& parentTrackId,
                         const int32_t& trackConfigId);

  void AddNewTrackSector(TrackSector& trackSector);

  void RemoveTrackSector(const int32_t& parentTrackId,
                         const int32_t& trackConfigId,
                         const std::string& tsName);

  void GetTrackSectorId(const int32_t& trackId,
                        const int32_t& trackConfigId,
                        const std::string& name,
                        int32_t& retTrackSectorId) const;

  void GetTrackSectorName(int32_t trackSectorId,
                          std::string& retTrackSectorName) const;

  std::optional<TrackSector> GetTrackSector(int32_t trackSectorId) const;

  void LoadData();

  // Rename the _bak file to normal (try using backup)
  void RenameBakToMain();

  TrackDataAll& GetData() noexcept;

  void GetTrackId(const std::string& trackName, int32_t& retId) const;

  void GetTrackConfig(const int32_t& parentTrackId,
                      const std::string& configName,
                      TrackLayoutConfiguration& retConfig) const;

  void GetTrackConfigId(const int32_t& parentTrackId,
                        const std::string& configName,
                        int32_t& retId) const;

  void GetTrackName(int32_t trackId, std::string& retName) const noexcept;

  void GetTrackConfigName(int32_t parentTrackId,
                          int32_t configId,
                          std::string& retName) const noexcept;

  void GetTrackAndConfigName(const int32_t& trackId,
                             const int32_t& configId,
                             std::string& retName) const noexcept;

 private:
  TrackDataAll data;

  TrackDataIO io;

  bool dataIsLoaded{false};
};
}  // namespace irsf
#endif  // TRACKDATAMANAGER_H

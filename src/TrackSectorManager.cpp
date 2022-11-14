
#include "TrackSectorManager.h"
#include <iostream>

using namespace irsf;

TrackSectorManager::TrackSectorManager(TrackDataManager* tdm) noexcept
    : trackDataManager(tdm) {}

void TrackSectorManager::GetTrackAndTrackConfigName(
    int32_t trackId,
    int32_t configId,
    std::string& retTrackAndConfigName) const noexcept {
  std::scoped_lock<std::mutex> lock(rMutex);

  trackDataManager->GetTrackAndConfigName(trackId, configId,
                                          retTrackAndConfigName);

  return;
}

void TrackSectorManager::SetCurrentTrack(int32_t trackId,
                                         int32_t configId) noexcept {
  currentTrackId = trackId;
  currentTrackConfigId = configId;
}

std::tuple<int32_t, int32_t> TrackSectorManager::GetCurrentTrack() {
  return std::make_tuple(currentTrackId, currentTrackConfigId);
}

void TrackSectorManager::GetListOfSectorsForCurrentTrack(
    std::vector<TrackSector>& retSectors) {
  retSectors.clear();

  TrackDataAll data = trackDataManager->GetData();

  for (auto& ts : data.trackSectors) {
    if (ts.trackId == currentTrackId) {
      if (ts.trackId == kTrackIdAllTracks) {
        retSectors.push_back(ts);
      } else if (ts.trackConfigurationId == currentTrackConfigId) {
        retSectors.push_back(ts);
      }
    }
  }
}

void TrackSectorManager::AddTrackSector(TrackSector& ts) {
  trackDataManager->AddNewTrackSector(ts);
}

void TrackSectorManager::RemoveTrackSector(const std::string& tsName) {
  std::cout << "Removing track sector" << tsName.c_str() << "\n";

  trackDataManager->RemoveTrackSector(currentTrackId, currentTrackConfigId,
                                      tsName);
}

int32_t TrackSectorManager::GetTrackSectorId(const std::string& tsName) const {
  std::scoped_lock<std::mutex> lock(rMutex);

  int32_t retId = kIdNotSelected;

  trackDataManager->GetTrackSectorId(currentTrackId, currentTrackConfigId,
                                     tsName, retId);

  std::cout << "track sector id = " << retId << std::endl;

  return retId;
}

TrackSector TrackSectorManager::GetTrackSector(
    const int32_t& trackSectorId) const {
  std::scoped_lock<std::mutex> lock(rMutex);

  TrackSector ret;
  ret.id = kIdNotSelected;

  auto tsret = trackDataManager->GetTrackSector(trackSectorId);

  if (tsret.has_value()) {
    ret = tsret.value();
  }

  return ret;
}

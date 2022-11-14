
#include "TrackDataManager.h"
#include <iostream>
#include "QDebug"

using namespace irsf;

TrackDataManager::TrackDataManager() {}

void TrackDataManager::AddNewTrack(const std::string& trackName) {
  int32_t maxIdFound = kIdNotSelected;

  if (trackName.size() == 0)
    throw IrsfException(IrsfError::InvalidName);

  for (const auto& track : data.tracks) {
    if (track.id > maxIdFound)
      maxIdFound = track.id;
  }

  data.tracks.push_back({trackName, maxIdFound + 1, {}});

  io.Save(data);
}

void TrackDataManager::RemoveTrack(const int32_t& trackId) {
  bool found = false;
  std::streamsize deleteIndex = 0;
  bool finished = false;
  size_t i = 0;

  while (!finished) {
    if (data.tracks[i].id == trackId) {
      found = true;
      deleteIndex = static_cast<std::streamsize>(i);
      finished = true;
    }

    ++i;
    if (i == data.tracks.size())
      finished = true;
  }

  if (found) {
    data.tracks.erase(data.tracks.begin() + deleteIndex);

    io.Save(data);

    return;
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void TrackDataManager::AddNewTrackConfig(const int32_t& parentTrackId,
                                         const std::string& configName,
                                         const float& trackLengthMeters) {
  if (configName.size() == 0)
    throw IrsfException(IrsfError::InvalidName);

  if (trackLengthMeters < 1)
    throw IrsfException(IrsfError::InvalidInput);

  for (auto& track : data.tracks) {
    if (track.id == parentTrackId) {
      int32_t maxId = kIdNotSelected;

      for (const auto& config : track.configurations) {
        if (config.id > maxId)
          maxId = config.id;
      }

      TrackLayoutConfiguration newConfig;
      newConfig.id = maxId + 1;
      newConfig.name = configName;
      newConfig.totalLengthMeters = trackLengthMeters;

      track.configurations.push_back(newConfig);

      io.Save(data);

      return;
    }
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void TrackDataManager::RemoveTrackConfig(const int32_t& parentTrackId,
                                         const int32_t& trackConfigId) {
  qDebug() << "RemoveTrackConfig";

  for (auto& track : data.tracks) {
    if (track.id == parentTrackId) {
      std::streamsize deleteIndex = 0;
      bool found = false;
      bool finished = false;
      size_t i = 0;

      while (!finished) {
        if (track.configurations[i].id == trackConfigId) {
          found = true;
          deleteIndex = static_cast<std::streamsize>(i);
          finished = true;
        }

        ++i;
        if (i == track.configurations.size())
          finished = true;
      }

      if (found) {
        track.configurations.erase(track.configurations.begin() + deleteIndex);

        io.Save(data);

        return;
      }
    }
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void TrackDataManager::AddNewTrackSector(TrackSector& trackSector) {
  int32_t maxIdFound = kIdNotSelected;

  for (const auto& ts : data.trackSectors) {
    if (ts.id > maxIdFound)
      maxIdFound = ts.id;
  }

  trackSector.id = maxIdFound + 1;

  // check sector with this name doesn't already exist

  bool nameOK = true;
  bool finished = false;
  size_t i = 0;

  while (!finished) {
    const auto& ts = data.trackSectors[i];
    if (ts.trackId == trackSector.trackId &&
        ts.trackConfigurationId == trackSector.trackConfigurationId) {
      if (ts.name.compare(trackSector.name) == 0) {
        nameOK = false;
        finished = true;
      }
    }

    ++i;
    if (i == data.trackSectors.size())
      finished = true;
  }

  if (nameOK) {
    data.trackSectors.push_back(trackSector);
  } else {
    std::cout << "Error : cannot add track sector. Name already exists. \n";
    throw IrsfException(IrsfError::NameAlreadyExists);
  }

  io.Save(data);
}

void TrackDataManager::RemoveTrackSector(const int32_t& parentTrackId,
                                         const int32_t& trackConfigId,
                                         const std::string& tsName) {
  bool found = false;
  std::streamsize deleteIndex = 0;
  bool finished = false;
  size_t i = 0;

  while (!finished) {
    if (data.trackSectors[i].trackId == parentTrackId) {
      if (data.trackSectors[i].trackConfigurationId == trackConfigId) {
        if (data.trackSectors[i].name.compare(tsName) == 0) {
          found = true;
          deleteIndex = static_cast<std::streamsize>(i);
          finished = true;
        }
      }
    }

    ++i;
    if (i == data.trackSectors.size())
      finished = true;
  }

  if (found) {
    data.trackSectors.erase(data.trackSectors.begin() + deleteIndex);
    io.Save(data);
    return;
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void TrackDataManager::GetTrackSectorId(const int32_t& trackId,
                                        const int32_t& trackConfigId,
                                        const std::string& name,
                                        int32_t& retTrackSectorId) const {
  bool found = false;

  retTrackSectorId = kIdNotSelected;
  bool finished = false;
  size_t i = 0;

  while (!finished) {
    if (data.trackSectors[i].trackId == trackId) {
      if (data.trackSectors[i].trackConfigurationId == trackConfigId ||
          trackId == 0) {
        if (data.trackSectors[i].name.compare(name) == 0) {
          found = true;
          int32_t x = data.trackSectors[i].id;
          std::cout << "x ts id = " << x << std::endl;
          retTrackSectorId = data.trackSectors[i].id;
          finished = true;
        }
      }
    }

    ++i;
    if (i == data.trackSectors.size())
      finished = true;
  }

  if (found) {
    std::cout << "GetTrackSectorId - found \n";
    return;
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void TrackDataManager::GetTrackSectorName(
    int32_t trackSectorId,
    std::string& retTrackSectorName) const {
  if (trackSectorId == kIdNotSelected) {
    retTrackSectorName = "";
    return;
  }

  for (const auto& ts : data.trackSectors) {
    if (ts.id == trackSectorId) {
      retTrackSectorName = ts.name;
      return;
    }
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

std::optional<TrackSector> TrackDataManager::GetTrackSector(
    int32_t trackSectorId) const {
  std::optional<TrackSector> ret;

  for (const auto& ts : data.trackSectors) {
    if (ts.id == trackSectorId) {
      // retTrackSector = ts;
      // return;
      ret = ts;
      return ret;
    }
  }

  throw IrsfException(IrsfError::ItemNotFound, "Track sector");

  return ret;
}

void TrackDataManager::LoadData() {
  if (dataIsLoaded)
    return;

  io.Load(data);

  dataIsLoaded = true;
}

void TrackDataManager::RenameBakToMain() {
  int32_t status;

  std::cout << "Renaming bak to main: TrackData.idb \n";

  status = remove("TrackData.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file TrackData.idb \n";

  status = rename("TrackData_bak.idb", "TrackData.idb");
  if (status != 0)
    std::cout << "Warning : Could not rename file "
                 "TrackData_bak.idb to TrackData.idb \n";
}

TrackDataAll& TrackDataManager::GetData() noexcept {
  return data;
}

void TrackDataManager::GetTrackId(const std::string& trackName,
                                  int32_t& retId) const {
  for (const auto& track : data.tracks) {
    if (trackName == track.name) {
      retId = track.id;
      std::cout << "Selected track name: " << track.name << "\n";
      return;
    }
  }

  throw IrsfException(IrsfError::ItemNotFound);
}

void TrackDataManager::GetTrackConfig(
    const int32_t& parentTrackId,
    const std::string& configName,
    TrackLayoutConfiguration& retConfig) const {
  for (const auto& track : data.tracks) {
    if (track.id == parentTrackId) {
      for (size_t i = 0; i < track.configurations.size(); i++) {
        if (track.configurations[i].name == configName) {
          retConfig = track.configurations[i];

          std::cout << "GetTrackConfig : found \n";

          return;
        }
      }
    }
  }

  std::cout << "GetTrackConfig : not found \n";

  throw IrsfException(IrsfError::ItemNotFound);
}

void TrackDataManager::GetTrackConfigId(const int32_t& parentTrackId,
                                        const std::string& configName,
                                        int32_t& retId) const {
  TrackLayoutConfiguration config;

  retId = kIdNotSelected;

  GetTrackConfig(parentTrackId, configName, config);

  retId = config.id;
}

void TrackDataManager::GetTrackName(int32_t trackId,
                                    std::string& retName) const noexcept {
  retName = "None";

  for (const auto& track : data.tracks) {
    if (track.id == trackId) {
      retName = track.name;
    }
  }

  return;
}

void TrackDataManager::GetTrackConfigName(int32_t parentTrackId,
                                          int32_t configId,
                                          std::string& retName) const noexcept {
  retName = "None";

  for (const auto& track : data.tracks) {
    if (track.id == parentTrackId) {
      for (const auto& config : track.configurations) {
        if (config.id == configId) {
          retName = config.name;
        }
      }
    }
  }

  return;
}

void TrackDataManager::GetTrackAndConfigName(
    const int32_t& trackId,
    const int32_t& configId,
    std::string& retName) const noexcept {
  std::string trackName, configName;

  GetTrackName(trackId, trackName);

  configName = "";

  retName = trackName;

  if (trackId >= 0 && trackId != kTrackIdAllTracks) {
    GetTrackConfigName(trackId, configId, configName);

    retName = trackName + " - " + configName;
  }

  return;
}

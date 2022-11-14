
#include "TrackDataIO.h"
#include <QDebug>
#include <iostream>
#include "BinaryReadWriteUtils.h"

using namespace irsf;

void TrackDataIO::Save(TrackDataAll& data) {
  qDebug() << "TrackData - SAVE";

  int32_t status;

  status = remove("TrackData_bak.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file TrackData_bak.idb \n";

  status = rename("TrackData.idb", "TrackData_bak.idb");
  if (status != 0)
    std::cout << "Warning : Could not rename file "
                 "TrackData.idb to TrackData_bak.idb \n";

  // fileOutput = std::fstream(
  //                "TrackData.idb",
  //                std::ios::out | std::ios::binary | std::ios::ate);

  std::string fileName = "TrackData.idb";
  auto f = fstream_raii_write(fileName);
  fileOutput = f.get();

  if (fileOutput->is_open() == false)
    throw IrsfException(IrsfError::CannotOpenFile);

  // version:
  auto version = kCurrentTrackDataFileVersion;
  WriteBinary(*fileOutput, &version);

  // Tracks:
  size_t trackCount = data.tracks.size();
  WriteBinary(*fileOutput, &trackCount);

  for (size_t i = 0; i < data.tracks.size(); i++) {
    WriteTrack(data.tracks[i]);
  }

  // TrackSectors:
  size_t trackSectionCount = data.trackSectors.size();
  WriteBinary(*fileOutput, &trackSectionCount);

  for (size_t i = 0; i < data.trackSectors.size(); i++) {
    WriteTrackSector(data.trackSectors[i]);
  }
}

void TrackDataIO::Load(TrackDataAll& data) {
  std::string filename = "TrackData.idb";

  auto cstream = fstream_raii_read(filename);
  fileInput = cstream.get();

  if (fileInput->is_open() != true)
    throw IrsfException(IrsfError::FileNotFound);

  data.tracks.clear();
  data.trackSectors.clear();

  // Read Version
  ReadBinary(fileInput, &versionOfInputFile);

  // Read Tracks
  size_t trackCount;
  ReadBinary(fileInput, &trackCount);

  for (size_t i = 0; i < trackCount; i++) {
    ReadTrack(data);
  }

  // TrackSections
  size_t trackSectionCount;
  ReadBinary(fileInput, &trackSectionCount);

  for (size_t i = 0; i < trackSectionCount; i++) {
    ReadTrackSector(data);
  }

  std::cout << "track data loaded \n";
}

void TrackDataIO::WriteTrack(Track& track) {
  // track.name
  size_t nameSize = track.name.size();
  WriteBinary(*fileOutput, &nameSize);

  WriteBinaryCharArray(*fileOutput, track.name.c_str(), nameSize);

  // track.id
  WriteBinary(*fileOutput, &track.id);

  // track.configurations
  size_t configSize = track.configurations.size();
  WriteBinary(*fileOutput, &configSize);

  for (size_t i = 0; i < track.configurations.size(); i++) {
    WriteTrackLayoutConfiguration(track.configurations[i]);
  }
}

void TrackDataIO::ReadTrack(TrackDataAll& data) {
  Track track;

  // Track.name
  size_t nameSize;
  ReadBinary(fileInput, &nameSize);

  track.name = std::string(nameSize, ' ');
  ReadBinaryCharArray(fileInput, &track.name[0], nameSize);

  // Track.id
  int32_t id;
  ReadBinary(fileInput, &id);
  track.id = id;

  // Track.configurations
  size_t configCount;
  ReadBinary(fileInput, &configCount);

  for (size_t i = 0; i < configCount; i++) {
    ReadTrackLayoutConfiguration(track);
  }

  data.tracks.push_back(track);
}

void TrackDataIO::WriteTrackLayoutConfiguration(
    TrackLayoutConfiguration& trackConfig) {
  // trackConfig.name
  size_t nameSize = trackConfig.name.size();
  WriteBinary(*fileOutput, &nameSize);

  WriteBinaryCharArray(*fileOutput, trackConfig.name.c_str(), nameSize);

  WriteBinary(*fileOutput, &trackConfig.id);

  WriteBinary(*fileOutput, &trackConfig.totalLengthMeters);
}

void TrackDataIO::ReadTrackLayoutConfiguration(Track& t) {
  TrackLayoutConfiguration config;

  size_t nameSize;
  ReadBinary(fileInput, &nameSize);

  config.name = std::string(nameSize, ' ');
  ReadBinaryCharArray(fileInput, &config.name[0], nameSize);

  // config.id
  int32_t id;
  ReadBinary(fileInput, &id);
  config.id = id;

  // config.totalLengthMeters
  float length;
  ReadBinary(fileInput, &length);
  config.totalLengthMeters = length;

  t.configurations.push_back(config);
}

void TrackDataIO::WriteTrackSector(TrackSector& ts) {
  // TrackSector.name
  size_t nameSize = ts.name.size();
  WriteBinary(*fileOutput, &nameSize);

  WriteBinaryCharArray(*fileOutput, ts.name.c_str(), nameSize);

  // TrackSector.id
  WriteBinary(*fileOutput, &ts.id);

  // TrackSector.startDistance
  WriteBinary(*fileOutput, &ts.startDistance);

  // TrackSector.endDistance
  WriteBinary(*fileOutput, &ts.endDistance);

  // TrackSector.trackId
  WriteBinary(*fileOutput, &ts.trackId);

  // TrackSector.trackConfigurationId
  WriteBinary(*fileOutput, &ts.trackConfigurationId);
}

void TrackDataIO::ReadTrackSector(TrackDataAll& data) {
  TrackSector ts;

  // TrackSection.name
  size_t nameSize;
  ReadBinary(fileInput, &nameSize);

  ts.name = std::string(nameSize, ' ');
  ReadBinaryCharArray(fileInput, &ts.name[0], nameSize);

  // TrackSection.id
  ReadBinary(fileInput, &ts.id);

  // TrackSection.startDistance
  ReadBinary(fileInput, &ts.startDistance);

  // TrackSection.endDistance
  ReadBinary(fileInput, &ts.endDistance);

  // TrackSection.trackId
  ReadBinary(fileInput, &ts.trackId);

  // TrackSection.trackConfigurationId
  ReadBinary(fileInput, &ts.trackConfigurationId);

  data.trackSectors.push_back(ts);
}

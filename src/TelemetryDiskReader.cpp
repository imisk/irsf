
#include "TelemetryDiskReader.h"
#include "BinaryReadWriteUtils.h"

using namespace irsf;

TelemetryDiskReader::TelemetryDiskReader() noexcept {}

void TelemetryDiskReader::LoadTelemetryFromFile(const std::string& fileName,
                                                TelemetryData* telemetryData) {
  size_t totalRead = 0;

  auto cstream = fstream_raii_read(fileName);

  fileInputStream = cstream.get();

  if (fileInputStream->is_open() == false)
    throw IrsfException(IrsfError::CannotOpenFile);

  ReadBeginningOfFile(telemetryData->Variables);

  readingCurrentLapVectorIndex = 0;

  telemetryData->LapIndex[readingCurrentLap] = readingCurrentLapVectorIndex;

  telemetryData->Data.emplace_back(std::vector<float>());

  TelemetryWriterEntryHeader header;

  header = ReadNextHeader();

  while (header != TelemetryWriterEntryHeader::EndOfFile) {
    if (header == TelemetryWriterEntryHeader::DataEntry) {
      std::vector<float> newData;
      ReadData(newData);

      totalRead += newData.size();

      telemetryData->Data[telemetryData->LapIndex[readingCurrentLap]].insert(
          telemetryData->Data[telemetryData->LapIndex[readingCurrentLap]].end(),
          newData.begin(), newData.end());

    } else if (header == TelemetryWriterEntryHeader::CurrentLap) {
      readingCurrentLap = ReadCurrentLap();

      qDebug() << "readingCurrentLap = " << readingCurrentLap;
      /*
       * If data for this lap has not been read so far,
       * add a new vector for it.
       */

      if (telemetryData->LapIndex.find(readingCurrentLap) ==
          telemetryData->LapIndex.end()) {
        ++readingCurrentLapVectorIndex;
        telemetryData->LapIndex[readingCurrentLap] =
            readingCurrentLapVectorIndex;

        telemetryData->Data.emplace_back(std::vector<float>());
      }

    } else {
      /*
      We found an error reading the file, probably
      abrupt ending in recording.
      So, let's just try to use the data we loaded so far anyway!
      */

      header = TelemetryWriterEntryHeader::EndOfFile;
    }

    if (header != TelemetryWriterEntryHeader::EndOfFile) {
      header = ReadNextHeader();
    }
  }

  qDebug() << "______ end of telemetry file ____ totalRead = " << totalRead;
}

TelemetryWriterEntryHeader TelemetryDiskReader::ReadNextHeader() {
  TelemetryWriterEntryHeader header;
  ReadBinary(fileInputStream, &header);
  return header;
}

int32_t TelemetryDiskReader::ReadVersion() {
  int32_t readVersion;
  ReadBinary(fileInputStream, &readVersion);
  return readVersion;
}

void TelemetryDiskReader::ReadVariableIdList(std::vector<VariableId>& retVars) {
  size_t varCount;

  retVars.clear();

  ReadBinary(fileInputStream, &varCount);

  for (size_t i = 0; i < varCount; i++) {
    VariableId id;
    ReadBinary(fileInputStream, &id);

    retVars.push_back(id);
  }
}

int32_t TelemetryDiskReader::ReadCurrentLap() {
  int32_t readLap;
  ReadBinary(fileInputStream, &readLap);
  return readLap;
}

void TelemetryDiskReader::ReadData(std::vector<float>& retData) {
  size_t valueCount;

  ReadBinary(fileInputStream, &valueCount);

  std::vector<float> fDataVec(valueCount, 0);

  fileInputStream->read(
      reinterpret_cast<char*>(&fDataVec[0]),
      static_cast<std::streamsize>(sizeof(float) * valueCount));

  if (!fileInputStream)
    throw IrsfException(IrsfError::CorruptedData);

  copy(&fDataVec[0], &fDataVec[0] + valueCount, back_inserter(retData));
}

void TelemetryDiskReader::ReadBeginningOfFile(
    std::vector<VariableId>& retVariableList) {
  TelemetryWriterEntryHeader header;
  int32_t readVersion = -1;

  header = ReadNextHeader();

  if (header != TelemetryWriterEntryHeader::VersionInfo)
    throw IrsfException(IrsfError::TelemetryFileBadFormat);

  std::cout << "Found VersionInfo header \n";

  readVersion = ReadVersion();

  std::cout << "readVersion = " << readVersion << std::endl;

  header = ReadNextHeader();
  if (header != TelemetryWriterEntryHeader::VariableDefinitions)
    throw IrsfException(IrsfError::TelemetryFileBadFormat);

  std::cout << "Found VariableDefinitions header \n";

  ReadVariableIdList(retVariableList);

  header = ReadNextHeader();
  if (header != TelemetryWriterEntryHeader::CurrentLap)
    throw IrsfException(IrsfError::TelemetryFileBadFormat);

  readingCurrentLap = ReadCurrentLap();

  std::cout << "Read current lap = " << readingCurrentLap << std::endl;
}

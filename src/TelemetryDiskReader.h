#ifndef TELEMETRYDISKREADER_H
#define TELEMETRYDISKREADER_H

#include <fstream>
#include <iostream>
#include "IrsfCommon.h"
#include "QDebug"
#include "TelemetryDiskReaderInterface.h"
namespace irsf {

/*
 * Reads telemetry data from disk
 */
class TelemetryDiskReader : public TelemetryDiskReaderInterface {
 public:
  TelemetryDiskReader() noexcept;

  // TelemetryDiskReaderInterface interface
 public:
  void LoadTelemetryFromFile(const std::string& fileName,
                             TelemetryData* telemetryData) override;

 private:
  void ReadBeginningOfFile(std::vector<VariableId>& retVariableList);

  TelemetryWriterEntryHeader ReadNextHeader();
  int32_t ReadVersion();
  void ReadVariableIdList(std::vector<VariableId>& retVars);
  int32_t ReadCurrentLap();
  void ReadData(std::vector<float>& retData);

  std::ifstream* fileInputStream;

  int32_t readingCurrentLap{-1};
  size_t readingCurrentLapVectorIndex{0};
};
}  // namespace irsf
#endif  // TELEMETRYDISKREADER_H

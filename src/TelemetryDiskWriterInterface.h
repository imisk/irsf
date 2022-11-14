#ifndef TELEMETRYDISKWRITERINTERFACE_H
#define TELEMETRYDISKWRITERINTERFACE_H

#include <string>
#include <vector>
#include "IrsfCommon.h"
namespace irsf {
class TelemetryDiskWriterInterface {
 public:
  virtual ~TelemetryDiskWriterInterface() {}

  virtual void OpenFile(const std::string& fileName) = 0;

  virtual void WriteData_Prepare(float* valuesToWrite,
                                 const size_t& valuesPerTick,
                                 const size_t& totalTicks) = 0;

  virtual void WriteData() = 0;

  virtual void WriteFileVersion() = 0;

  virtual void WriteCurrentLap_Prepare(int32_t currentLap) = 0;

  virtual void WriteCurrentLap() = 0;

  virtual void WriteVariableList(const std::vector<VariableId>& varList) = 0;

  virtual void WriteEndOfFile() = 0;

  virtual void CloseFile() = 0;
};
}  // namespace irsf
#endif  // TELEMETRYDISKWRITERINTERFACE_H

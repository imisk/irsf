#ifndef TELEMETRYDISKREADERINTERFACE_H
#define TELEMETRYDISKREADERINTERFACE_H

#include <string>
#include <vector>
#include "IrsfCommon.h"
namespace irsf {
class TelemetryDiskReaderInterface {
 public:
  virtual ~TelemetryDiskReaderInterface() {}

  virtual void LoadTelemetryFromFile(const std::string& fileName,
                                     TelemetryData* telemetryData) = 0;
};
}  // namespace irsf
#endif  // TELEMETRYDISKREADERINTERFACE_H

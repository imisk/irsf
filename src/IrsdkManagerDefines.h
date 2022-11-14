#ifndef IRSDKMANAGERDEFINES_H
#define IRSDKMANAGERDEFINES_H

#include <Windows.h>
#include <vector>
#include "irsdk/irsdk_defines.h"

namespace irsf {
namespace irsdk {

class IrsdkManagerInterface {
 public:
  IrsdkManagerInterface() = default;
  IrsdkManagerInterface(const IrsdkManagerInterface& other) = default;
  IrsdkManagerInterface(IrsdkManagerInterface&& other) = default;
  IrsdkManagerInterface& operator=(const IrsdkManagerInterface& other) =
      default;
  IrsdkManagerInterface& operator=(IrsdkManagerInterface&& other) = default;
  virtual ~IrsdkManagerInterface() noexcept = 0;
  virtual bool Startup() = 0;
  virtual bool WaitForData() = 0;
};

struct IrsdkWindowsCtr {
  HANDLE hMemMapFile;
  const char* pSharedMem;
  HANDLE hDataValidEvent;
};

struct IrsdkVarsData {
  const irsdk_header* pHeader;
  char* data;
  unsigned long long dataLength;
  std::vector<irsdk_varHeader*> variableHeaders;
  int32_t lastTickCount;
  time_t lastValidTime;
};
}  // namespace irsdk

}  // namespace irsf

#endif  // IRSDKMANAGERDEFINES_H

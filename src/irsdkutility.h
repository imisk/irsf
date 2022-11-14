#ifndef IRSDKUTILITY_H
#define IRSDKUTILITY_H

#include "IrsdkManagerDefines.h"
#include "IrsfCommon.h"
#include "irsdk/irsdk_defines.h"

namespace irsf {
namespace irsdk {

// Returns true if no error
bool IrsdkResizeData(IrsdkVarsData* varData);

int32_t irsdk_varNameToIndex(IrsdkVarsData* varData,
                             IrsdkWindowsCtr* winCtr,
                             const char* name) noexcept(false);

const irsdk_varHeader* irsdk_getVarHeaderEntry(IrsdkVarsData* varData,
                                               IrsdkWindowsCtr* winCtr,
                                               int32_t index) noexcept;

void GetVarType(VariableId varId, irsdk_VarType& retType) noexcept;

}  // namespace irsdk
}  // namespace irsf

#endif  // IRSDKUTILITY_H

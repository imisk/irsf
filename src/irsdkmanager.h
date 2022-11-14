#ifndef IRSDKMANAGER_H
#define IRSDKMANAGER_H

#include "IrsdkManagerDefines.h"

//#include "IrsfCommon.h"
#include <QDebug>
#include <thread>

#include "InputVariableInterface.h"
#include "InputVariableRawInterface.h"

namespace irsf {

enum class VariableId;

namespace irsdk {
/*
Manager class that handles everything from the iRacing SDK. Based on code
examples provided by iRacing, adapted to our needs.
*/
class IrsdkManager : public IrsdkManagerInterface {
 public:
  explicit IrsdkManager();

  // Returns true if successful
  bool Startup() final;

  bool WaitForData() final;

  void GetIrsdkValuePointer(const std::string& varName,
                            irsdk_VarType& retType,
                            void*& retPtr);

  void InitVariables(
      const std::vector<VariableId>& inputVariablesIn,
      std::vector<iVarInterface_sp>& retInputVariables,
      std::vector<iVarRawInterface_sp>& retInputVariablesNonFloat);

 private:
  std::unique_ptr<IrsdkWindowsCtr> winCtr{std::make_unique<IrsdkWindowsCtr>()};
  std::unique_ptr<IrsdkVarsData> varData{std::make_unique<IrsdkVarsData>()};
  bool isInitialized{false};

  /*
   * Get variable headers from iRacing which will describe
   * all of the variables
   * available from the shared memory given by iRacing.
   */
  void UpdateVarHeaders();
  bool UpdateTelemetry();
};

}  // namespace irsdk
}  // namespace irsf

#endif  // IRSDKMANAGER_H

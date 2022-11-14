
#include "FormulaInputVariableFactory.h"
#include "InputVariableRaw.h"
#include "irsdkutility.h"
using namespace irsf::irsdk;
using namespace irsf;

/*
 * to-do: a future version of IRSF will support processed input variables so
 * that you can use average values of certain inputs for smoother values, etc.
 */
FormulaInputVariableFactory::FormulaInputVariableFactory() noexcept {}

// currently unused function
void FormulaInputVariableFactory::CreateInputVariable(
    VariableId variableId,
    std::unique_ptr<InputVariableInterface>& retInputVar) const noexcept {
  if (static_cast<int32_t>(variableId) <= kIrsdkMaxVariableId) {
    irsdk_VarType type = irsdk_int;
    GetVarType(variableId, type);

    if (type == irsdk_float) {
      retInputVar =
          std::make_unique<InputVariableRaw<float>>(variableId, nullptr);
    }
  }
}

// currently unused function
void FormulaInputVariableFactory::CreateInputVariableProcessed(
    VariableId processId,
    VariableId variableToProcess,
    int32_t optionalParameter,
    std::unique_ptr<InputVariableInterface>& retInputVar) {
  // to be added

  // to-do: add function, or remove warning for unused params
  if (processId == VariableId::EngineWarnings ||
      variableToProcess == VariableId::EngineWarnings ||
      optionalParameter == 0 || retInputVar->GetPointer() == nullptr) {
  }
}

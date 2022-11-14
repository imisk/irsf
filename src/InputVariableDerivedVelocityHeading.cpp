
#include "InputVariableDerivedVelocityHeading.h"

using namespace irsf;

void InputVariableDerivedVelocityHeading::Init(
    std::vector<InputVariableInterface*> inputVariablesIn) {
  qDebug() << " InputVariableDerivedVelocityHeading::Init";

  for (const auto& var : inputVariablesIn) {
    if (var->GetVariableId() == VariableId::VelocityX) {
      inputX = var->GetPointer();
      qDebug() << "ivdvh: found X";
    }

    if (var->GetVariableId() == VariableId::VelocityY) {
      inputY = var->GetPointer();
      qDebug() << "ivdvh: found Y";
    }
  }

  if (inputX == nullptr || inputY == nullptr) {
    throw IrsfException(
        IrsfError::InputVariableDerivedVelocityHeadingMissingTelemetry);
  }
}

void InputVariableDerivedVelocityHeading::Calculate() {
  /*
   * to-do: velocity heading and other derived variables are to be added in a
   * future version of IRSF
   */

  float value = (*inputX + *inputY) * 2;

  *varPtr = value;
}

std::vector<VariableId>
InputVariableDerivedVelocityHeading::GetRequiredInputVariableRaw()
    const noexcept {
  std::vector<VariableId> ret;

  ret.push_back(VariableId::VelocityX);
  ret.push_back(VariableId::VelocityY);
  ret.push_back(VariableId::VelocityZ);

  return ret;
}

float* InputVariableDerivedVelocityHeading::GetPointer() const noexcept {
  return varPtr.get();
}

VariableId InputVariableDerivedVelocityHeading::GetVariableId() const noexcept {
  return variableId;
}

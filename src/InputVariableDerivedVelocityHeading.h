#ifndef INPUTVARIABLEDERIVEDVELOCITYHEADING_H
#define INPUTVARIABLEDERIVEDVELOCITYHEADING_H

#include "InputVariableDerivedBase.h"
#include "IrsfCommon.h"
#include "QDebug"
namespace irsf {
/*
A derived variable which calculates vehicle heading in 360 degrees

work in progress
*/
class InputVariableDerivedVelocityHeading : public InputVariableDerivedBase {
 public:
  InputVariableDerivedVelocityHeading() = default;

  ~InputVariableDerivedVelocityHeading() override = default;

  InputVariableDerivedVelocityHeading(
      InputVariableDerivedVelocityHeading& other) = delete;

  InputVariableDerivedVelocityHeading& operator=(
      InputVariableDerivedVelocityHeading& other) = delete;

  InputVariableDerivedVelocityHeading(
      InputVariableDerivedVelocityHeading&& other) = default;

  InputVariableDerivedVelocityHeading& operator=(
      InputVariableDerivedVelocityHeading&& other) noexcept = default;

  void Init(std::vector<InputVariableInterface*> inputVariablesIn) override;

  void Calculate() override;

  std::vector<VariableId> GetRequiredInputVariableRaw() const noexcept override;

  void ResetPastValues() override {}

  float* GetPointer() const noexcept override;

  VariableId GetVariableId() const noexcept override;

 private:
  std::vector<InputVariableInterface> varList;

  float* inputX{nullptr};
  float* inputY{nullptr};

  std::unique_ptr<float> varPtr{std::make_unique<float>()};
  VariableId variableId{VariableId::DerivedVelocityHeading};
};
}  // namespace irsf
#endif  // INPUTVARIABLEDERIVEDVELOCITYHEADING_H

#ifndef INPUTVARIABLEDERIVEDBASE_H
#define INPUTVARIABLEDERIVEDBASE_H

#include "InputVariableCalculableInterface.h"
namespace irsf {
/*
 * Base class for all input variables which produce a value by derivation,
 * and are special classess in the program.
 */
class InputVariableDerivedBase : public InputVariableCalculableInterface {
 public:
  InputVariableDerivedBase() = default;

  ~InputVariableDerivedBase() override = default;

  InputVariableDerivedBase(InputVariableDerivedBase& other) = delete;

  InputVariableDerivedBase& operator=(InputVariableDerivedBase& other) = delete;

  InputVariableDerivedBase(InputVariableDerivedBase&& other) noexcept = default;

  InputVariableDerivedBase& operator=(
      InputVariableDerivedBase&& other) noexcept = default;

  // InputVariableInterface interface
 public:
  float* GetPointer() const noexcept override = 0;

  VariableId GetVariableId() const noexcept override = 0;

  // InputVariableCalculableInterface interface
 public:
  void Init(std::vector<InputVariableInterface*> inputVariablesIn) override = 0;

  void Calculate() override = 0;

  std::vector<VariableId> GetRequiredInputVariableRaw()
      const noexcept override = 0;

  void ResetPastValues() override = 0;
};
}  // namespace irsf
#endif  // INPUTVARIABLEDERIVEDBASE_H
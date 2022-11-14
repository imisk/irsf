#ifndef INPUTVARIABLEPROCESSEDBASE_H
#define INPUTVARIABLEPROCESSEDBASE_H

#include "InputVariableCalculableInterface.h"
namespace irsf {

/*
 * Base class for input variables which are produces by processing a certain
 * set of values which will be stored in inputVars.
 */
class InputVariableProcessedBase : public InputVariableCalculableInterface {
 public:
  explicit InputVariableProcessedBase() = default;

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
#endif  // INPUTVARIABLEPROCESSEDBASE_H

#ifndef INPUTVARIABLECALCULABLEINTERFACE_H
#define INPUTVARIABLECALCULABLEINTERFACE_H

#include <vector>
#include "InputVariableInterface.h"
#include "IrsfCommon.h"
namespace irsf {
class InputVariableCalculableInterface : public InputVariableInterface {
 public:
  InputVariableCalculableInterface() = default;
  virtual void Init(std::vector<InputVariableInterface*> inputVariablesIn) = 0;

  virtual void Calculate() = 0;

  virtual std::vector<VariableId> GetRequiredInputVariableRaw()
      const noexcept = 0;

  /* For values which rely on previous ticks to be in order, we
   * need to reset the past values for periods when the calculation
   * restarts in another region of data.
   */
  virtual void ResetPastValues() = 0;
};
}  // namespace irsf
#endif  // INPUTVARIABLECALCULABLEINTERFACE_H

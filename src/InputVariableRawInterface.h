#ifndef INPUTVARIABLERAWINTERFACE_H
#define INPUTVARIABLERAWINTERFACE_H

#include <memory>
#include "InputVariableInterface.h"
namespace irsf {
class InputVariableRawInterface : public InputVariableInterface {
 public:
  virtual void ConvertToFloat() noexcept = 0;
  VariableId GetVariableId() const noexcept override = 0;
};

using iVarRawInterface_sp = std::shared_ptr<InputVariableRawInterface>;
}  // namespace irsf
#endif  // INPUTVARIABLERAWINTERFACE_H

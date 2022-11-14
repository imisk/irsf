#ifndef INPUTVARIABLEINTERFACE_H
#define INPUTVARIABLEINTERFACE_H

#include <memory>
#include "IrsfCommon.h"
namespace irsf {
class InputVariableInterface {
 public:
  InputVariableInterface() = default;
  InputVariableInterface(const InputVariableInterface& other) = default;
  InputVariableInterface(InputVariableInterface&& other) = default;
  InputVariableInterface& operator=(const InputVariableInterface& other) =
      default;
  InputVariableInterface& operator=(InputVariableInterface&& other) = default;
  virtual ~InputVariableInterface() {}

  virtual float* GetPointer() const noexcept = 0;
  virtual VariableId GetVariableId() const noexcept = 0;
};

using iVarInterface_sp = std::shared_ptr<InputVariableInterface>;
}  // namespace irsf
#endif  // INPUTVARIABLEINTERFACE_H

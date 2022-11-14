#ifndef INPUTVARIABLERAW_H
#define INPUTVARIABLERAW_H

#include <memory>

#include "InputVariableRawInterface.h"
#include "IrsfCommon.h"
namespace irsf {
template <typename T>
/*
An input variable which is obtained directly from a single value given by
iRacing SDK. Currently specialises to three data types provided by iRacing which
are float,double and int32_t.
*/
class InputVariableRaw : public InputVariableRawInterface {
 public:
  explicit InputVariableRaw(VariableId id,
                            std::unique_ptr<T> valuePointer) noexcept;

  ~InputVariableRaw() override;

  InputVariableRaw(InputVariableRaw& other) = delete;

  InputVariableRaw& operator=(InputVariableRaw& other) = delete;

  InputVariableRaw(InputVariableRaw&& other) noexcept;

  InputVariableRaw& operator=(InputVariableRaw&& other) noexcept;

  float* GetPointer() const noexcept override;

  VariableId GetVariableId() const noexcept override;

  inline void ConvertToFloat() noexcept override;

 private:
  std::unique_ptr<float> valuePtr;

  std::unique_ptr<T> valuePtrT;

  VariableId varId;
};
}  // namespace irsf
#endif  // INPUTVARIABLERAW_H

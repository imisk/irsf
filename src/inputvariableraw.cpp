
#include "InputVariableRaw.h"
#include "QDebug"

using namespace irsf;

template <>
InputVariableRaw<float>::InputVariableRaw(
    VariableId id,
    std::unique_ptr<float> valuePointer) noexcept
    : valuePtr(std::move(valuePointer)), varId(id) {}

template <typename T>
InputVariableRaw<T>::InputVariableRaw(InputVariableRaw&& other) noexcept {
  varId = other.varId;
  valuePtrT = std::move(other.valuePtrT);
  valuePtr = std::move(other.valuePtr);
  other.valuePtrT = nullptr;
  other.valuePtr = nullptr;
  other.varId = VariableId::VariableUnknown;
}

template <typename T>
InputVariableRaw<T>& InputVariableRaw<T>::operator=(
    InputVariableRaw<T>&& other) noexcept {
  varId = other.varId;
  valuePtrT = std::move(other.valuePtrT);
  valuePtr = std::move(other.valuePtr);
  other.valuePtrT = nullptr;
  other.valuePtr = nullptr;
  other.varId = VariableId::VariableUnknown;

  return *this;
}

template <>
InputVariableRaw<double>::InputVariableRaw(
    VariableId id,
    std::unique_ptr<double> valuePointer) noexcept {
  valuePtrT = std::move(valuePointer);
  valuePtr = std::make_unique<float>();
  *valuePtr = 0;
  varId = id;
}

template <>
InputVariableRaw<int32_t>::InputVariableRaw(
    VariableId id,
    std::unique_ptr<int32_t> valuePointer) noexcept {
  valuePtrT = std::move(valuePointer);
  valuePtr = std::make_unique<float>();
  *valuePtr = 0;
  varId = id;
}

template <>
InputVariableRaw<float>::~InputVariableRaw() {}

template <typename T>
InputVariableRaw<T>::~InputVariableRaw() {
  valuePtr = nullptr;
}

template <typename T>
float* InputVariableRaw<T>::GetPointer() const noexcept {
  return valuePtr.get();
}

template <typename T>
VariableId InputVariableRaw<T>::GetVariableId() const noexcept {
  return varId;
}

template <typename T>
void InputVariableRaw<T>::ConvertToFloat() noexcept {
  if (valuePtrT == nullptr) {
    qDebug() << "T == nullptr";
  } else {
    *valuePtr = static_cast<float>(*valuePtrT);
  }
}

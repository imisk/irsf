
#include "InputVariableProcessedAverage.h"

using namespace irsf;

InputVariableProcessedAverage::InputVariableProcessedAverage(
    size_t inAveragePeriod,
    VariableId inVariableIdToProcess) noexcept
    : averagePeriod(inAveragePeriod),
      averagePeriodFloat(static_cast<float>(averagePeriod)),
      variableIdToProcess(inVariableIdToProcess) {}

void InputVariableProcessedAverage::Calculate() {
  // return measuredValue until enough elements are in queue

  valuesToAverage.push(*measuredValue);

  valuesToAverageTotal += *measuredValue;

  // front is oldest, back is newest
  if (valuesToAverage.size() > averagePeriod) {
    valuesToAverageTotal -= valuesToAverage.front();
    valuesToAverage.pop();

    *varPtr = valuesToAverageTotal / averagePeriodFloat;

  } else {
    *varPtr = *measuredValue;
  }
}

void InputVariableProcessedAverage::Init(
    std::vector<InputVariableInterface*> inputVariablesIn) {
  qDebug() << " InputVariableProcessedAverage::Init ";
  if (inputVariablesIn.size() == 0)
    throw IrsfException(IrsfError::MissingInputVariable);

  inputVars.push_back(inputVariablesIn[0]);

  measuredValue = inputVariablesIn[0]->GetPointer();

  qDebug() << " InputVariableProcessedAverage::Init == OK";
}

void InputVariableProcessedAverage::ResetPastValues() {
  while (!valuesToAverage.empty()) {
    valuesToAverage.pop();
  }
  valuesToAverageTotal = 0.0f;
}

float* InputVariableProcessedAverage::GetPointer() const noexcept {
  return varPtr.get();
}

VariableId InputVariableProcessedAverage::GetVariableId() const noexcept {
  return variableId;
}

std::vector<VariableId>
InputVariableProcessedAverage::GetRequiredInputVariableRaw() const noexcept {
  std::vector<VariableId> retList;

  retList.push_back(variableIdToProcess);

  return retList;
}

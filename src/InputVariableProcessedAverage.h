#ifndef INPUTVARIABLEPROCESSEDDELTA_H
#define INPUTVARIABLEPROCESSEDDELTA_H

#include <queue>
#include "InputVariableProcessedBase.h"
#include "IrsfCommon.h"
#include "QDebug"
namespace irsf {
/*
 * Input variable which processes several values in a row to produce an average
 * value
 */

class InputVariableProcessedAverage : public InputVariableProcessedBase {
 public:
  explicit InputVariableProcessedAverage(
      size_t inAveragePeriod,
      VariableId inVariableIdToProcess) noexcept;

  // InputVariableCalculableInterface interface
 public:
  void Calculate() override;
  void Init(std::vector<InputVariableInterface*> inputVariablesIn) override;
  void ResetPastValues() override;

  float* GetPointer() const noexcept override;

  VariableId GetVariableId() const noexcept override;

  std::vector<VariableId> GetRequiredInputVariableRaw() const noexcept override;

 private:
  // how many ticks to average the value over
  size_t averagePeriod;
  float averagePeriodFloat;
  float* measuredValue{nullptr};
  std::queue<float> valuesToAverage;
  float valuesToAverageTotal{0.0f};

 private:
  std::vector<InputVariableInterface*> inputVars;
  std::unique_ptr<float> varPtr;
  VariableId variableId{VariableId::ProcessedAverage};

 private:
  VariableId variableIdToProcess;
};
}  // namespace irsf
#endif  // INPUTVARIABLEPROCESSEDDELTA_H

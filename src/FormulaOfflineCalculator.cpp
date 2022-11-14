
#include "FormulaOfflineCalculator.h"
#include "InputVariableRaw.h"

using namespace irsf;

FormulaOfflineCalculator::FormulaOfflineCalculator(
    FormulaDbManager* fdm,
    FormulaEvaluator* eval) noexcept
    : formulaDbManager(fdm), formulaEvaluator(eval) {}

void FormulaOfflineCalculator::CalculateFormulaForRangeOneLap(
    TelemetryData* telemetry,
    IrsfSignal* signal,
    float distanceStart,
    float distanceEnd,
    int32_t lap,
    std::vector<TelemetryChartDataPoint>& retValues) {
  telemetryData = telemetry;

  //-------------------------------------- get list of required variables

  auto formula = formulaDbManager->GetFormulaWithName(signal->formulaName);

  if (formula == nullptr)
    throw IrsfException(IrsfError::FormulaNotFound);

  formulaEvaluator->InfixToPostfix(formula->GetCurrentFormulaInfix(),
                                   formulaPostfixBase);

  for (auto& operand : formula->operandsInList) {
    variableIds.insert(operand.GetVariableId());
  }

  //------------------ create inputVariables

  InitVariablesOffline();

  //------------------- loop

  auto retEvalVal = std::make_unique<float>();
  *retEvalVal = 0.0f;

  for (const auto& lapInfo : telemetry->LapIndex) {
    int32_t currentLapNumber = lapInfo.first;

    if (currentLapNumber == lap) {
      // we are on our lap
      size_t currentLapIdx = lapInfo.second;

      size_t offsetFirstElement = telemetry->Variables.size();

      if (telemetryData->Data[currentLapIdx].size() > offsetFirstElement * 2) {
        bool finished = false;
        while (!finished) {
          float dist =
              telemetryData
                  ->Data[currentLapIdx][offsetFirstElement + offsetLapDistance];

          if (dist >= distanceStart && dist <= distanceEnd) {
            // update simualted values
            for (auto& simVal : simulatedValues) {
              *simVal->simulatedValue =
                  telemetryData->Data[currentLapIdx][offsetFirstElement +
                                                     simVal->indexInTelemetry];
            }

            // then calculate the formula
            formulaEvaluator->EvaluateFormula(formulaPostfixEvaluated_p,
                                              retEvalVal.get());

            retValues.push_back({*retEvalVal, dist});
          }

          offsetFirstElement += telemetry->Variables.size();  // * 50;

          if (offsetFirstElement >= telemetryData->Data[currentLapIdx].size()) {
            finished = true;
          }
        }
      } else {
        throw IrsfException(IrsfError::NoValuesInSelectedTelemetryRange);
      }
    }
  }
}

void FormulaOfflineCalculator::InitVariablesOffline() {
  for (const auto& varId : variableIds) {
    auto newSimValue = std::make_unique<SimulatedLiveVariable>();

    bool found = false;
    bool lapDistFound = false;
    for (size_t i = 0; i < telemetryData->Variables.size(); i++) {
      if (telemetryData->Variables[i] == varId) {
        found = true;
        newSimValue->indexInTelemetry = i;
      }

      if (telemetryData->Variables[i] == VariableId::LapDist) {
        lapDistFound = true;
        offsetLapDistance = i;
      }
    }

    if (found == false) {
      throw IrsfException(IrsfError::TelemetryDoesNotContainRequiredVariableId);
    }

    if (lapDistFound == false) {
      throw IrsfException(IrsfError::LapDistanceVariableMissing);
    }

    auto newSimulatedValue = std::make_unique<float>();

    newSimValue->simulatedValue = newSimulatedValue.get();

    simulatedValues.push_back(std::move(newSimValue));

    auto ivr = std::make_shared<InputVariableRaw<float>>(
        varId, std::move(newSimulatedValue));

    inputVariables.push_back(ivr);
  }

  formulaEvaluator->CreateFormulaEvaluatedValues(
      inputVariables, formulaPostfixBase, formulaPostfixEvaluated,
      formulaPostfixEvaluated_p);
}

#include "DerivedTelemetryDataOfflineCalculator.h"
namespace irsf {

DerivedTelemetryDataOfflineCalculator::DerivedTelemetryDataOfflineCalculator() {
}

IrsfError
DerivedTelemetryDataOfflineCalculator::CalculateInputVariableDerivedOffline(
    TelemetryData* telemetry,
    InputVariableCalculableInterface* derived,
    std::vector<std::vector<float>>* retData) {
  if (retData == nullptr)
    return IrsfError::InvalidPointer;

  qDebug() << "CalculateInputVariableDerivedOffline()";

  calculationTelemetry = telemetry;
  calculationInputVarDerived = derived;
  calculationRetData = retData;

  InitializeInputVariableRawSimulation();

  qDebug() << "Laps found = " << calculationTelemetry->Data.size();

  for (size_t curLap = 0; curLap < calculationTelemetry->Data.size();
       curLap++) {
    CalculateInputVariableDerivedForOneLap(curLap);
  }

  return IrsfError::OK;
}

void DerivedTelemetryDataOfflineCalculator::
    InitializeInputVariableRawSimulation() {
  // Create the simulated InputVariableRaw<float> for the Derived variable

  std::vector<VariableId> requiredVariables =
      calculationInputVarDerived->GetRequiredInputVariableRaw();

  std::vector<InputVariableInterface*> derivedInputs;

  for (VariableId curVarId : requiredVariables) {
    bool varIdFound = false;

    for (size_t i = 0; i < calculationTelemetry->Variables.size(); i++) {
      if (calculationTelemetry->Variables[i] == curVarId) {
        varIdFound = true;

        qDebug() << "--- variableId found in telemetry";

        auto ivrValue = std::make_unique<float>();

        auto ivr = std::make_unique<InputVariableRaw<float>>(
            curVarId, std::move(ivrValue));

        InputVariableRawSimulated.push_back(std::move(ivr));
        InputVariableRawSimulatedOffset.push_back(i);

        derivedInputs.push_back(ivr.get());
      }
    }

    if (!varIdFound) {
      qDebug() << "--- variableId NOT found in telemetry **************";
      throw IrsfException(IrsfError::TelemetryDoesNotContainRequiredVariableId);
    }
  }

  qDebug() << "InputVariableRawSimulated.size = "
           << InputVariableRawSimulated.size();

  /*
   * here the Calculable variable gets the required Float* and figures out
   * how to later use them on each tick update
   */
  calculationInputVarDerived->Init(derivedInputs);
}

void DerivedTelemetryDataOfflineCalculator::
    CalculateInputVariableDerivedForOneLap(size_t lapIndex) {
  std::vector<float> valuesThisLap;

  std::vector<std::vector<float>> retData = *calculationRetData;

  retData.push_back(std::vector<float>());

  auto derivedValuePtr = calculationInputVarDerived->GetPointer();

  /*
   * to be considered: maybe this should be optional? we maybe dont want to
   * reset
   * AVG values at start/finish line ? maybe we should only call
   * ResetPastValues
   * on entering a new track section after a value wasn't being calculated for
   * a while...
   */
  calculationInputVarDerived->ResetPastValues();

  size_t tickCountThisLap = calculationTelemetry->Data[lapIndex].size() /
                            calculationTelemetry->Variables.size();

  qDebug() << "tickCountThisLap = " << tickCountThisLap;

  // go through each tick of telemetry
  for (size_t currentTick = 0; currentTick < tickCountThisLap; currentTick++) {
    size_t telemetryCurrentTickIndex0 = 0;

    telemetryCurrentTickIndex0 =
        currentTick * calculationTelemetry->Variables.size();

    // set the values at the required pointers
    for (size_t inputVarIndex = 0;
         inputVarIndex < InputVariableRawSimulated.size(); inputVarIndex++) {
      auto inputVar = InputVariableRawSimulated[inputVarIndex].get();

      auto valuePtr = inputVar->GetPointer();

      size_t telemetryCurrentTickIndexVar =
          telemetryCurrentTickIndex0 +
          InputVariableRawSimulatedOffset[inputVarIndex];

      float dataFromTelemetry =
          calculationTelemetry->Data[lapIndex][telemetryCurrentTickIndexVar];

      *valuePtr = dataFromTelemetry;
    }

    calculationInputVarDerived->Calculate();

    valuesThisLap.push_back(*derivedValuePtr);
  }

  retData.push_back(valuesThisLap);

  calculationRetData->push_back(valuesThisLap);
}
}  // namespace irsf

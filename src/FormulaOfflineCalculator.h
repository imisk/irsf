#ifndef FORMULAOFFLINECALCULATOR_H
#define FORMULAOFFLINECALCULATOR_H

#include <set>
#include "FormulaDbManager.h"
#include "FormulaEvaluator.h"
#include "IrsfCommon.h"
namespace irsf {
struct SimulatedLiveVariable {
  float* simulatedValue;

  // Index/offset within telemetryData->Variables and each lap data
  size_t indexInTelemetry;
};

/*
 * Calculates formula (signal) offline, based on saved telemetry data.
 */
class FormulaOfflineCalculator {
 public:
  explicit FormulaOfflineCalculator(FormulaDbManager* fdm,
                                    FormulaEvaluator* eval) noexcept;

  /*
   * Calculate the values for the given signal and distance range,
   * for the given lap.
   *
   * @param retValues The returned values are calculated and placed
   * in this vector
   * */
  void CalculateFormulaForRangeOneLap(
      TelemetryData* telemetry,
      IrsfSignal* signal,
      float distanceStart,
      float distanceEnd,
      int32_t lap,
      std::vector<TelemetryChartDataPoint>& retValues);

 private:
  FormulaDbManager* formulaDbManager;

  
  //Populate vector inputVariables, init simulatedValues  
  void InitVariablesOffline();

  // We create input variables for offline tracking
  std::vector<iVarInterface_sp> inputVariables; 

  /*
   * Simulated values, updated once per tick. The indices here are a match of
   * inputVariables
   */
  std::vector<std::unique_ptr<SimulatedLiveVariable>> simulatedValues;

  std::set<VariableId> variableIds;

  TelemetryData* telemetryData{nullptr};

  /*
   * Index of LapDistance in data (equals to offset)
   */
  size_t offsetLapDistance{0};

  FormulaEvaluator* formulaEvaluator;

  std::vector<FormulaSymbolBase*> formulaPostfixBase;
  std::vector<SymbEvaluated> formulaPostfixEvaluated;
  std::vector<FormulaSymbolEvaluated*> formulaPostfixEvaluated_p;
};
}  // namespace irsf //
#endif  // FORMULAOFFLINECALCULATOR_H

#ifndef DERIVEDTELEMETRYDATAOFFLINECALCULATOR_H
#define DERIVEDTELEMETRYDATAOFFLINECALCULATOR_H

#include "InputVariableCalculableInterface.h"
#include "InputVariableRaw.h"
#include "QDebug"
namespace irsf {

struct TelemetryData;

/*
 * Calculates derived values (input variable derived) based on pre-recorded
 * telemetry from files on disk.
 */
class DerivedTelemetryDataOfflineCalculator {
 public:
  explicit DerivedTelemetryDataOfflineCalculator();

  /*
   *Use the derived formula on telemetry data to calculate retData
   * The return value retData has the same 1-d format as telemetry.
   * Data, but only for 1 value (the derived one being calculated here)
   */
  IrsfError CalculateInputVariableDerivedOffline(
      TelemetryData* telemetry,
      InputVariableCalculableInterface* derived,
      std::vector<std::vector<float>>* retData);

 private:
  void InitializeInputVariableRawSimulation();

  /*
  Calls Calculate() on calculationInputVarDerived for each tick of the given
  lap lapIndex and stores all values in calculationRetData in sequential order
  */
  void CalculateInputVariableDerivedForOneLap(size_t lapIndex);

  TelemetryData* calculationTelemetry{nullptr};
  InputVariableCalculableInterface* calculationInputVarDerived{nullptr};
  std::vector<std::vector<float>>* calculationRetData{nullptr};

  /* This is the offset of each InputVariableRaw in the
   * InputVariableRawSimulated vector in the telemetry
   * data which is currently being read for calculating
   * the derived value. The values can range from 0 to
   * telemetry.Variables.size().
   */
  std::vector<size_t> InputVariableRawSimulatedOffset;

  /*
   * Only float type because telemetry saves data all as Float
   */
  std::vector<std::unique_ptr<InputVariableRaw<float>>>
      InputVariableRawSimulated;
};

}  // namespace irsf
#endif  // DERIVEDTELEMETRYDATAOFFLINECALCULATION_H

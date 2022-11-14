#ifndef TELEMETRYVIEWERMANAGER_H
#define TELEMETRYVIEWERMANAGER_H

#include "WindowTelemetryView.h"

#include "IrsfCommon.h"
#include "QString"
#include "TelemetryDiskReader.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <vector>
namespace irsf {
/*
This class manages the currently viewed telemetry, it is a manager class
for the telemetry viewer window.
Hold the chart pointer, current chart descriptions, etc
*/
class TelemetryViewerManager {
 public:
  TelemetryViewerManager();

  void SetActiveTelemetryFile(const QString& fileName);

  void UpdateChart(TelemetryViewerOptionsForChart& options);

  /*
   * Find what is the maximum value of Distance in the active
   * telemetry data.
   */
  float MaximumDistanceActiveData() const noexcept;

  std::vector<QBrush> listboxVariableIdColours;

  TelemetryData* GetActiveData() const noexcept;

 private:
  std::unique_ptr<TelemetryData> activeData;

  std::unique_ptr<TelemetryDiskReader> telemetryDiskReader{
      std::make_unique<TelemetryDiskReader>()};

  std::unique_ptr<WindowTelemetryView> winTelView{
      std::make_unique<WindowTelemetryView>()};

  QChart mainChart;

  QChartView mainChartView;

  float maximumDistanceActiveData{0.0f};
};
}  // namespace irsf
#endif  // TELEMETRYVIEWERMANAGER_H

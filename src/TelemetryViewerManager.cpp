
#include "TelemetryViewerManager.h"
#include "Utilities.h"

using namespace irsf;

TelemetryViewerManager::TelemetryViewerManager() : mainChartView(&mainChart) {
  mainChartView.setRenderHint(QPainter::Antialiasing);

  winTelView->SetChart(&mainChartView);

  activeData = std::make_unique<TelemetryData>();

  listboxVariableIdColours.push_back(Qt::red);
  listboxVariableIdColours.push_back(Qt::blue);
  listboxVariableIdColours.push_back(Qt::green);
  listboxVariableIdColours.push_back(Qt::black);
  listboxVariableIdColours.push_back(Qt::cyan);
  listboxVariableIdColours.push_back(Qt::magenta);
  listboxVariableIdColours.push_back(Qt::darkRed);
  listboxVariableIdColours.push_back(Qt::gray);
}

void TelemetryViewerManager::SetActiveTelemetryFile(const QString& fileName) {
  telemetryDiskReader->LoadTelemetryFromFile(fileName.toStdString(),
                                             activeData.get());

  FindMaxValueOfVariable(activeData.get(), VariableId::LapDist,
                         maximumDistanceActiveData);
}

void TelemetryViewerManager::UpdateChart(
    TelemetryViewerOptionsForChart& options) {
  mainChart.removeAllSeries();

  CreateDataSeriesFromTelemetry(options, &mainChart, activeData.get(),
                                listboxVariableIdColours);

  winTelView->show();
}

float TelemetryViewerManager::MaximumDistanceActiveData() const noexcept {
  return maximumDistanceActiveData;
}

TelemetryData* TelemetryViewerManager::GetActiveData() const noexcept {
  return activeData.get();
}

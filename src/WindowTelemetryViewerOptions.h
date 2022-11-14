#ifndef TELEMETRYVIEWEROPTIONS_H
#define TELEMETRYVIEWEROPTIONS_H

#include <QDialog>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "IrsfCommon.h"
#include "TelemetryViewerManager.h"

namespace Ui {
class WindowTelemetryViewerOptions;
}

class WindowTelemetryViewerOptions final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowTelemetryViewerOptions(QWidget* parent = nullptr);
  ~WindowTelemetryViewerOptions() final;

  irsf::IrsfError Init();

 private slots:
  void on_btn_ShowChart_clicked();

  void on_btn_LoadTelemetry_clicked();

  void on_btn_AddVariable_clicked();

  void on_btn_DistanceMax_clicked();

  void on_btn_DistanceZoomOut_clicked();

  void on_btn_DistanceZoomIn_clicked();

  void on_btn_DistanceLeft_clicked();

  void on_btn_DistanceRight_clicked();

  void on_btn_ClearVariables_clicked();

 private:
  /*
   * Create a TelemetryViewerOptionsForChart object based on
   * the selections in this window.
   */
  void CreateOptionsFromSelection();

  void GetDistanceValuesFromInput(float& distanceStart, float& distanceEnd);

  void ApplyChartMovement(irsf::WindowTelemetryViewerOptionsMoveAction action);

  Ui::WindowTelemetryViewerOptions* ui;

  std::unique_ptr<irsf::TelemetryViewerManager> mngr;

  irsf::TelemetryViewerOptionsForChart options;

  static constexpr float kZoomFactor = 0.1f;
  static constexpr float kMoveFactor = 0.05f;
  static constexpr size_t kMaxVariablesPerChart = 8;

  size_t currentListboxVariableIdCount;
};

#endif  // TELEMETRYVIEWEROPTIONS_H

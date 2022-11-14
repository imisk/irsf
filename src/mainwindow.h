#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CoreContext.h"
#include "WindowBrakeMarkerEditor.h"
#include "WindowConfig.h"
#include "WindowFormulaEditor.h"
#include "WindowLive.h"
#include "WindowSignalEditor.h"
#include "WindowSignalSetEditor.h"
#include "WindowTelemetryViewerOptions.h"
#include "WindowTrackListEditor.h"
#include "WindowTrackSectorEditor.h"
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void Init();

 public slots:

  void handleResultsRecordTelemetry(int32_t re);

 private slots:

  void on_btn_TelemetryViewer_clicked();

  void on_btn_FormulaEditor_clicked();

  void on_btn_TrackListEditor_clicked();

  void on_btn_SignalEditor_clicked();

  void on_btn_TsEditor_clicked();

  void on_btn_Live_clicked();

  void on_btn_SignalSetEditor_clicked();

  void on_btn_BrakeMarkerEditor_clicked();

  void on_btn_Config_clicked();

 private:
  void InitWindows();

  Ui::MainWindow* ui;

  irsf::Worker* BrakingPointsWorker{nullptr};

  // Windows:
  std::unique_ptr<WindowLive> windowLive;
  std::unique_ptr<WindowSignalEditor> windowSignalEditor;
  std::unique_ptr<WindowFormulaEditor> windowFormulaEditor;
  std::unique_ptr<WindowTelemetryViewerOptions> windowTelemetryViewerOptions;
  std::unique_ptr<WindowTrackListEditor> windowTrackListEditor;
  std::unique_ptr<WindowTrackSectorEditor> windowTrackSectorEditor;
  std::unique_ptr<WindowSignalSetEditor> windowSignalSetEditor;
  std::unique_ptr<WindowBrakeMarkerEditor> windowBrakeMarkerEditor;
  std::unique_ptr<WindowConfig> windowConfig;

  std::unique_ptr<irsf::CoreContext> core;
};
#endif  // MAINWINDOW_H

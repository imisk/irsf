
#include "mainwindow.h"
#include <stdio.h>
#include <string.h>
#include <QString>
#include <QThread>
#include "ErrorMessageBoxUtility.h"

#include "ui_mainwindow.h"

using namespace irsf;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::Init() {
  core = std::make_unique<CoreContext>();

  try {
    core->Initialize();

    InitWindows();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void MainWindow::handleResultsRecordTelemetry(int32_t re) {
  Q_UNUSED(re)
}

void MainWindow::on_btn_TelemetryViewer_clicked() {
  windowTelemetryViewerOptions->show();
}

void MainWindow::on_btn_FormulaEditor_clicked() {
  windowFormulaEditor->show();
}

void MainWindow::on_btn_TrackListEditor_clicked() {
  windowTrackListEditor->show();

  try {
    windowTrackListEditor->SetModeSelectionOnly(false);
    windowTrackListEditor->RefreshWindow();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void MainWindow::on_btn_SignalEditor_clicked() {
  windowSignalEditor->show();
}

void MainWindow::on_btn_TsEditor_clicked() {
  windowTrackSectorEditor->EnableSelectionOnlyMode(false);
  windowTrackSectorEditor->show();
}

void MainWindow::on_btn_Live_clicked() {
  windowLive->show();
  windowLive->RefreshWindow();
}

void MainWindow::on_btn_SignalSetEditor_clicked() {
  windowSignalSetEditor->SetMode(false);
  windowSignalSetEditor->show();
}

void MainWindow::InitWindows() {
  windowLive = std::make_unique<WindowLive>(
      core->GetTrackDataManager(), core->GetFormulaDbManager(),
      core->GetSignalDbManager(), core->GetAppDbManager());

  windowSignalEditor = std::make_unique<WindowSignalEditor>(
      core->GetTrackDataManager(), core->GetFormulaDbManager(),
      core->GetSignalDbManager(), core->GetAppDbManager());

  windowSignalEditor->Init();

  windowFormulaEditor =
      std::make_unique<WindowFormulaEditor>(core->GetFormulaDbManager());
  windowFormulaEditor->Init();

  windowTelemetryViewerOptions =
      std::make_unique<WindowTelemetryViewerOptions>();
  windowTelemetryViewerOptions->Init();

  windowTrackListEditor =
      std::make_unique<WindowTrackListEditor>(core->GetTrackDataManager());

  windowTrackSectorEditor =
      std::make_unique<WindowTrackSectorEditor>(core->GetTrackDataManager());

  windowSignalSetEditor = std::make_unique<WindowSignalSetEditor>(
      core->GetSignalDbManager(), core->GetTrackDataManager());

  windowSignalSetEditor->Init();

  windowBrakeMarkerEditor = std::make_unique<WindowBrakeMarkerEditor>(
      core->GetAppDbManager(), core->GetTrackDataManager());

  windowBrakeMarkerEditor->Init();

  windowConfig = std::make_unique<WindowConfig>(
      core->GetAppDbManager()->GetAppConfig(), core->GetAppDbManager());

  windowConfig->Init();
}

void MainWindow::on_btn_BrakeMarkerEditor_clicked() {
  windowBrakeMarkerEditor->show();
}

void MainWindow::on_btn_Config_clicked() {
  windowConfig->show();
}

// todo - list of all todos to be done at a later date
/*

- App should be distributed with base versions of all .idb files. If the user
corrupts their files, they have to reinstall the app. So we don't need functions
to create default .idb files.

- Decide on default file names for brake marker .wav files, such as marker.wav
and premarker.wav, and place those names under  void
AppDbManager::ResetAppConfigToDefault(). They should be placed in the default
directory such as /SOUNDS/

- perform a test: create a track sector which starts before pit entry and ends
after pit entry. apply steering wheel sound to it. test to see if the sound will
stop when you enter the pits. the goal is to test the StopAllActiveEvents() call
when entering pits

-  WindowSignalEditor::RefreshWindowCurveIcons() paths should be relative and
not absolute, so you also need to copy the graphical resources to local folders
*/

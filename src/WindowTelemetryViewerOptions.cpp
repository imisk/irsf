
#include "WindowTelemetryViewerOptions.h"
#include <vector>
#include "ErrorMessageBoxUtility.h"
#include "QDebug"
#include "QFileDialog"
#include "Utilities.h"
#include "ui_WindowTelemetryViewerOptions.h"

using namespace irsf;

WindowTelemetryViewerOptions::WindowTelemetryViewerOptions(QWidget* parent)
    : QDialog(parent), ui(new Ui::WindowTelemetryViewerOptions) {
  ui->setupUi(this);
}

WindowTelemetryViewerOptions::~WindowTelemetryViewerOptions() {
  delete ui;
}

IrsfError WindowTelemetryViewerOptions::Init() {
  mngr = std::make_unique<TelemetryViewerManager>();

  std::vector<std::string> varNames = GetNamesOfAllInputVariableRawAndDerived();

  for (const auto& v : varNames) {
    ui->cb_AddVariable->addItem(QString(v.c_str()));
  }

  currentListboxVariableIdCount = 0;

  return IrsfError::OK;
}

void WindowTelemetryViewerOptions::on_btn_ShowChart_clicked() {
  try {
    CreateOptionsFromSelection();

    mngr->UpdateChart(options);

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::on_btn_LoadTelemetry_clicked() {
  try {
    ui->lbl_CurrentTelemetryFilename->setText("None");

    QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open Telemetry File"), "",
                                     tr("IRSF Telemetry Recording (*.itr)"));

    if (fileName == "")
      return;

    mngr->SetActiveTelemetryFile(fileName);

    ui->lbl_CurrentTelemetryFilename->setText(fileName);

    // update list of variables to only include those from the telemetry
    ui->cb_AddVariable->clear();

    for (const auto& varId : mngr->GetActiveData()->Variables) {
      std::string varIdText = GetVariableNameFromVariableId(varId);

      ui->cb_AddVariable->addItem(QString(varIdText.c_str()));
    }

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::on_btn_AddVariable_clicked() {
  try {
    if (currentListboxVariableIdCount >= kMaxVariablesPerChart)
      throw IrsfException(
          IrsfError::CannotAddAnyMoreVariableToTelemetryChartView);

    QString selectedVar = ui->cb_AddVariable->currentText();

    QListWidgetItem* pItem = new QListWidgetItem(selectedVar);
    pItem->setForeground(
        mngr->listboxVariableIdColours[currentListboxVariableIdCount]);

    // check that variable isn't already in the list
    bool exists = false;
    for (int32_t i = 0; i < ui->lb_VariablesOnChart->count(); i++) {
      QString itm = ui->lb_VariablesOnChart->item(i)->text();

      if (itm == selectedVar)
        exists = true;
    }

    if (!exists) {
      ui->lb_VariablesOnChart->addItem(pItem);

      currentListboxVariableIdCount++;
    }

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::on_btn_DistanceMax_clicked() {
  try {
    int32_t distMax = static_cast<int32_t>(mngr->MaximumDistanceActiveData());
    ui->le_DistanceEnd->setText(QString::number(distMax));

    ui->le_DistanceStart->setText("0");

    CreateOptionsFromSelection();

    mngr->UpdateChart(options);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::CreateOptionsFromSelection() {
  // Laps
  if (ui->cb_Laps_AllLaps->checkState() == Qt::CheckState::Checked) {
    options.ShowAllLaps = true;
  } else {
    QString lapStr = ui->le_Laps->text();

    CreateIntListFromCommaDelimitedText(options.lapList, lapStr);
  }

  // Variables
  options.variableList.clear();
  for (int32_t i = 0; i < ui->lb_VariablesOnChart->count(); i++) {
    QString itm = ui->lb_VariablesOnChart->item(i)->text();

    VariableId varId = GetVariableIdFromVariableName(itm.toStdString());

    if (varId != VariableId::VariableUnknown)
      options.variableList.push_back(varId);
  }

  if (options.variableList.size() == 0)
    throw IrsfException(IrsfError::NoVariablesSelectedForTelemetry);

  // Distance
  GetDistanceValuesFromInput(options.DistanceStart, options.DistanceEnd);
}

void WindowTelemetryViewerOptions::GetDistanceValuesFromInput(
    float& distanceStart,
    float& distanceEnd) {
  std::string distMinText = ui->le_DistanceStart->text().toStdString();
  std::string distMaxText = ui->le_DistanceEnd->text().toStdString();

  int32_t distMin = -1;
  int32_t distMax = -1;

  try {
    distMin = std::stoi(distMinText);
    distMax = std::stoi(distMaxText);
  } catch (...) {
    throw IrsfException(IrsfError::InvalidDistanceValuesForTelemetry);
  }

  if (distMin == -1 || distMax == -1)
    throw IrsfException(IrsfError::InvalidDistanceValuesForTelemetry);

  if (distMax <= distMin)
    throw IrsfException(IrsfError::InvalidDistanceValuesForTelemetry);

  if (distMin < 0) {
    distMin = 0;
    ui->le_DistanceStart->setText(QString::number(distMin));
  }

  if (static_cast<float>(distMax) > mngr->MaximumDistanceActiveData()) {
    distMax = static_cast<int32_t>(mngr->MaximumDistanceActiveData());
    ui->le_DistanceEnd->setText(QString::number(distMax));
  }

  distanceStart = static_cast<float>(distMin);
  distanceEnd = static_cast<float>(distMax);
}

void WindowTelemetryViewerOptions::ApplyChartMovement(
    WindowTelemetryViewerOptionsMoveAction action) {
  float newStart;
  float newEnd;

  GetDistanceValuesFromInput(newStart, newEnd);

  float totalDistance = newEnd - newStart;

  float distanceDelta = 0.0f;

  switch (action) {
    case WindowTelemetryViewerOptionsMoveAction::ZoomIn:

      distanceDelta = kZoomFactor * totalDistance;

      newStart += distanceDelta / 2;
      newEnd -= distanceDelta / 2;

      break;

    case WindowTelemetryViewerOptionsMoveAction::ZoomOut:

      distanceDelta = kZoomFactor * totalDistance;

      newStart -= distanceDelta / 2;
      newEnd += distanceDelta / 2;

      if (newStart < 0)
        newStart = 0;

      if (newEnd > mngr->MaximumDistanceActiveData())
        newEnd = mngr->MaximumDistanceActiveData();

      break;

    case WindowTelemetryViewerOptionsMoveAction::MoveLeft:

      distanceDelta = kMoveFactor * totalDistance;

      newStart -= distanceDelta;

      if (newStart < 0)
        newStart = 0;

      newEnd = newStart + totalDistance;

      break;

    case WindowTelemetryViewerOptionsMoveAction::MoveRight:

      distanceDelta = kMoveFactor * totalDistance;

      newEnd += distanceDelta;

      if (newEnd > mngr->MaximumDistanceActiveData())
        newEnd = mngr->MaximumDistanceActiveData();

      newStart = newEnd - totalDistance;

      break;

    case WindowTelemetryViewerOptionsMoveAction::Unknown:

      break;
  }

  ui->le_DistanceStart->setText(QString::number(static_cast<double>(newStart)));
  ui->le_DistanceEnd->setText(QString::number(static_cast<double>(newEnd)));

  CreateOptionsFromSelection();

  mngr->UpdateChart(options);
}

void WindowTelemetryViewerOptions::on_btn_DistanceZoomOut_clicked() {
  try {
    ApplyChartMovement(WindowTelemetryViewerOptionsMoveAction::ZoomOut);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::on_btn_DistanceZoomIn_clicked() {
  try {
    ApplyChartMovement(WindowTelemetryViewerOptionsMoveAction::ZoomIn);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::on_btn_DistanceLeft_clicked() {
  try {
    ApplyChartMovement(WindowTelemetryViewerOptionsMoveAction::MoveLeft);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::on_btn_DistanceRight_clicked() {
  try {
    ApplyChartMovement(WindowTelemetryViewerOptionsMoveAction::MoveRight);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTelemetryViewerOptions::on_btn_ClearVariables_clicked() {
  ui->lb_VariablesOnChart->clear();
  currentListboxVariableIdCount = 0;
}

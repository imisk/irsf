#include "WindowConfig.h"
#include "ErrorMessageBoxUtility.h"
#include "Utilities.h"
#include "ui_WindowConfig.h"

using namespace irsf;

WindowConfig::WindowConfig(AppConfig* ac, AppDbManager* adb, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::WindowConfig),
      appConfig(ac),
      appDbManager(adb) {
  ui->setupUi(this);
}

WindowConfig::~WindowConfig() {
  delete ui;
}

void WindowConfig::Init() {
  RefreshWindow();
}

void WindowConfig::on_btn_TelRemove_clicked() {
  try {
    std::cout << "Removing variable: " << telemetryItem_selected << std::endl;

    if (telemetryItem_selected == "Lap") {
      ShowMessageBox(
          "Error: cannot remove Lap variable, it is required for "
          "telemetry recording to function properly. \n");
      return;
    }

    VariableId id = GetVariableIdFromVariableName(telemetryItem_selected);

    if (id == VariableId::VariableUnknown) {
      ShowMessageBox("Error: unrecognized variable selected \n");
      return;
    }

    appDbManager->DeleteVariableIdFromTelemetryRecording(id);

    RefreshWindow();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowConfig::RefreshWindow() {
  auto telemetryVars = GetNamesOfAllInputVariableRawAndDerived();

  std::sort(telemetryVars.begin(), telemetryVars.end());

  ui->lb_TelAvailable->clear();

  for (auto& s : telemetryVars) {
    ui->lb_TelAvailable->addItem(QString(s.c_str()));
  }

  //---- selected:

  ui->lb_TelSelected->clear();

  for (auto& var : appConfig->TelemetryRecordingVariables) {
    std::string name = GetVariableNameFromVariableId(var);
    ui->lb_TelSelected->addItem(QString(name.c_str()));
  }

  ui->le_FrameCount->setText(QString::number(appConfig->FrameCount));
  ui->le_Channels->setText(QString::number(appConfig->ChannelCount));
  ui->le_SampleRate->setText(QString::number(appConfig->Wav_SampleRate));

  ui->le_LoopLength->setText(QString::number(appConfig->bm_LoopLength));
  ui->le_Latency->setText(QString::number(appConfig->bm_ExpectedLatencyMs));
  ui->le_DelayBetweenBeeps->setText(
      QString::number(appConfig->bm_DelayBetweenBeeps));
  ui->le_NextLapDetection->setText(
      QString::number(appConfig->bm_NextLapMinDistance));

  ui->le_FileNameMarker->setText(QString(appConfig->Marker_fileName.c_str()));
  ui->le_FileNamePreMarker->setText(
      QString(appConfig->PreMarker_fileName.c_str()));

  ui->lbl_Volume->setText(
      QString::number(static_cast<double>(appConfig->bm_SoundVolume)));

  SetVolumeSliderPosition(appConfig->bm_SoundVolume);

  ui->le_MaxTicksInMemory->setText(
      QString::number(appConfig->telemetry_MaxTicksInMemory));
}

void WindowConfig::SetVolumeSliderPosition(float volumeValue) {
  if (volumeValue < kVolumeMin)
    volumeValue = kVolumeMin;
  if (volumeValue > kVolumeMax)
    volumeValue = kVolumeMax;

  float distanceFromMin = volumeValue - kVolumeMin;

  float distancePercentage = distanceFromMin / (kVolumeMax - kVolumeMin);
  float tickPos = 100.0f * distancePercentage;

  ui->hs_Volume->setValue(static_cast<int>(tickPos));
}

void WindowConfig::GetVolumeSliderPosition(int sliderPos) {
  float pct = static_cast<float>(sliderPos) / 100.0f;

  float delta = pct * (kVolumeMax - kVolumeMin);

  float final = kVolumeMin + delta;

  appConfig->bm_SoundVolume = final;
}

void WindowConfig::on_lb_TelSelected_currentTextChanged(
    const QString& currentText) {
  try {
    telemetryItem_selected = currentText.toStdString();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowConfig::on_lb_TelAvailable_currentTextChanged(
    const QString& currentText) {
  try {
    telemetryItem_available = currentText.toStdString();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowConfig::on_btn_TelAdd_clicked() {
  try {
    std::cout << "Adding variable: " << telemetryItem_available << std::endl;

    VariableId id = GetVariableIdFromVariableName(telemetryItem_available);

    if (id == VariableId::VariableUnknown) {
      ShowMessageBox("Error: unrecognized variable selected \n");
      return;
    }

    appDbManager->AddVariableIdToTelemetryRecording(id);

    RefreshWindow();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowConfig::on_btn_TelDefault_clicked() {
  try {
    std::cout << "Resetting telemetry variables to default \n";

    appDbManager->ResetTelemetryVariablesToDefault();

    RefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowConfig::on_hs_Volume_sliderMoved(int position) {
  try {
    GetVolumeSliderPosition(position);

    ui->lbl_Volume->setText(
        QString::number(static_cast<double>(appConfig->bm_SoundVolume)));
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowConfig::on_btn_Save_clicked() {
  try {
    bool ok;

    appConfig->telemetry_MaxTicksInMemory =
        static_cast<size_t>(ui->le_MaxTicksInMemory->text().toInt(&ok));

    if (appConfig->telemetry_MaxTicksInMemory > 10000)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for max ticks in memory\n");
      return;
    }

    appConfig->FrameCount = ui->le_FrameCount->text().toInt(&ok);
    if (!ok) {
      ShowMessageBox("Error: bad value for frame count \n");
      return;
    }

    appConfig->ChannelCount = ui->le_Channels->text().toInt(&ok);
    if (appConfig->ChannelCount <= 0 || appConfig->ChannelCount > 6)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for channels \n");
      return;
    }

    appConfig->Wav_SampleRate = ui->le_SampleRate->text().toInt(&ok);
    if (appConfig->Wav_SampleRate <= 0)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for sample rate \n");
      return;
    }

    appConfig->bm_LoopLength = ui->le_LoopLength->text().toInt(&ok);
    if (appConfig->bm_LoopLength < 0)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for loop length \n");
      return;
    }

    appConfig->bm_ExpectedLatencyMs = ui->le_Latency->text().toInt(&ok);
    if (appConfig->bm_ExpectedLatencyMs < 0)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for latency \n");
      return;
    }

    appConfig->bm_DelayBetweenBeeps =
        ui->le_DelayBetweenBeeps->text().toInt(&ok);
    if (appConfig->bm_DelayBetweenBeeps < 0)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for delay between beeps \n");
      return;
    }

    appConfig->bm_NextLapMinDistance =
        ui->le_NextLapDetection->text().toInt(&ok);
    if (appConfig->bm_NextLapMinDistance < 0)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for next lap detection \n");
      return;
    }

    appConfig->bm_SoundVolume = ui->lbl_Volume->text().toFloat(&ok);
    if (appConfig->bm_SoundVolume < 0.0f)
      ok = false;
    if (!ok) {
      ShowMessageBox("Error: bad value for volume \n");
      return;
    }

    std::string nMarker = ui->le_FileNameMarker->text().toStdString();

    if (nMarker.size() == 0) {
      ShowMessageBox("Error: marker file name missing");
      return;
    }

    appConfig->Marker_fileName = nMarker;

    std::string nPremarker = ui->le_FileNamePreMarker->text().toStdString();

    if (nPremarker.size() == 0) {
      ShowMessageBox("Error: premarker file name missing");
      return;
    }

    appConfig->PreMarker_fileName = nPremarker;

    appDbManager->SaveDb();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

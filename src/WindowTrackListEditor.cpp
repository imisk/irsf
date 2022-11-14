
#include "WindowTrackListEditor.h"
#include <iostream>
#include "ErrorMessageBoxUtility.h"
#include "QDebug"
#include "ui_WindowTrackListEditor.h"

using namespace irsf;

WindowTrackListEditor::WindowTrackListEditor(TrackDataManager* tdManager,
                                             QWidget* parent)
    : QDialog(parent),
      ui(new Ui::WindowTrackListEditor),
      trackDataManager(tdManager) {
  ui->setupUi(this);

  selectedTrackId = kIdNotSelected;
  selectedTrackConfigId = kIdNotSelected;
}

WindowTrackListEditor::~WindowTrackListEditor() {
  delete ui;
}

void WindowTrackListEditor::on_btn_AddNewTrack_Add_clicked() {
  try {
    qDebug() << "Add button";

    QString qsName;
    qsName = ui->le_AddNewTrack_NameInput->text();

    std::string name = qsName.toStdString();

    trackDataManager->AddNewTrack(name);

    RefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackListEditor::RefreshWindow() {
  qDebug() << "Refresh window";

  // Tracks
  ui->lb_Tracks->clear();

  TrackDataAll data = trackDataManager->GetData();

  for (size_t i = 0; i < data.tracks.size(); i++) {
    ui->lb_Tracks->addItem(QString(data.tracks[i].name.c_str()));
  }

  if (selectedTrackId != kIdNotSelected)
    ui->lbl_SelectedTrackIdInput->setText(QString::number(selectedTrackId));
  else
    ui->lbl_SelectedTrackIdInput->setText("-");

  if (selectedTrackConfigId != kIdNotSelected)
    ui->lbl_SelectedConfigIdInput->setText(
        QString::number(selectedTrackConfigId));
  else
    ui->lbl_SelectedConfigIdInput->setText("-");

  RefreshTrackConfigurations();
}

void WindowTrackListEditor::GetSelectedTrack(
    int32_t& retSelectedTrackId,
    int32_t& retSelectedTrackConfigId) noexcept {
  retSelectedTrackId = selectedTrackId;
  retSelectedTrackConfigId = selectedTrackConfigId;
}

void WindowTrackListEditor::SetModeSelectionOnly(bool selectOnly) {
  if (selectOnly) {
    QRect geom(50, 50, 497, 497);
    this->setGeometry(geom);
  } else {
    QRect geom(50, 50, 997, 497);
    this->setGeometry(geom);
  }
}

void WindowTrackListEditor::on_lb_Tracks_currentTextChanged(
    const QString& currentText) {
  try {
    std::string trackName = currentText.toStdString();

    if (trackName.size() == 0)
      return;

    trackDataManager->GetTrackId(trackName, selectedTrackId);

    qDebug() << "selected track id = " << selectedTrackId;

    ui->lbl_SelectedTrackIdInput->setText(QString::number(selectedTrackId));

    selectedTrackConfigId = kIdNotSelected;

    RefreshTrackConfigurations();
  } catch (IrsfException& err) {
    ui->lbl_SelectedTrackIdInput->setText("-");
    selectedTrackId = kIdNotSelected;

    HandleErrorMessage(err);
  } catch (...) {
    ui->lbl_SelectedTrackIdInput->setText("-");
    selectedTrackId = kIdNotSelected;

    HandleGeneralError();
  }
}

void WindowTrackListEditor::RefreshTrackConfigurations() {
  ui->lb_TrackConfigs->clear();

  qDebug() << "RefreshTrackConfigurations ... selectedTrackId is "
           << selectedTrackId;

  if (selectedTrackId == kIdNotSelected)
    return;

  Track* selectedTrack = nullptr;

  TrackDataAll data = trackDataManager->GetData();

  for (size_t i = 0; i < data.tracks.size(); i++) {
    if (data.tracks[i].id == selectedTrackId) {
      selectedTrack = &data.tracks[i];
    }
  }

  if (selectedTrack == nullptr) {
    qDebug() << "Track with ID not found.";
    return;
  }

  qDebug() << "Track config count = " << selectedTrack->configurations.size();

  for (const auto& config : selectedTrack->configurations) {
    ui->lb_TrackConfigs->addItem(QString(config.name.c_str()));
  }
}

void WindowTrackListEditor::on_btn_AddNewTrackConfig_Add_clicked() {
  try {
    if (selectedTrackId == kIdNotSelected ||
        selectedTrackId == kTrackIdAllTracks) {
      return;
    }

    QString qsName;
    qsName = ui->le_AddNewTrackConfig_NameInput->text();

    std::string name = qsName.toStdString();

    bool ok;
    QString qsLen = ui->le_AddNewTrackConfig_LengthInput->text();
    float len = qsLen.toFloat(&ok);

    if (!ok) {
      qDebug() << "Error : bad length";
      ShowMessageBox("Error : bad length for track config.");
      len = -1;
      return;
    }

    trackDataManager->AddNewTrackConfig(selectedTrackId, name, len);

    RefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackListEditor::on_btn_DeleteTrackConfig_clicked() {
  try {
    if (selectedTrackId == kIdNotSelected) {
      ShowMessageBox("Error : no track selected.");
      return;
    }

    if (selectedTrackConfigId == kIdNotSelected) {
      ShowMessageBox("Error : no track config selected.");
      return;
    }

    trackDataManager->RemoveTrackConfig(selectedTrackId, selectedTrackConfigId);

    selectedTrackConfigId = kIdNotSelected;

    RefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackListEditor::on_lb_TrackConfigs_currentTextChanged(
    const QString& currentText) {
  try {
    std::string configName = currentText.toStdString();

    if (configName.size() == 0)
      return;

    trackDataManager->GetTrackConfigId(selectedTrackId, configName,
                                       selectedTrackConfigId);

    std::cout << "Selected track config id = " << selectedTrackConfigId
              << std::endl;

    ui->lbl_SelectedConfigIdInput->setText(
        QString::number(selectedTrackConfigId));

    TrackLayoutConfiguration config;

    trackDataManager->GetTrackConfig(selectedTrackId, configName, config);

    std::cout << "Selected track config length (meters) = "
              << config.totalLengthMeters << std::endl;

    RefreshTrackConfigurations();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);

    ui->lbl_SelectedConfigIdInput->setText("-");
    selectedTrackConfigId = kIdNotSelected;
  } catch (...) {
    HandleGeneralError();

    ui->lbl_SelectedConfigIdInput->setText("-");
    selectedTrackConfigId = kIdNotSelected;
  }
}

void WindowTrackListEditor::on_btn_DeleteTrack_clicked() {
  try {
    if (selectedTrackId == kIdNotSelected ||
        selectedTrackId == kTrackIdAllTracks) {
      ShowMessageBox("Error : no track selected.");
      return;
    }

    trackDataManager->RemoveTrack(selectedTrackId);

    selectedTrackId = kIdNotSelected;

    RefreshWindow();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackListEditor::on_btn_Select_clicked() {
  if (selectedTrackId == kIdNotSelected || selectedTrackId == kIdNotSelected) {
    ShowMessageBox("Error : no track selected.");
    return;
  }

  selectButtonClicked();
  this->hide();
}

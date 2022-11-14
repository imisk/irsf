
#include "WindowTrackSectorEditor.h"
#include <iostream>
#include "ErrorMessageBoxUtility.h"
#include "ui_WindowTrackSectorEditor.h"

using namespace irsf;

WindowTrackSectorEditor::WindowTrackSectorEditor(TrackDataManager* tdm,
                                                 QWidget* parent)
    : QDialog(parent),
      ui(new Ui::WindowTrackSectorEditor),
      mngr(std::make_unique<TrackSectorManager>(tdm)),
      windowTrackListEditor(std::make_unique<WindowTrackListEditor>(tdm)) {
  ui->setupUi(this);

  connect(windowTrackListEditor.get(), SIGNAL(selectButtonClicked()), this,
          SLOT(slotRefreshWindowTrack()));
}

WindowTrackSectorEditor::~WindowTrackSectorEditor() {
  delete ui;
}

void WindowTrackSectorEditor::EnableSelectionOnlyMode(bool enable) {
  if (enable) {
    ui->gb_AddNew->setVisible(false);
    ui->btn_Remove->setVisible(false);
    ui->btn_TrackSelect->setVisible(false);
    ui->btn_SelectTs->setVisible(true);
  } else {
    ui->gb_AddNew->setVisible(true);
    ui->btn_Remove->setVisible(true);
    ui->btn_TrackSelect->setVisible(true);
    ui->btn_SelectTs->setVisible(false);
  }
}

void WindowTrackSectorEditor::SetCurrentTrack(int32_t trackId,
                                              int32_t trackConfigId) {
  mngr->SetCurrentTrack(trackId, trackConfigId);

  std::string name;

  mngr->GetTrackAndTrackConfigName(trackId, trackConfigId, name);

  ui->le_TrackName->setText(QString(name.c_str()));

  RefreshList();
}

int32_t WindowTrackSectorEditor::GetSelectedTrackSectorId(
    std::string& retName) noexcept {
  retName = selectedTrackSectorName;
  return selectedTrackSectorId;
}

void WindowTrackSectorEditor::slotRefreshWindowTrack() {
  try {
    int32_t trackId = kIdNotSelected;
    int32_t configId = kIdNotSelected;

    windowTrackListEditor->GetSelectedTrack(trackId, configId);

    SetCurrentTrack(trackId, configId);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackSectorEditor::on_btn_TrackSelect_clicked() {
  try {
    windowTrackListEditor->show();
    windowTrackListEditor->RefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackSectorEditor::on_btn_Add_clicked() {
  try {
    QString name = ui->le_Name->text();

    if (name.size() == 0)
      throw IrsfException(IrsfError::InvalidName);

    bool ok;
    QString qsStart = ui->le_Start->text();

    float start = 0.0f;
    float end = 0.0f;

    if (qsStart.size() > 0)
      start = qsStart.toFloat(&ok);
    else
      throw IrsfException(IrsfError::InvalidInput);

    if (!ok) {
      QString msg = "Bad start length - error.";
      ShowMessageBox(msg);

      throw IrsfException(IrsfError::InvalidInput);
    }

    QString qsEnd = ui->le_End->text();

    if (qsEnd.size() > 0)
      end = qsEnd.toFloat(&ok);
    else
      throw IrsfException(IrsfError::InvalidInput);

    if (!ok) {
      QString msg = "Bad end length - error.";
      ShowMessageBox(msg);

      throw IrsfException(IrsfError::InvalidInput);
    }

    TrackSector ts;

    if (name.length() == 0) {
      QString msg = "Please input name for track sector!";
      ShowMessageBox(msg);

      throw IrsfException(IrsfError::InvalidName);
    }

    if (start >= end) {
      QString msg =
          "The starting distance must be lower "
          "than ending distance.";
      ShowMessageBox(msg);
      throw IrsfException(IrsfError::InvalidInput);
    }

    ts.name = name.toStdString();
    ts.startDistance = start;
    ts.endDistance = end;

    std::tie(ts.trackId, ts.trackConfigurationId) = mngr->GetCurrentTrack();

    qDebug() << "track ID = " << ts.trackId;

    mngr->AddTrackSector(ts);

    RefreshList();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackSectorEditor::RefreshList() {
  // get list of track sectors and populate listbox

  std::vector<TrackSector> list;
  mngr->GetListOfSectorsForCurrentTrack(list);

  ui->lb_MainList->clear();

  if (list.size() > 0) {
    for (auto ts : list) {
      ui->lb_MainList->addItem(QString(ts.name.c_str()));
    }
  }
}

void WindowTrackSectorEditor::on_btn_Remove_clicked() {
  try {
    auto list = ui->lb_MainList->selectedItems();

    if (list.count() > 0) {
      qDebug() << "Selected TS is " << list[0]->text();
      std::string name = list[0]->text().toStdString();

      mngr->RemoveTrackSector(name);

      QString msg = "Track sector removed.";
      ShowMessageBox(msg);

    } else {
      std::cout << "No TS selected. \n";
    }

    RefreshList();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackSectorEditor::on_btn_SelectTs_clicked() {
  try {
    auto list = ui->lb_MainList->selectedItems();

    if (list.count() > 0) {
      qDebug() << "Selected TS is " << list[0]->text();
      std::string name = list[0]->text().toStdString();

      selectedTrackSectorName = name;
      selectedTrackSectorId = mngr->GetTrackSectorId(name);

      selectButtonClicked();

      this->hide();
    } else {
      QString msg = "You did not select any items";
      ShowMessageBox(msg);
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowTrackSectorEditor::on_lb_MainList_currentTextChanged(
    const QString& currentText) {
  try {
    std::cout << "\n Selected Track Sector is: "
              << currentText.toStdString().c_str() << std::endl;

    std::string name = currentText.toStdString();

    int32_t tsid = mngr->GetTrackSectorId(name);

    TrackSector ts = mngr->GetTrackSector(tsid);

    std::cout << "id: " << ts.id << std::endl;
    std::cout << "startDistance: " << ts.startDistance << std::endl;
    std::cout << "endDistance: " << ts.endDistance << std::endl;
    std::cout << "trackId: " << ts.trackId << std::endl;
    std::cout << "trackConfigurationId: " << ts.trackConfigurationId
              << std::endl;
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

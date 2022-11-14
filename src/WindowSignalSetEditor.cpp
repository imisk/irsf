
#include "WindowSignalSetEditor.h"
#include "ErrorMessageBoxUtility.h"
#include "ui_WindowSignalSetEditor.h"

using namespace irsf;

WindowSignalSetEditor::WindowSignalSetEditor(SignalDbManager* sigDbMan,
                                             TrackDataManager* trackDatMan,
                                             QWidget* parent)
    : QDialog(parent),
      ui(new Ui::WindowSignalSetEditor),
      signalDbManager(sigDbMan),
      trackDataManager(trackDatMan) {
  ui->setupUi(this);
}

WindowSignalSetEditor::~WindowSignalSetEditor() {
  delete ui;
}

void WindowSignalSetEditor::SetMode(bool SelectSetOnly) {
  if (SelectSetOnly == true) {
    ui->btn_Save->hide();
    ui->btn_AddSignal->hide();
    ui->btn_DeleteSet->hide();
    ui->btn_TrackSelect->hide();
    ui->btn_RemoveSignal->hide();

    ui->btn_Select->show();
  } else {
    ui->btn_Save->show();
    ui->btn_AddSignal->show();
    ui->btn_DeleteSet->show();
    ui->btn_TrackSelect->show();
    ui->btn_RemoveSignal->show();

    ui->btn_Select->hide();
  }
}

IrsfSignalSet* WindowSignalSetEditor::GetCurrentSignalSet() noexcept {
  return &currentSignalSet;
}

void WindowSignalSetEditor::Init() {
  windowLoadSignal = std::make_unique<WindowLoadSignal>(signalDbManager, this);

  windowTrackListEditor =
      std::make_unique<WindowTrackListEditor>(trackDataManager, this);

  connect(windowTrackListEditor.get(), SIGNAL(selectButtonClicked()), this,
          SLOT(slotRefreshWindowTrack()));

  connect(windowLoadSignal.get(), SIGNAL(loadButtonClicked()), this,
          SLOT(slotAddSignal()));

  slotRefreshWindow();
}

void WindowSignalSetEditor::slotRefreshWindowTrack() {
  try {
    int32_t trackId = kIdNotSelected;
    int32_t configId = kIdNotSelected;

    windowTrackListEditor->GetSelectedTrack(trackId, configId);

    currentSignalSet.trackId = trackId;
    currentSignalSet.trackConfigId = configId;

    std::string trackAndConfigName;

    trackDataManager->GetTrackAndConfigName(trackId, configId,
                                            trackAndConfigName);

    ui->le_TrackName->setText(QString(trackAndConfigName.c_str()));

    signalDbManager->SaveDb();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::slotAddSignal() {
  try {
    IrsfSignal* loadedSignal = windowLoadSignal->GetSelectedSignal();

    if (loadedSignal == nullptr) {
      std::cout << "No signal was selected.\n";
      return;
    }

    std::cout << "Signal " << loadedSignal->name << " was added.\n";

    // check if signal with same name was already added
    bool found = false;
    for (const auto& sigName : currentSignalSet.signalNames) {
      if (loadedSignal->name.compare(sigName) == 0) {
        found = true;
      }
    }

    if (found == true) {
      throw IrsfException(IrsfError::NameAlreadyExists);
    }

    currentSignalSet.signalNames.push_back(loadedSignal->name);

    signalDbManager->SaveDb();

    slotRefreshCurrentSignalSet();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::slotRefreshCurrentSignalSet() {
  try {
    ui->le_Name->setText(currentSignalSet.name.c_str());

    std::string trackAndConfigName;

    trackDataManager->GetTrackAndConfigName(currentSignalSet.trackId,
                                            currentSignalSet.trackConfigId,
                                            trackAndConfigName);

    ui->le_TrackName->setText(QString(trackAndConfigName.c_str()));

    ui->lb_Signals->clear();
    for (const auto& signalName : currentSignalSet.signalNames) {
      ui->lb_Signals->addItem(signalName.c_str());
    }

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::slotRefreshWindow() {
  try {
    ui->lb_AvailableSets->clear();

    for (const auto& set : signalDbManager->GetSignalSetList()) {
      std::cout << "adding name to set list = >" << set->name.c_str() << "<\n";
      ui->lb_AvailableSets->addItem(QString(set->name.c_str()));
    }

    ui->lb_Signals->clear();

    if (currentSignalSet.signalNames.size() > 0) {
      for (const auto& sigName : currentSignalSet.signalNames) {
        ui->lb_Signals->addItem(QString(sigName.c_str()));
      }
    }

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_btn_AddSignal_clicked() {
  try {
    std::cout << "Add signal button...\n";

    if (currentSignalSet.trackId == kIdNotSelected) {
      throw IrsfException(IrsfError::NoSignalSetSelected);
    }

    if (currentSignalSet.trackId != kTrackIdAllTracks) {
      if (currentSignalSet.trackId < 0 || currentSignalSet.trackConfigId < 0) {
        throw IrsfException(IrsfError::NoTrackAndTrackConfigSelected);
      }
    }

    windowLoadSignal->SetTrack(currentSignalSet.trackId,
                               currentSignalSet.trackConfigId);

    windowLoadSignal->show();

    windowLoadSignal->RefreshList();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_btn_TrackSelect_clicked() {
  try {
    windowTrackListEditor->show();
    windowTrackListEditor->SetModeSelectionOnly(true);
    windowTrackListEditor->RefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_lb_AvailableSets_currentTextChanged(
    const QString& currentText) {
  try {
    if (currentText == "")
      return;

    std::vector<IrsfSignalSet*> list = signalDbManager->GetSignalSetList();

    for (const auto& f : list) {
      if (f->name == currentText.toStdString()) {
        currentSignalSet = *f;
        slotRefreshCurrentSignalSet();
        break;
      }
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_btn_DeleteSet_clicked() {
  try {
    auto curSelection = ui->lb_AvailableSets->currentItem()->text();

    auto res =
        QMessageBox::question(this, "Delete Signal Set", "Are you sure?");

    if (res == QMessageBox::StandardButton::Yes) {
      std::cout << "Deleting signal set: " << curSelection.toStdString();

      signalDbManager->DeleteSignalSet(curSelection.toStdString());
      slotRefreshWindow();
    }

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_btn_RemoveSignal_clicked() {
  try {
    QString signalName = ui->lb_Signals->currentItem()->text();

    if (currentSignalSet.trackId == kIdNotSelected)
      throw IrsfException(IrsfError::NoSignalSetSelected);

    if (signalName == "")
      throw IrsfException(IrsfError::NoSignalSelected);

    signalDbManager->RemoveSignalFromSignalSet(currentSignalSet.name,
                                               signalName.toStdString());

    slotRefreshWindow();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_btn_Select_clicked() {
  try {
    selectButtonClicked();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_btn_Save_clicked() {
  try {
    QString qName = ui->le_Name->text();

    IrsfSignalSet ns;

    currentSignalSet = ns;

    currentSignalSet.name = qName.toStdString();

    if (qName == "" || qName == "None") {
      throw IrsfException(IrsfError::InvalidName);
    }

    signalDbManager->SaveSignalSet(&currentSignalSet);

    slotRefreshWindow();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalSetEditor::on_le_Name_textEdited(const QString& arg1) {
  ui->lb_Signals->clear();

  Q_UNUSED(arg1)
}

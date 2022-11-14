#include "WindowBrakeMarkerEditor.h"
#include "ErrorMessageBoxUtility.h"
#include "IrsfCommon.h"
#include "Utilities.h"
#include "ui_WindowBrakeMarkerEditor.h"

using namespace irsf;

WindowBrakeMarkerEditor::WindowBrakeMarkerEditor(AppDbManager* adb,
                                                 TrackDataManager* tdb,
                                                 QWidget* parent)
    : QDialog(parent),
      ui(new Ui::WindowBrakeMarkerEditor),
      appDbManager(adb),
      trackDataManager(tdb) {
  ui->setupUi(this);

  SelectFirstSet();
  RefreshWindow(true);

  textChangeEnabled = true;
}

WindowBrakeMarkerEditor::~WindowBrakeMarkerEditor() {
  delete ui;
}

void WindowBrakeMarkerEditor::slotRefreshWindowTrack() {
  try {
    int32_t trackId = kIdNotSelected;
    int32_t configId = kIdNotSelected;

    windowTrackListEditor->GetSelectedTrack(trackId, configId);

    currentSet->TrackId = trackId;
    currentSet->TrackConfigId = configId;

    appDbManager->SaveDb();

    std::string name;
    trackDataManager->GetTrackAndConfigName(trackId, configId, name);

    ui->le_Track->setText(QString(name.c_str()));

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowBrakeMarkerEditor::on_btn_Save_clicked() {
  try {
    std::string currentSetName = ui->le_CurrentSetName->text().toStdString();

    if (currentSetName.size() == 0) {
      ShowMessageBox(QString("Error: brake marker set cannot be blank"));
      return;
    }

    // Check if it already exists
    if (appDbManager->BrakeMarkerSetExists(currentSetName)) {
      ShowMessageBox(
          QString("Error: brake marker set with this name already exists"));
      return;
    }

    currentSet = appDbManager->CreateNewBrakeMarkerSet(currentSetName);

    RefreshWindow(true);

    ui->cb_SetList->setCurrentText(QString(currentSet->name.c_str()));

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowBrakeMarkerEditor::RefreshWindow(bool updateMainList) {
  auto currentSet_store = currentSet;

  if (updateMainList) {
    ui->cb_SetList->clear();

    auto nameList = appDbManager->GetBrakeMarkerSetNameList();

    for (auto& n : nameList) {
      ui->cb_SetList->addItem(n);
    }
  }

  if (currentSet_store != nullptr) {
    currentSet = currentSet_store;
  }

  if (currentSet == nullptr) {
    SelectFirstSet();
  }

  if (currentSet == nullptr)
    return;

  QString name(currentSet->name.c_str());
  ui->le_CurrentSetName->setText(name);

  ui->cb_SetList->setCurrentText(name);

  std::string trackName;
  trackDataManager->GetTrackAndConfigName(currentSet->TrackId,
                                          currentSet->TrackConfigId, trackName);

  QString qTrackName(trackName.c_str());
  ui->le_Track->setText(qTrackName);

  ui->lb_Markers->clear();

  for (auto& b : currentSet->bmList) {
    std::string s;
    s = BrakeMarkerToString(b);

    // QString newItem(b.getText().c_str());

    QString newItem(s.c_str());

    ui->lb_Markers->addItem(newItem);
  }
}

void WindowBrakeMarkerEditor::SelectFirstSet() {
  auto nameList = appDbManager->GetBrakeMarkerSetNameList();

  if (nameList.size() == 0)
    return;

  auto name = nameList[0].toStdString();

  currentSet = appDbManager->GetBrakeMarkerSet(name);
}

void WindowBrakeMarkerEditor::on_cb_SetList_currentTextChanged(
    const QString& arg1) {
  try {
    if (textChangeEnabled) {
      std::string name = arg1.toStdString();
      currentSet = appDbManager->GetBrakeMarkerSet(name);
      // std::cout << "currentSet on_cb_ changed == " << currentSet->name <<
      // std::endl;
      RefreshWindow(false);
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowBrakeMarkerEditor::on_btn_Rename_clicked() {
  try {
    if (currentSet == nullptr) {
      ShowMessageBox(QString("Error: no set is currently selected \n"));
      return;
    }

    std::string newName = ui->le_CurrentSetName->text().toStdString();

    if (newName.size() == 0) {
      ShowMessageBox(QString("Error: you did not enter a name. \n"));
      return;
    }

    auto tr = appDbManager->GetBrakeMarkerSet(newName);

    if (tr != nullptr) {
      ShowMessageBox(QString("Error: set with this name already exists.\n"));
      return;
    }

    std::cout << "Renaming brake marker set from " << currentSet->name << " to "
              << newName << std::endl;

    currentSet->name = newName;

    appDbManager->SaveDb();

    RefreshWindow(true);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowBrakeMarkerEditor::on_btn_Delete_clicked() {
  try {
    if (currentSet == nullptr) {
      ShowMessageBox(QString("Error: no set is currently selected \n"));
      return;
    }

    appDbManager->DeleteBrakeMarkerSet(currentSet->name);

    SelectFirstSet();

    RefreshWindow(true);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowBrakeMarkerEditor::Init() {
  windowTrackListEditor =
      std::make_unique<WindowTrackListEditor>(trackDataManager);

  connect(windowTrackListEditor.get(), SIGNAL(selectButtonClicked()), this,
          SLOT(slotRefreshWindowTrack()));
}

void WindowBrakeMarkerEditor::on_btn_SelectTrack_clicked() {
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

void WindowBrakeMarkerEditor::on_btn_AddNewMarker_clicked() {
  try {
    QString dist = ui->le_Distance->text();
    QString speed = ui->le_Speed->text();

    BrakeMarker n;

    bool ok;
    n.speedAtMarker = speed.toFloat(&ok);

    if (!ok) {
      ShowMessageBox("Error: bad value for speed.\n");
      return;
    }

    n.distancePosition = dist.toFloat(&ok);

    if (!ok) {
      ShowMessageBox("Error: bad value for distance.\n");
      return;
    }

    if (currentSet == nullptr) {
      ShowMessageBox("Error: no set currently selected.\n");
      return;
    }

    appDbManager->AddBrakeMarkerToBrakeMarkerSet(currentSet->name, n);

    RefreshWindow(false);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowBrakeMarkerEditor::on_btn_DelMarker_clicked() {
  try {
    std::string curMarkerText = "";

    if (ui->lb_Markers->currentItem() != nullptr) {
      curMarkerText = ui->lb_Markers->currentItem()->text().toStdString();
    } else {
      ShowMessageBox("Error: no marker is currently selected.\n");
      return;
    }

    std::cout << "Marker to delete: >" << curMarkerText << "< \n";

    if (currentSet == nullptr) {
      ShowMessageBox("Error: no set currently selected.\n");
      return;
    }

    appDbManager->DeleteBrakeMarkerFromBrakeMarkerSet(currentSet->name,
                                                      curMarkerText);

    RefreshWindow(false);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

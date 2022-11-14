
#include "WindowLive.h"
#include "ErrorMessageBoxUtility.h"
#include "ui_WindowLive.h"

using namespace irsf;

WindowLive::WindowLive(TrackDataManager* tdm,
                       FormulaDbManager* fdm,
                       SignalDbManager* sdm,
                       AppDbManager* adm,
                       QWidget* parent)
    :

      QDialog(parent),
      ui(new Ui::WindowLive),
      trackDataManager(tdm),
      mngr(std::make_unique<LiveManager>(tdm, fdm, sdm, adm)),
      win(std::make_unique<WindowSignalSetEditor>(sdm, tdm)),
      appDbManager(adm) {
  handler->SetLiveManager(mngr.get());

  ui->setupUi(this);

  connect(win.get(), SIGNAL(selectButtonClicked()), this,
          SLOT(slotSignalSetSelected()));
}

WindowLive::~WindowLive() {
  delete ui;
}

void WindowLive::RefreshWindow() {
  auto bms = appDbManager->GetBrakeMarkerSetNameList();

  ui->cb_BrakeMarkerSets->clear();

  ui->cb_BrakeMarkerSets->addItem(QString("None"));

  for (auto& b : bms) {
    ui->cb_BrakeMarkerSets->addItem(b);
  }
}

void WindowLive::on_btn_Activate_clicked() {
  try {
    std::cout << "Activating. \n";

    if (currentSignalSet == nullptr)
      throw IrsfException(IrsfError::NoSignalSetSelected);

    bool recTelemetry = false;

    if (ui->cb_RecordTelemetry->isChecked())
      recTelemetry = true;

    std::string None("None");
    std::string selBmName = ui->cb_BrakeMarkerSets->currentText().toStdString();

    if (selBmName == None) {
      mngr->SetBrakeMarkerUsage(false);
    } else {
      mngr->SetBrakeMarkerUsage(true, selBmName);
    }

    mngr->SetCurrentSignalSet(currentSignalSet);

    mngr->SetRecordingTelemetry(recTelemetry);

    handler->Activate();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLive::on_btn_Select_clicked() {
  try {
    win->slotRefreshWindow();
    win->SetMode(true);
    win->show();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLive::slotSignalSetSelected() {
  try {
    currentSignalSet = win->GetCurrentSignalSet();

    win->hide();

    if (currentSignalSet != nullptr) {
      ui->le_SignalSetName->setText(currentSignalSet->name.c_str());

      std::string tName;

      mngr->GetTrackAndConfigName(currentSignalSet->trackId,
                                  currentSignalSet->trackConfigId, tName);

      ui->le_Track->setText(tName.c_str());
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLive::handleErrorActivateLive(IrsfException& err) {
  std::cout << "---- WindowLive::handleErrorActivateLive \n";
  HandleErrorMessage(err);
}

void WindowLive::on_btn_Stop_clicked() {
  try {
    mngr->RequestStop();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLive::on_cb_BrakeMarkerSets_currentTextChanged(const QString& arg1) {
  try {
    std::cout << "Selected brake marker set: " << arg1.toStdString()
              << std::endl;

    std::string selectedName = arg1.toStdString();

    std::string None("None");

    if (selectedName != None) {
      auto bset = appDbManager->GetBrakeMarkerSet(selectedName);

      if (bset != nullptr) {
        std::string trackName;
        trackDataManager->GetTrackAndConfigName(bset->TrackId,
                                                bset->TrackConfigId, trackName);

        ui->le_Track_bm->setText(QString(trackName.c_str()));
      }
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}


#include "WindowLoadSignal.h"
#include <QtDebug>
#include "ErrorMessageBoxUtility.h"
#include "SignalDbManager.h"
#include "ui_WindowLoadSignal.h"

using namespace irsf;

WindowLoadSignal::WindowLoadSignal(SignalDbManager* sigDbMan, QWidget* parent)
    : QDialog(parent), ui(new Ui::WindowLoadSignal), mngr(sigDbMan) {
  ui->setupUi(this);

  signalsList = mngr->GetSignalList();
}

WindowLoadSignal::~WindowLoadSignal() {
  delete ui;
}

void WindowLoadSignal::SetTrack(int32_t trackId,
                                int32_t trackConfigId) noexcept {
  currentTrackId = trackId;
  currentTrackConfigId = trackConfigId;
}

void WindowLoadSignal::RefreshList() {
  ui->lb_Main->clear();

  std::vector<std::string> names;
  names.clear();

  mngr->GetSignalNamesForTrack(currentTrackId, currentTrackConfigId, names);

  for (const auto& s : names) {
    qDebug() << "Load Signal = " << s.c_str();
    ui->lb_Main->addItem(QString(s.c_str()));
  }
}

IrsfSignal* WindowLoadSignal::GetSelectedSignal() noexcept {
  return selectedSignal;
}

void WindowLoadSignal::on_btn_Cancel_clicked() {
  this->hide();
}

void WindowLoadSignal::on_btn_Delete_clicked() {
  try {
    if (selectedSignal == nullptr)
      throw IrsfException(IrsfError::NoSignalSelected);

    auto res = QMessageBox::question(this, "Delete Signal", "Are you sure?");

    if (res == QMessageBox::StandardButton::Yes) {
      std::cout << "Trying to delete signal >" << selectedSignal->name
                << "< \n";

      mngr->DeleteSignal(selectedSignal->name);
      RefreshList();

      std::cout << "Signal deleted. \n";
    }

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLoadSignal::on_lb_Main_currentTextChanged(
    const QString& currentText) {
  try {
    for (const auto& sig : signalsList) {
      if (sig->name == currentText.toStdString()) {
        if (sig->trackId == kTrackIdAllTracks &&
            sig->trackId == currentTrackId) {
          selectedSignal = sig;
          break;
        }

        if (sig->trackId == currentTrackId &&
            sig->trackConfigId == currentTrackConfigId) {
          selectedSignal = sig;
          break;
        }
      }
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLoadSignal::on_btn_Select_clicked() {
  try {
    loadButtonClicked();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }

  this->hide();
}

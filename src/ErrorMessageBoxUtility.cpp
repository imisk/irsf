#include "ErrorMessageBoxUtility.h"
namespace irsf {

void HandleErrorMessage(const IrsfException& err) {
  QMessageBox msgBox;

  std::string s(err.what());

  QString message(s.c_str());

  QString full_message = "Error: " + message;

  msgBox.setText(full_message);

  msgBox.exec();
}

void HandleGeneralError() {
  QMessageBox msgBox;
  QString message =
      "Error: An unspecified error occured. For more "
      "information, please look at the textual console output. ";
  msgBox.setText(message);
  msgBox.exec();
}

void ShowMessageBox(QString message) {
  QMessageBox msgBox;
  msgBox.setText(message);
  msgBox.exec();
}

void ShowMessageBox(const char* message) {
  QString msg(message);
  ShowMessageBox(msg);
}

}  // namespace irsf

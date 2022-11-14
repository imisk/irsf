#ifndef ERRORMESSAGEBOXUTILITY_H
#define ERRORMESSAGEBOXUTILITY_H

#include <QMessageBox>
#include "IrsfCommon.h"  //

namespace irsf {

class IrsfException;

void HandleErrorMessage(const IrsfException& err);

void ShowMessageBox(QString message);

void ShowMessageBox(const char* message);

void HandleGeneralError();
}  // namespace irsf
#endif  // ERRORMESSAGEBOXUTILITY_H

// todo: consider introducing pImpl idiom somewhere just to show off

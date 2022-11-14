#include "CoreContext.h"
#include <QDir>
#include <QStandardPaths>
namespace irsf {

CoreContext::CoreContext() {}

void CoreContext::Initialize() {
  IrsfException retErr(IrsfError::OK);
  bool oops = false;

  auto vvvd = QDir::currentPath();
  std::cout << "currentPath = " << vvvd.toStdString() << std::endl;

  auto sPath =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  std::cout << "wPath = " << sPath.toStdString() << std::endl;

  try {
    formulaDbManager->LoadDb();
  } catch (IrsfException& err) {
    if (err.GetError() == IrsfError::CorruptedData ||
        err.GetError() == IrsfError::FileNotFound) {
      try {
        formulaDbManager->RenameBakToMain();
        formulaDbManager->LoadDb();
      } catch (IrsfException& err) {
        retErr = err;
        oops = true;
      }

    } else {
      retErr = err;
      oops = true;
    }
  }

  try {
    signalDbManager->LoadDb();
  } catch (IrsfException& err) {
    if (err.GetError() == IrsfError::CorruptedData ||
        err.GetError() == IrsfError::FileNotFound) {
      try {
        signalDbManager->RenameBakToMain();
        signalDbManager->LoadDb();
      } catch (IrsfException& err) {
        retErr = err;
        oops = true;
      }

    } else {
      retErr = err;
      oops = true;
    }
  }

  try {
    trackDataManager->LoadData();
  } catch (IrsfException& err) {
    if (err.GetError() == IrsfError::CorruptedData ||
        err.GetError() == IrsfError::FileNotFound) {
      try {
        trackDataManager->RenameBakToMain();
        trackDataManager->LoadData();
      } catch (IrsfException& err) {
        retErr = err;
        oops = true;
      }

    } else {
      retErr = err;
      oops = true;
    }
  }

  try {
    appDbManager->LoadDb();

  } catch (IrsfException& err) {
    if (err.GetError() == IrsfError::CorruptedData ||
        err.GetError() == IrsfError::FileNotFound) {
      try {
        appDbManager->RenameBakToMain();
        appDbManager->LoadDb();
      } catch (IrsfException& err) {
        retErr = err;
        oops = true;
      }

    } else {
      retErr = err;
      oops = true;
    }
  }

  if (oops)
    throw retErr;
}

FormulaDbManager* CoreContext::GetFormulaDbManager() {
  return formulaDbManager.get();
}

SignalDbManager* CoreContext::GetSignalDbManager() {
  return signalDbManager.get();
}

TrackDataManager* CoreContext::GetTrackDataManager() {
  return trackDataManager.get();
}

AppDbManager* CoreContext::GetAppDbManager() {
  return appDbManager.get();
}
}  // namespace irsf

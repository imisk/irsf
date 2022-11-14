
#include "WindowLiveHandler.h"
#include "ErrorMessageBoxUtility.h"

using namespace irsf;

WindowLiveHandler::WindowLiveHandler() {
  worker = std::make_unique<Worker>();

  qRegisterMetaType<IrsfError>("IrsfError");

  worker->moveToThread(&processorThread);

  connect(&processorThread, &QThread::finished, worker.get(),
          &QObject::deleteLater);
  connect(this, &WindowLiveHandler::Activate, worker.get(),
          &Worker::processActivateLive);
  connect(worker.get(), &Worker::rethrowErrorActivateLive, this,
          &WindowLiveHandler::handleErrorActivate);
  connect(worker.get(), &Worker::finishedActivateLive, this,
          &WindowLiveHandler::handleActivateLiveFinished);

  processorThread.start();
}

WindowLiveHandler::~WindowLiveHandler() {
  processorThread.quit();
  processorThread.wait();
}

void WindowLiveHandler::handleErrorActivate(IrsfException& err) {
  HandleErrorMessage(err);
}

void WindowLiveHandler::handleActivateLiveFinished() {
  // code to be added if needed
}

void WindowLiveHandler::SetLiveManager(LiveManager* mngr) noexcept {
  liveManager = mngr;

  worker->SetLiveManager(liveManager);
}

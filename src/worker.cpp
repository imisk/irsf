
#include "worker.h"

using namespace irsf;

Worker::Worker() : liveManager(nullptr) {}

Worker::~Worker() {}

void Worker::SetLiveManager(LiveManager* lm) noexcept {
  liveManager = lm;
}

void Worker::processActivateLive() {
  try {
    liveManager->InitializeAll();
    liveManager->MainLoop();

  } catch (IrsfException& err) {
    rethrowErrorActivateLive(err);
    finishedActivateLive();
  } catch (...) {
    IrsfException exc = IrsfException(IrsfError::GeneralError);
    rethrowErrorActivateLive(exc);
  }
}

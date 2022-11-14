
#include "TelemetryDiskWriterHandler.h"
#include "ErrorMessageBoxUtility.h"

using namespace irsf;

TelemetryDiskWriterHandler::TelemetryDiskWriterHandler() {
  qRegisterMetaType<IrsfError>("IrsfError");

  worker->moveToThread(&writerThread);

  connect(&writerThread, &QThread::finished, worker.get(),
          &QObject::deleteLater);

  connect(this, &TelemetryDiskWriterHandler::WriteData, worker.get(),
          &TelemetryDiskWriterWorker::processWriteData);

  connect(worker.get(), &TelemetryDiskWriterWorker::rethrowErrorWriteData, this,
          &TelemetryDiskWriterHandler::handleErrorWriteData);

  connect(this, &TelemetryDiskWriterHandler::WriteCurrentLap, worker.get(),
          &TelemetryDiskWriterWorker::processWriteCurrentLap);

  connect(worker.get(), &TelemetryDiskWriterWorker::rethrowErrorWriteCurrentLap,
          this, &TelemetryDiskWriterHandler::handleErrorWriteCurrentLap);

  writerThread.start();
}

TelemetryDiskWriterHandler::~TelemetryDiskWriterHandler() {
  writerThread.quit();
  writerThread.wait();
}

void TelemetryDiskWriterHandler::SetWriter(
    TelemetryDiskWriter* inWriter) noexcept {
  worker->writer = inWriter;
}

void TelemetryDiskWriterHandler::handleErrorWriteData(
    const IrsfException& err) {
  HandleErrorMessage(err);
}

void TelemetryDiskWriterHandler::handleErrorWriteCurrentLap(
    const IrsfException& err) {
  HandleErrorMessage(err);
}

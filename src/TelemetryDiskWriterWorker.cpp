

#include "TelemetryDiskWriterWorker.h"

using namespace irsf;

TelemetryDiskWriterWorker::TelemetryDiskWriterWorker() noexcept {}

TelemetryDiskWriterWorker::~TelemetryDiskWriterWorker() {}

void TelemetryDiskWriterWorker::processWriteData() {
  try {
    writer->WriteData();
  } catch (IrsfException& err) {
    rethrowErrorWriteData(err);
  } catch (...) {
    IrsfException exc = IrsfException(IrsfError::GeneralError);
    rethrowErrorWriteData(exc);
  }
}

void TelemetryDiskWriterWorker::processWriteCurrentLap() {
  try {
    writer->WriteCurrentLap();
  } catch (IrsfException& err) {
    rethrowErrorWriteCurrentLap(err);
  } catch (...) {
    IrsfException exc = IrsfException(IrsfError::GeneralError);
    rethrowErrorWriteCurrentLap(exc);
  }
}

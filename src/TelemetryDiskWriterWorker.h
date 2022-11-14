#ifndef TELEMETRYDISKWRITERWORKER_H
#define TELEMETRYDISKWRITERWORKER_H

#include <QObject>
#include "IrsfCommon.h"
#include "QThread"
#include "TelemetryDiskWriter.h"
namespace irsf {
/*
 * Worker thread handler for TelemetryDiskWriter to perform writing in a
 * secondary thread.
 */
class TelemetryDiskWriterWorker : public QObject {
  Q_OBJECT

 public:
  explicit TelemetryDiskWriterWorker() noexcept;

  ~TelemetryDiskWriterWorker() override;

  TelemetryDiskWriterWorker(TelemetryDiskWriterWorker& other) = delete;

  TelemetryDiskWriterWorker& operator=(TelemetryDiskWriterWorker& other) =
      delete;

  TelemetryDiskWriterWorker(TelemetryDiskWriterWorker&& other) = delete;

  TelemetryDiskWriterWorker& operator=(TelemetryDiskWriterWorker&& other) =
      delete;

  friend class TelemetryDiskWriterHandler;

 public slots:

  void processWriteData();

  void processWriteCurrentLap();

 signals:

  void rethrowErrorWriteData(IrsfException& err);

  void rethrowErrorWriteCurrentLap(IrsfException& err);

 private:
  TelemetryDiskWriter* writer{nullptr};
};
}  // namespace irsf
#endif  // TELEMETRYDISKWRITERWORKER_H

#ifndef TELEMETRYDISKWRITERHANDLER_H
#define TELEMETRYDISKWRITERHANDLER_H

#include <QObject>
#include <QThread>
#include "IrsfCommon.h"
#include "TelemetryDiskWriterWorker.h"

namespace irsf {
/*
 * Multithreaded handling of live telemetry data, so that a thread is launched
 * for every new batch of data that needs to be written to disk, and sent to
 * the TelemetryDiskWriter class.
 */
class TelemetryDiskWriterHandler : public QObject {
  Q_OBJECT

  QThread writerThread;

 public:
  explicit TelemetryDiskWriterHandler();

  ~TelemetryDiskWriterHandler() override;

  TelemetryDiskWriterHandler(TelemetryDiskWriterHandler& other) = delete;

  TelemetryDiskWriterHandler& operator=(TelemetryDiskWriterHandler& other) =
      delete;

  TelemetryDiskWriterHandler(TelemetryDiskWriterHandler&& other) = delete;

  TelemetryDiskWriterHandler& operator=(TelemetryDiskWriterHandler&& other) =
      delete;

  void SetWriter(TelemetryDiskWriter* inWriter) noexcept;

 public slots:

  void handleErrorWriteData(const IrsfException& err);

  void handleErrorWriteCurrentLap(const IrsfException& err);

 signals:

  void WriteData();

  void WriteCurrentLap();

 private:
  std::shared_ptr<TelemetryDiskWriterWorker> worker{
      std::make_shared<TelemetryDiskWriterWorker>()};  // cross-thread
};
}  // namespace irsf
#endif  // TELEMETRYDISKWRITERHANDLER_H

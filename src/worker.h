#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include "LiveManager.h"
#include "QObject"
#include "QString"

namespace irsf {

class Worker : public QObject {
  Q_OBJECT
 public:
  explicit Worker();
  ~Worker() override;

  void SetLiveManager(LiveManager* lm) noexcept;

 public slots:

  void processActivateLive();

 signals:

  void finishedTest1();
  void finishedRecordTelemetry();

  void finishedSignalsLive();

  void finishedActivateLive();

  void sendResultTest1(int32_t retError);
  void sendResultRecordTelemetry(int32_t retError);

  void sendResultSignalsLive(int32_t retError);

  void sendResultActivateLive(int32_t retError);

  void rethrowErrorActivateLive(IrsfException& err);

 private:
  LiveManager* liveManager;
};
}  // namespace irsf

#endif  // WORKER_H

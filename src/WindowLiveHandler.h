#ifndef WINDOWLIVEHANDLER_H
#define WINDOWLIVEHANDLER_H

#include <QObject>
#include <QThread>
#include "IrsfCommon.h"
#include "worker.h"

class WindowLiveHandler final : public QObject {
  Q_OBJECT

  QThread processorThread;

 public:
  WindowLiveHandler();

  ~WindowLiveHandler() final;

  friend class WindowLive;

 public slots:

  void handleErrorActivate(irsf::IrsfException& err);

  void handleActivateLiveFinished();

 signals:
  void Activate();

 private:
  void SetLiveManager(irsf::LiveManager* mngr) noexcept;

  irsf::LiveManager* liveManager;

  std::unique_ptr<irsf::Worker> worker;
};

#endif  // WINDOWLIVEHANDLER_H

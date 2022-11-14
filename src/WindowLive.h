#ifndef WINDOWLIVE_H
#define WINDOWLIVE_H

#include <QDialog>
#include "AppDbManager.h"
#include "LiveManager.h"
#include "WindowLiveHandler.h"
#include "WindowSignalSetEditor.h"

namespace Ui {
class WindowLive;
}

class WindowLive final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowLive(irsf::TrackDataManager* tdm,
                      irsf::FormulaDbManager* fdm,
                      irsf::SignalDbManager* sdm,
                      irsf::AppDbManager* adm,
                      QWidget* parent = nullptr);

  ~WindowLive() final;

  void RefreshWindow();

 private slots:
  void on_btn_Activate_clicked();

  void on_btn_Select_clicked();

  void slotSignalSetSelected();

  void handleErrorActivateLive(irsf::IrsfException& err);

  void on_btn_Stop_clicked();

  void on_cb_BrakeMarkerSets_currentTextChanged(const QString& arg1);

 private:
  Ui::WindowLive* ui;

  irsf::TrackDataManager* trackDataManager;
  std::unique_ptr<irsf::LiveManager> mngr;
  std::unique_ptr<WindowSignalSetEditor> win;
  irsf::IrsfSignalSet* currentSignalSet{nullptr};
  std::unique_ptr<WindowLiveHandler> handler{
      std::make_unique<WindowLiveHandler>()};
  irsf::AppDbManager* appDbManager;
};

#endif  // WINDOWLIVE_H

#ifndef WINDOWLOADSIGNAL_H
#define WINDOWLOADSIGNAL_H

#include <QDialog>
#include "SignalDbManager.h"

namespace Ui {
class WindowLoadSignal;
}

class WindowLoadSignal final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowLoadSignal(irsf::SignalDbManager* sigDbMan,
                            QWidget* parent = nullptr);
  ~WindowLoadSignal() final;

  void SetTrack(int32_t trackId, int32_t trackConfigId) noexcept;

  void RefreshList();

  irsf::IrsfSignal* GetSelectedSignal() noexcept;

 signals:

  void loadButtonClicked();

 private slots:
  void on_btn_Cancel_clicked();

  void on_btn_Delete_clicked();

  void on_lb_Main_currentTextChanged(const QString& currentText);

  void on_btn_Select_clicked();

 private:
  Ui::WindowLoadSignal* ui;

  irsf::SignalDbManager* mngr;

  int32_t currentTrackId;
  int32_t currentTrackConfigId;

  std::vector<irsf::IrsfSignal*> signalsList;

  irsf::IrsfSignal* selectedSignal{nullptr};
};

#endif  // WINDOWLOADSIGNAL_H

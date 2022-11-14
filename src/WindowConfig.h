#ifndef WINDOWCONFIG_H
#define WINDOWCONFIG_H

#include <QDialog>
#include "AppDbManager.h"
#include "IrsfCommon.h"

namespace Ui {
class WindowConfig;
}

class WindowConfig final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowConfig(irsf::AppConfig* ac,
                        irsf::AppDbManager* adb,
                        QWidget* parent = nullptr);
  ~WindowConfig() final;

  void Init();

 private slots:
  void on_btn_TelRemove_clicked();

  void on_lb_TelSelected_currentTextChanged(const QString& currentText);

  void on_lb_TelAvailable_currentTextChanged(const QString& currentText);

  void on_btn_TelAdd_clicked();

  void on_btn_TelDefault_clicked();

  void on_hs_Volume_sliderMoved(int position);

  void on_btn_Save_clicked();

 private:
  void RefreshWindow();

  // Set slider based on volume value
  void SetVolumeSliderPosition(float volumeValue);

  // Set volume value based on slider
  void GetVolumeSliderPosition(int sliderPos);

  Ui::WindowConfig* ui;

  static constexpr float kVolumeMin = 0.0f;
  static constexpr float kVolumeMax = 2.0f;

  irsf::AppConfig* appConfig;
  irsf::AppDbManager* appDbManager;
  std::string telemetryItem_available;
  std::string telemetryItem_selected;
};

#endif  // WINDOWCONFIG_H

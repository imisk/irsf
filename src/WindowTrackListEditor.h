#ifndef WINDOWTRACKLISTEDITOR_H
#define WINDOWTRACKLISTEDITOR_H

#include <QDialog>
#include "TrackDataManager.h"

namespace Ui {
class WindowTrackListEditor;
}

class WindowTrackListEditor final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowTrackListEditor(irsf::TrackDataManager* tdManager,
                                 QWidget* parent = nullptr);

  ~WindowTrackListEditor() final;

  void RefreshWindow();

  // Return the selected track/track config IDs via arguments
  void GetSelectedTrack(int32_t& retSelectedTrackId,
                        int32_t& retSelectedTrackConfigId) noexcept;

  void SetModeSelectionOnly(bool selectOnly);

 signals:
  void selectButtonClicked();

 private slots:
  void on_btn_AddNewTrack_Add_clicked();

  void on_lb_Tracks_currentTextChanged(const QString& currentText);

  void on_btn_AddNewTrackConfig_Add_clicked();

  void on_btn_DeleteTrackConfig_clicked();

  void on_lb_TrackConfigs_currentTextChanged(const QString& currentText);

  void on_btn_DeleteTrack_clicked();

  void on_btn_Select_clicked();

 private:
  Ui::WindowTrackListEditor* ui;

  irsf::TrackDataManager* trackDataManager;

  int32_t selectedTrackId;

  int32_t selectedTrackConfigId;

  void RefreshTrackConfigurations();
};

#endif  // WINDOWTRACKLISTEDITOR_H

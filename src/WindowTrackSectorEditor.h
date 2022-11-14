#ifndef WINDOWTRACKSECTOREDITOR_H
#define WINDOWTRACKSECTOREDITOR_H

#include <QDebug>
#include <QDialog>
#include "TrackDataManager.h"
#include "TrackSectorManager.h"
#include "WindowTrackListEditor.h"

namespace Ui {
class WindowTrackSectorEditor;
}

class WindowTrackSectorEditor final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowTrackSectorEditor(irsf::TrackDataManager* tdm,
                                   QWidget* parent = nullptr);

  ~WindowTrackSectorEditor() final;

  /*
   * If enabled: Track is pre-set, you can only select a track sector or
   * close the window
   */
  void EnableSelectionOnlyMode(bool enable);

  void SetCurrentTrack(int32_t trackId, int32_t trackConfigId);

  int32_t GetSelectedTrackSectorId(std::string& retName) noexcept;

 signals:
  void selectButtonClicked();

 public slots:

  // A new Track/Track config was selected
  void slotRefreshWindowTrack();

 private slots:

  void on_btn_TrackSelect_clicked();

  void on_btn_Add_clicked();

  void on_btn_Remove_clicked();

  void on_btn_SelectTs_clicked();

  void on_lb_MainList_currentTextChanged(const QString& currentText);

 private:
  Ui::WindowTrackSectorEditor* ui;

  std::unique_ptr<irsf::TrackSectorManager> mngr;

  std::unique_ptr<WindowTrackListEditor> windowTrackListEditor;

  void RefreshList();

  int32_t selectedTrackSectorId{0};
  std::string selectedTrackSectorName{"None"};
};

#endif  // WINDOWTRACKSECTOREDITOR_H

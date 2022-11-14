#ifndef WINDOWBRAKEMARKEREDITOR_H
#define WINDOWBRAKEMARKEREDITOR_H

#include <QDialog>
#include "AppDbManager.h"
#include "TrackDataManager.h"
#include "WindowTrackListEditor.h"

namespace Ui {
class WindowBrakeMarkerEditor;
}

class WindowBrakeMarkerEditor final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowBrakeMarkerEditor(irsf::AppDbManager* adb,
                                   irsf::TrackDataManager* tdb,
                                   QWidget* parent = nullptr);
  ~WindowBrakeMarkerEditor() final;

  void Init();

 public slots:

  void slotRefreshWindowTrack();

 private slots:
  void on_btn_Save_clicked();

  void on_cb_SetList_currentTextChanged(const QString& arg1);

  void on_btn_Rename_clicked();

  void on_btn_Delete_clicked();

  void on_btn_SelectTrack_clicked();

  void on_btn_AddNewMarker_clicked();

  void on_btn_DelMarker_clicked();

 private:
  // Refresh the current set box based on currentSet
  void RefreshWindow(bool updateMainList);

  Ui::WindowBrakeMarkerEditor* ui;
  irsf::AppDbManager* appDbManager;

  irsf::TrackDataManager* trackDataManager;

  irsf::BrakeMarkerSet* currentSet{nullptr};

  // Have the first BrakeMarkerSet in the list marked as selected
  void SelectFirstSet();

  bool textChangeEnabled{false};

  std::unique_ptr<WindowTrackListEditor> windowTrackListEditor;
};

#endif  // WINDOWBRAKEMARKEREDITOR_H

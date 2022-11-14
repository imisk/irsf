#ifndef WINDOWSIGNALSETEDITOR_H
#define WINDOWSIGNALSETEDITOR_H

#include <QDialog>

#include "SignalDbManager.h"
#include "WindowLoadSignal.h"
#include "WindowTrackListEditor.h"

namespace Ui {
class WindowSignalSetEditor;
}

class WindowSignalSetEditor final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowSignalSetEditor(irsf::SignalDbManager* sigDbMan,
                                 irsf::TrackDataManager* trackDatMan,
                                 QWidget* parent = nullptr);

  ~WindowSignalSetEditor() final;

  /*
   * If we set the mode to SelectSetOnly, we hide the buttons for editing
   */
  void SetMode(bool SelectSetOnly);

  irsf::IrsfSignalSet* GetCurrentSignalSet() noexcept;

  void Init();

 signals:

  void selectButtonClicked();

 public slots:

  void slotRefreshWindowTrack();
  void slotAddSignal();
  void slotRefreshCurrentSignalSet();
  void slotRefreshWindow();

 private slots:
  void on_btn_AddSignal_clicked();

  void on_btn_TrackSelect_clicked();

  void on_lb_AvailableSets_currentTextChanged(const QString& currentText);

  void on_btn_DeleteSet_clicked();

  void on_btn_RemoveSignal_clicked();

  void on_btn_Select_clicked();

  void on_btn_Save_clicked();

  void on_le_Name_textEdited(const QString& arg1);

 private:
  Ui::WindowSignalSetEditor* ui;
  std::unique_ptr<WindowLoadSignal> windowLoadSignal;
  std::unique_ptr<WindowTrackListEditor> windowTrackListEditor;
  irsf::SignalDbManager* signalDbManager;
  irsf::TrackDataManager* trackDataManager;
  irsf::IrsfSignalSet currentSignalSet;
};

#endif  // WINDOWSIGNALSETEDITOR_H

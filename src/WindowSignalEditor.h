#ifndef WINDOWSIGNALEDITOR_H
#define WINDOWSIGNALEDITOR_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "SignalEditorManager.h"
#include "TrackDataManager.h"
#include "WindowLoadFormula.h"
#include "WindowLoadSignal.h"
#include "WindowTrackListEditor.h"
#include "WindowTrackSectorEditor.h"

namespace Ui {
class WindowSignalEditor;
}

class WindowSignalEditor final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowSignalEditor(irsf::TrackDataManager* inTrackDataMngr,
                              irsf::FormulaDbManager* inFormulaDbMngr,
                              irsf::SignalDbManager* inSignalDbMngr,
                              irsf::AppDbManager* inAppDbManager,
                              QWidget* parent = nullptr);

  ~WindowSignalEditor() final;

  void SetChart(QChartView* c);

  void Init();

 public slots:

  void slotRefreshWindow();
  void slotRefreshWindowFormula();
  void slotRefreshWindowTrack();
  void slotRefreshWindowTrackSector();
  void slotLoadSignal();

 private slots:
  void on_btn_Signal_Save_clicked();

  void on_btn_Formula_Select_clicked();

  void on_btn_TrackSelect_clicked();

  void on_btn_SelectTrackSector_clicked();

  void on_btn_LoadTelemetry_clicked();

  void on_cb_Range2enabled_stateChanged(int arg1);

  void on_le_Range1max_returnPressed();

  void on_le_Range1min_returnPressed();

  void on_le_Range2max_returnPressed();

  void on_le_Range2min_returnPressed();

  void on_btn_SoundSelect_clicked();

  void on_hs_Volume_valueChanged(int value);

  void on_btn_Signal_Load_clicked();

  void on_rb_SignalDistance_FullTrack_toggled(bool checked);

  void updateRanges();

  void on_btn_Range1auto_clicked();

  void on_btn_Range2auto_clicked();

  void on_btn_Curve1_clicked();

  void on_btn_Curve2_clicked();

  void on_btn_Curve3_clicked();

  void on_btn_Curve4_clicked();

  void on_btn_Curve5_clicked();

  void on_le_Signal_Name_textEdited(const QString& arg1);

  void on_btn_SoundPlay_clicked();

 private:
  void UpdateChart();

  void UpdateChartHistogram();

  void RefreshWindowCurveIcons();

  Ui::WindowSignalEditor* ui;

  std::unique_ptr<WindowLoadFormula> windowLoadFormula;

  std::unique_ptr<WindowTrackListEditor> windowTrackListEditor;

  std::unique_ptr<WindowTrackSectorEditor> windowTrackSectorEditor;

  std::unique_ptr<WindowLoadSignal> windowLoadSignal;

  QChartView* displayChartView;

  std::unique_ptr<irsf::SignalEditorManager> mngr;
  irsf::TrackDataManager* tdm;
  irsf::FormulaDbManager* fdm;
  irsf::SignalDbManager* sdm;
  irsf::AppDbManager* adm;

  QLineSeries* seriesMain;
  QChart* chartMain;

  bool currentlyPlayingSoundSample{false};
};

#endif  // WINDOWSIGNALEDITOR_H

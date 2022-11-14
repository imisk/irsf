#include "WindowSignalEditor.h"
#include <string>
#include "ErrorMessageBoxUtility.h"
#include "QBarCategoryAxis"
#include "QBarSeries"
#include "QBarSet"
#include "QFileDialog"
#include "QRubberBand"
#include "QValueAxis"
#include "ui_WindowSignalEditor.h"
#include "Utilities.h"

using namespace irsf;

WindowSignalEditor::WindowSignalEditor(TrackDataManager* inTrackDataMngr,
                                       FormulaDbManager* inFormulaDbMngr,
                                       SignalDbManager* inSignalDbMngr,
                                       AppDbManager* inAppDbManager,
                                       QWidget* parent)
    : QDialog(parent),
      ui(new Ui::WindowSignalEditor),
      tdm(inTrackDataMngr),
      fdm(inFormulaDbMngr),
      sdm(inSignalDbMngr),
      adm(inAppDbManager)

{
  ui->setupUi(this);
}

WindowSignalEditor::~WindowSignalEditor() {
  delete ui;
}

void WindowSignalEditor::SetChart(QChartView* c) {
  ui->verticalLayout->addWidget(c);
}

void WindowSignalEditor::Init() {
  try {
    mngr = std::make_unique<SignalEditorManager>(tdm, sdm, fdm, adm);

    windowTrackListEditor = std::make_unique<WindowTrackListEditor>(tdm);

    windowTrackSectorEditor = std::make_unique<WindowTrackSectorEditor>(tdm);

    windowLoadFormula = std::make_unique<WindowLoadFormula>();

    mngr->Initialize();

    windowLoadSignal =
        std::make_unique<WindowLoadSignal>(mngr->GetSignalDbManager());

    connect(windowLoadFormula.get(), SIGNAL(loadButtonClicked()), this,
            SLOT(slotRefreshWindowFormula()));

    connect(windowTrackListEditor.get(), SIGNAL(selectButtonClicked()), this,
            SLOT(slotRefreshWindowTrack()));

    connect(windowTrackSectorEditor.get(), SIGNAL(selectButtonClicked()), this,
            SLOT(slotRefreshWindowTrackSector()));

    connect(windowLoadSignal.get(), SIGNAL(loadButtonClicked()), this,
            SLOT(slotLoadSignal()));

    chartMain = new QChart();

    displayChartView = new QChartView(chartMain);

    RefreshWindowCurveIcons();

    slotRefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::slotRefreshWindow() {
  try {
    std::string trackName = "";
    mngr->GetTrackAndTrackConfigName(trackName);
    ui->le_TrackName->setText(trackName.c_str());

    ui->le_Range1max->setText(
        std::to_string(mngr->currentSignal.range1.max).c_str());
    ui->le_Range1min->setText(
        std::to_string(mngr->currentSignal.range1.min).c_str());

    ui->le_Signal_Name->setText(mngr->currentSignal.name.c_str());

    ui->lbl_Formula->setText(mngr->currentSignal.formulaName.c_str());

    if (mngr->currentSignal.secondRangeActive == true) {
      ui->cb_Range2enabled->setCheckState(Qt::CheckState::Checked);
      ui->le_Range2max->setText(
          std::to_string(mngr->currentSignal.range2.max).c_str());
      ui->le_Range2min->setText(
          std::to_string(mngr->currentSignal.range2.min).c_str());
    } else {
      ui->cb_Range2enabled->setCheckState(Qt::CheckState::Unchecked);
      ui->le_Range2max->setText("");
      ui->le_Range2min->setText("");
    }

    std::string tsName = "No Track Sector selected";

    if (mngr->currentSignal.useFullTrack) {
      ui->rb_SignalDistance_FullTrack->setChecked(true);
      ui->rb_SignalDistance_TrackSector->setChecked(false);
    } else {
      ui->rb_SignalDistance_FullTrack->setChecked(false);
      ui->rb_SignalDistance_TrackSector->setChecked(true);

      try {
        mngr->GetTrackDataManager()->GetTrackSectorName(
            mngr->currentSignal.trackSectorId, tsName);
      } catch (...) {
        std::cout << "Warning: track sector name could not be found for the "
                     "given track id \n";
      }
    }

    ui->lbl_TrackSectorName->setText(tsName.c_str());

    ui->le_SoundFilePath->setText(
        mngr->currentSignal.sound.soundFileName.c_str());

    int32_t sliderVal =
        static_cast<int32_t>(mngr->currentSignal.sound.soundVolume * 100.0f);

    ui->hs_Volume->setValue(sliderVal);

    RefreshWindowCurveIcons();

    UpdateChart();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::slotRefreshWindowFormula() {
  try {
    Formula* sel = windowLoadFormula->GetSelectedFormula();
    mngr->currentFormula = sel;

    if (mngr->currentFormula == nullptr) {
      ui->lbl_Formula->setText(QString("None"));
      mngr->currentSignal.formulaName = "None";
    } else {
      ui->lbl_Formula->setText(QString(mngr->currentFormula->name.c_str()));
      mngr->currentSignal.formulaName = mngr->currentFormula->name;
    }

    UpdateChart();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::slotRefreshWindowTrack() {
  try {
    int32_t trackId = kIdNotSelected;
    int32_t configId = kIdNotSelected;

    windowTrackListEditor->GetSelectedTrack(trackId, configId);

    std::string previousName = "";
    bool updateName = false;

    if (mngr->currentSignal.name.size() > 0) {
      updateName = true;
      previousName = mngr->currentSignal.name;
    }

    if (trackId != mngr->currentSignal.trackId ||
        configId != mngr->currentSignal.trackConfigId) {
      mngr->currentSignal.trackId = trackId;
      mngr->currentSignal.trackConfigId = configId;

      std::string trackAndConfigName;

      mngr->GetTrackAndTrackConfigName(trackAndConfigName);

      ui->le_TrackName->setText(QString(trackAndConfigName.c_str()));

      mngr->currentSignal.useFullTrack = true;

      if (updateName) {
        mngr->currentSignal.name = previousName + " - copy";
      }

      slotRefreshWindow();
    }

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::slotRefreshWindowTrackSector() {
  try {
    std::string tsName;

    int32_t tsid = windowTrackSectorEditor->GetSelectedTrackSectorId(tsName);

    mngr->currentSignal.trackSectorId = tsid;

    std::cout << "setting : currentSignal -> trackSectorId = " << tsid
              << std::endl;

    ui->lbl_TrackSectorName->setText(tsName.c_str());

    UpdateChart();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::slotLoadSignal() {
  try {
    IrsfSignal* loadedSignal = windowLoadSignal->GetSelectedSignal();

    if (loadedSignal == nullptr) {
      std::cout << "No signal was selected.\n";
      return;
    }

    std::cout << "Signal " << loadedSignal->name << " was loaded.\n";

    mngr->currentSignal = *loadedSignal;

    slotRefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_btn_Signal_Save_clicked() {
  try {
    // Pick up the values from textboxes
    on_le_Range1max_returnPressed();
    on_le_Range1min_returnPressed();
    on_le_Range2max_returnPressed();
    on_le_Range2min_returnPressed();

    if (mngr->currentSignal.range1.max <= mngr->currentSignal.range1.min) {
      throw IrsfException(IrsfError::InvalidRange1Relation);
    }

    if (mngr->currentSignal.secondRangeActive) {
      if (mngr->currentSignal.range2.max <= mngr->currentSignal.range2.min) {
        throw IrsfException(IrsfError::InvalidRange2Relation);
      }

      if (mngr->currentSignal.range2.max >= mngr->currentSignal.range1.min) {
        throw IrsfException(IrsfError::InvalidRangeOverlap);
      }
    }

    if (mngr->currentFormula == nullptr) {
      throw IrsfException(IrsfError::FormulaIsEmpty);
    }

    if (mngr->currentSignal.sound.soundFileName == "") {
      throw IrsfException(IrsfError::InvalidSoundFileName);
    }

    auto qname = ui->le_Signal_Name->text();

    if (qname == "")
      throw IrsfException(IrsfError::InvalidName);

    mngr->SaveSignal(qname.toStdString());

    ShowMessageBox("Signal saved.");

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_btn_Formula_Select_clicked() {
  try {
    windowLoadFormula->show();
    auto formulaList = mngr->GetFormulaList();
    windowLoadFormula->RefreshFormulaList(formulaList);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_btn_TrackSelect_clicked() {
  try {
    windowTrackListEditor->show();
    windowTrackListEditor->SetModeSelectionOnly(true);
    windowTrackListEditor->RefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_btn_SelectTrackSector_clicked() {
  try {
    windowTrackSectorEditor->show();
    windowTrackSectorEditor->EnableSelectionOnlyMode(true);

    std::cout << "Current track id (sig) = " << mngr->currentSignal.trackId
              << std::endl;

    windowTrackSectorEditor->SetCurrentTrack(mngr->currentSignal.trackId,
                                             mngr->currentSignal.trackConfigId);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_btn_LoadTelemetry_clicked() {
  try {
    ui->lbl_Telemetry->setText("None");

    QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open Telemetry File"), "",
                                     tr("IRSF Telemetry Recording (*.itr)"));

    if (fileName == "")
      return;

    mngr->SetActiveTelemetryFile(fileName);

    std::cout << "Telemetry loaded OK. \n";
    ui->lbl_Telemetry->setText(fileName);

    UpdateChart();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_cb_Range2enabled_stateChanged(int arg1) {
  try {
    if (arg1 == 0) {
      ui->le_Range2max->setEnabled(false);
      ui->le_Range2min->setEnabled(false);
      mngr->currentSignal.secondRangeActive = false;
    } else {
      ui->le_Range2max->setEnabled(true);
      ui->le_Range2min->setEnabled(true);
      mngr->currentSignal.secondRangeActive = true;
    }

    slotRefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_le_Range1max_returnPressed() {
  std::string val(ui->le_Range1max->text().toStdString());

  try {
    float n = std::stof(val);

    mngr->currentSignal.range1.max = n;

    std::cout << "Range 1 maximum set to " << n
              << std::endl;  // informational message

    slotRefreshWindow();
  } catch (std::invalid_argument const& e) {
    if (e.what() != nullptr) {
      IrsfException exc =
          IrsfException(IrsfError::InvalidInputRange1, e.what());
      HandleErrorMessage(exc);
    } else {
      IrsfException exc = IrsfException(IrsfError::InvalidInputRange1);
      HandleErrorMessage(exc);
    }

    ui->le_Range1max->setText("");

  } catch (std::out_of_range const& e) {
    if (e.what() != nullptr) {
      IrsfException exc =
          IrsfException(IrsfError::InvalidInputRange1, e.what());
      HandleErrorMessage(exc);
    } else {
      IrsfException exc = IrsfException(IrsfError::InvalidInputRange1);
      HandleErrorMessage(exc);
    }

    ui->le_Range1max->setText("");
  }
}

void WindowSignalEditor::on_le_Range1min_returnPressed() {
  std::string val(ui->le_Range1min->text().toStdString());

  try {
    float n = std::stof(val);

    mngr->currentSignal.range1.min = n;

    std::cout << "Range 1 minimum set to " << n << std::endl;

    slotRefreshWindow();
  } catch (std::invalid_argument const& e) {
    std::cout << "Range 1 min: Bad input. " << e.what() << std::endl;
    ui->le_Range1min->setText("");

    ShowMessageBox("Range 1 minimum : bad input.");

  } catch (std::out_of_range const& e) {
    std::cout << "Range 1 min: Value out of range." << e.what() << std::endl;
    ShowMessageBox("Range 1 minimum : value out of range.");
    ui->le_Range1min->setText("");
  }
}

void WindowSignalEditor::on_le_Range2max_returnPressed() {
  std::string val(ui->le_Range2max->text().toStdString());

  try {
    float n = std::stof(val);

    mngr->currentSignal.range2.max = n;

    std::cout << "Range 2 maximum set to " << n << std::endl;

    slotRefreshWindow();
  } catch (std::invalid_argument const& e) {
    std::cout << "Range 2 max: Bad input. " << e.what() << std::endl;
    ShowMessageBox("Range 2 maximum: bad input.");
    ui->le_Range2max->setText("");

  } catch (std::out_of_range const& e) {
    std::cout << "Range 2 max: Value out of range." << e.what() << std::endl;
    ShowMessageBox("Range 2 maximum : value out of range.");
    ui->le_Range2max->setText("");
  }
}

void WindowSignalEditor::on_le_Range2min_returnPressed() {
  std::string val(ui->le_Range2min->text().toStdString());

  try {
    float n = std::stof(val);

    mngr->currentSignal.range2.min = n;

    std::cout << "Range 2 minimum set to " << n << std::endl;

    slotRefreshWindow();
  } catch (std::invalid_argument const& e) {
    std::cout << "Range 2 min: Bad input. " << e.what() << std::endl;
    ShowMessageBox("Range 2 minimum : bad input.");

    ui->le_Range2min->setText("");

  } catch (std::out_of_range const& e) {
    std::cout << "Range 2 min: Value out of range." << e.what() << std::endl;
    ShowMessageBox("Range 2 minimum : value out of range.");

    ui->le_Range2min->setText("");
  }
}

void WindowSignalEditor::on_btn_SoundSelect_clicked() {
  try {
    ui->le_SoundFilePath->setText("None");

    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Sound File"), "", tr("WAV sound (*.wav)"));

    if (fileName == "") {
      std::cout << "No WAV file selected. \n";
      return;
    } else {
      ui->le_SoundFilePath->setText(fileName);

      mngr->currentSignal.sound.soundFileName = fileName.toStdString();
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_hs_Volume_valueChanged(int value) {
  float fVolume = static_cast<float>(value) / 100.0f;

  mngr->currentSignal.sound.soundVolume = fVolume;
}

void WindowSignalEditor::on_btn_Signal_Load_clicked() {
  try {
    if (mngr->currentSignal.trackId != kTrackIdAllTracks) {
      if (mngr->currentSignal.trackId < 0 ||
          mngr->currentSignal.trackConfigId < 0) {
        std::cout << "Error: you must first select track and track "
                     "configuration before selecting a signal. \n";

        ShowMessageBox(
            "Error: you must first select track and track "
            "configuration before selecting a signal. \n");

        return;
      }
    }

    windowLoadSignal->SetTrack(mngr->currentSignal.trackId,
                               mngr->currentSignal.trackConfigId);

    windowLoadSignal->show();

    windowLoadSignal->RefreshList();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::on_rb_SignalDistance_FullTrack_toggled(bool checked) {
  try {
    if (checked)
      mngr->currentSignal.useFullTrack = true;
    else
      mngr->currentSignal.useFullTrack = false;

    UpdateChart();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::updateRanges() {
  try {
    float mean;
    float stddev;

    if (mngr->valuesAllLaps.size() > 0) {
      float minVal, maxVal, minDist, maxDist;

      FindMeanAndStdDevTelemetryData(mngr->valuesAllLaps, mean, stddev, minVal,
                                     maxVal, minDist, maxDist);
    } else {
      mean = 0.0f;
      stddev = 1.0f;
    }

    if (mngr->currentSignal.secondRangeActive) {
      mngr->currentSignal.range1.max = mean + stddev;
      mngr->currentSignal.range1.min = mean + (stddev * 0.1f);

      mngr->currentSignal.range2.max = mean - (stddev * 0.1f);
      mngr->currentSignal.range2.min = mean - stddev;
    } else {
      mngr->currentSignal.range1.max = mean + stddev;
      mngr->currentSignal.range1.min = mean - stddev;
    }

    slotRefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowSignalEditor::UpdateChart() {
  std::vector<QLineSeries*> series;
  std::vector<QBarSeries*> histSeries;
  float minX, maxX, minY, maxY;

  // first check if telemetry is loaded
  if (mngr->CheckTelemetryLoaded() == false)
    return;

  if (mngr->currentSignal.name == "")
    return;

  chartMain->removeAllSeries();

  mngr->GetSeriesForCurrentSignal(series, minX, maxX, minY, maxY);

  mngr->GetSeriesForRanges(series, minX, maxX);

  for (const auto& cSeries : series) {
    chartMain->addSeries(cSeries);
  }

  chartMain->createDefaultAxes();

  displayChartView->setChart(chartMain);
  displayChartView->setRenderHint(QPainter::Antialiasing);
  displayChartView->setRubberBand(QChartView::RectangleRubberBand);

  chartMain->createDefaultAxes();

  QAbstractAxis* x = chartMain->axisX();

  x->setRange(minX, maxX);

  if (mngr->currentSignal.range1.min < minY)
    minY = mngr->currentSignal.range1.min;

  if (mngr->currentSignal.range1.max > maxY)
    maxY = mngr->currentSignal.range1.max;

  if (mngr->currentSignal.secondRangeActive) {
    if (mngr->currentSignal.range2.min < minY)
      minY = mngr->currentSignal.range2.min;

    if (mngr->currentSignal.range2.max > maxY)
      maxY = mngr->currentSignal.range2.max;
  }

  QAbstractAxis* y = chartMain->axisY();
  y->setRange(minY, maxY);

  SetChart(displayChartView);
}

void WindowSignalEditor::UpdateChartHistogram() {
  QBarSeries* histSeries = new QBarSeries();
  float minX, maxX, minY, maxY;

  mngr->GetSeriesForCurrentSignalHistogram(*histSeries, minX, maxX, minY, maxY);

  chartMain->removeAllSeries();

  chartMain->addSeries(histSeries);

  QStringList categories;

  categories << "1"
             << "2"
             << "3"
             << "4"
             << "5"
             << "6"
             << "7"
             << "8"
             << "9"
             << "10"
             << "11"
             << "12"
             << "13"
             << "14"
             << "15"
             << "16"
             << "17"
             << "18"
             << "19"
             << "20";

  QBarCategoryAxis* axisX = new QBarCategoryAxis();
  axisX->append(categories);
  chartMain->addAxis(axisX, Qt::AlignBottom);
  histSeries->attachAxis(axisX);

  chartMain->legend()->setVisible(true);
  chartMain->legend()->setAlignment(Qt::AlignBottom);

  displayChartView->setRenderHint(QPainter::Antialiasing);

  displayChartView->setChart(chartMain);
  SetChart(displayChartView);
}

void WindowSignalEditor::RefreshWindowCurveIcons() {
  QPixmap mapIcon1("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_1.png");

  QIcon ButtonIcon1(mapIcon1);

  QPixmap mapIcon2("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_2.png");
  QIcon ButtonIcon2(mapIcon2);

  QPixmap mapIcon3("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_3.png");
  QIcon ButtonIcon3(mapIcon3);

  QPixmap mapIcon4("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_4.png");
  QIcon ButtonIcon4(mapIcon4);

  QPixmap mapIcon5("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_5.png");
  QIcon ButtonIcon5(mapIcon5);

  QPixmap mapIcon1sel("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_1sel.png");
  QIcon ButtonIcon1sel(mapIcon1sel);

  QPixmap mapIcon2sel("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_2sel.png");
  QIcon ButtonIcon2sel(mapIcon2sel);

  QPixmap mapIcon3sel("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_3sel.png");
  QIcon ButtonIcon3sel(mapIcon3sel);

  QPixmap mapIcon4sel("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_4sel.png");
  QIcon ButtonIcon4sel(mapIcon4sel);

  QPixmap mapIcon5sel("C:\\Dev\\IRSF\\gui\\irsf-curve_icon_5sel.png");
  QIcon ButtonIcon5sel(mapIcon5sel);

  QPixmap mapIconPlay("C:\\Dev\\IRSF\\gui\\irsf_playSound.png");
  QIcon ButtonIconPlay(mapIconPlay);
  ui->btn_SoundPlay->setIcon(ButtonIconPlay);

  if (mngr->currentSignal.sound.curve == SoundVolumeCurve::Fastest) {
    ui->btn_Curve1->setIcon(ButtonIcon1sel);
    ui->btn_Curve1->setIconSize(mapIcon1sel.rect().size());
    ui->btn_Curve1->setFixedSize(mapIcon1sel.rect().size());
  } else {
    ui->btn_Curve1->setIcon(ButtonIcon1);
    ui->btn_Curve1->setIconSize(mapIcon1.rect().size());
    ui->btn_Curve1->setFixedSize(mapIcon1.rect().size());
  }

  if (mngr->currentSignal.sound.curve == SoundVolumeCurve::Fast) {
    ui->btn_Curve2->setIcon(ButtonIcon2sel);
    ui->btn_Curve2->setIconSize(mapIcon2sel.rect().size());
    ui->btn_Curve2->setFixedSize(mapIcon2sel.rect().size());
  } else {
    ui->btn_Curve2->setIcon(ButtonIcon2);
    ui->btn_Curve2->setIconSize(mapIcon2.rect().size());
    ui->btn_Curve2->setFixedSize(mapIcon2.rect().size());
  }

  if (mngr->currentSignal.sound.curve == SoundVolumeCurve::Linear) {
    ui->btn_Curve3->setIcon(ButtonIcon3sel);
    ui->btn_Curve3->setIconSize(mapIcon3sel.rect().size());
    ui->btn_Curve3->setFixedSize(mapIcon3sel.rect().size());
  } else {
    ui->btn_Curve3->setIcon(ButtonIcon3);
    ui->btn_Curve3->setIconSize(mapIcon3.rect().size());
    ui->btn_Curve3->setFixedSize(mapIcon3.rect().size());
  }

  if (mngr->currentSignal.sound.curve == SoundVolumeCurve::Slow) {
    ui->btn_Curve4->setIcon(ButtonIcon4sel);
    ui->btn_Curve4->setIconSize(mapIcon4sel.rect().size());
    ui->btn_Curve4->setFixedSize(mapIcon4sel.rect().size());
  } else {
    ui->btn_Curve4->setIcon(ButtonIcon4);
    ui->btn_Curve4->setIconSize(mapIcon4.rect().size());
    ui->btn_Curve4->setFixedSize(mapIcon4.rect().size());
  }

  if (mngr->currentSignal.sound.curve == SoundVolumeCurve::Slowest) {
    ui->btn_Curve5->setIcon(ButtonIcon5sel);
    ui->btn_Curve5->setIconSize(mapIcon5sel.rect().size());
    ui->btn_Curve5->setFixedSize(mapIcon5sel.rect().size());
  } else {
    ui->btn_Curve5->setIcon(ButtonIcon5);
    ui->btn_Curve5->setIconSize(mapIcon5.rect().size());
    ui->btn_Curve5->setFixedSize(mapIcon5.rect().size());
  }
}

void WindowSignalEditor::on_btn_Range1auto_clicked() {
  updateRanges();
}

void WindowSignalEditor::on_btn_Range2auto_clicked() {
  updateRanges();
}

void WindowSignalEditor::on_btn_Curve1_clicked() {
  mngr->currentSignal.sound.curve = SoundVolumeCurve::Fastest;

  RefreshWindowCurveIcons();
}

void WindowSignalEditor::on_btn_Curve2_clicked() {
  mngr->currentSignal.sound.curve = SoundVolumeCurve::Fast;

  RefreshWindowCurveIcons();
}

void WindowSignalEditor::on_btn_Curve3_clicked() {
  mngr->currentSignal.sound.curve = SoundVolumeCurve::Linear;

  RefreshWindowCurveIcons();
}

void WindowSignalEditor::on_btn_Curve4_clicked() {
  mngr->currentSignal.sound.curve = SoundVolumeCurve::Slow;

  RefreshWindowCurveIcons();
}

void WindowSignalEditor::on_btn_Curve5_clicked() {
  mngr->currentSignal.sound.curve = SoundVolumeCurve::Slowest;

  RefreshWindowCurveIcons();
}

void WindowSignalEditor::on_le_Signal_Name_textEdited(const QString& arg1) {
  Q_UNUSED(arg1)

  auto qname = ui->le_Signal_Name->text();

  if (qname == "") {
    return;
  }

  mngr->currentSignal.name = qname.toStdString();
}

void WindowSignalEditor::on_btn_SoundPlay_clicked() {
  try {
    if (currentlyPlayingSoundSample == false) {
      int vol = ui->hs_Volume->value();
      float volumeMultiplier = static_cast<float>(vol) / 100.0f;

      std::cout << "Playing audio sample \n";
      mngr->PlaySoundSample(volumeMultiplier);
      currentlyPlayingSoundSample = true;
    } else {
      std::cout << "Stopping audio sample \n";
      mngr->StopSoundSample();
      currentlyPlayingSoundSample = false;
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}


#include "SignalEditorManager.h"
#include <algorithm>
#include "Utilities.h"

using namespace irsf;

SignalEditorManager::SignalEditorManager(TrackDataManager* tdm,
                                         SignalDbManager* sdm,
                                         FormulaDbManager* fdm,
                                         AppDbManager* adm) noexcept
    : formulaDbManager(fdm),
      signalDbManager(sdm),
      trackDataManager(tdm),
      appDbManager(adm) {}

void SignalEditorManager::Initialize() {
  telemetryViewerManager = std::make_unique<TelemetryViewerManager>();
  formulaEvaluator = std::make_unique<FormulaEvaluator>();

  liveManager = std::make_unique<LiveManager>(
      trackDataManager, formulaDbManager, signalDbManager, appDbManager);

  formulaOfflineCalculator = std::make_unique<FormulaOfflineCalculator>(
      formulaDbManager, formulaEvaluator.get());

  InitializeCurrentSignal();
}

std::vector<Formula*>& SignalEditorManager::GetFormulaList() noexcept {
  return formulaDbManager->GetFormulaList();
}

TrackDataManager* SignalEditorManager::GetTrackDataManager() const noexcept {
  return trackDataManager;
}

SignalDbManager* SignalEditorManager::GetSignalDbManager() const noexcept {
  return signalDbManager;
}

void SignalEditorManager::GetTrackAndTrackConfigName(
    std::string& retTrackAndConfigName) const noexcept {
  trackDataManager->GetTrackAndConfigName(currentSignal.trackId,
                                          currentSignal.trackConfigId,
                                          retTrackAndConfigName);

  return;
}

SignalEditorManager::~SignalEditorManager() noexcept {}

void SignalEditorManager::SetActiveTelemetryFile(const QString& fileName) {
  telemetryViewerManager->SetActiveTelemetryFile(fileName);
}

bool SignalEditorManager::CheckTelemetryLoaded() const noexcept {
  if (telemetryViewerManager->GetActiveData()->Data.size() > 0) {
    return true;
  }

  return false;
}

void SignalEditorManager::GetSeriesForCurrentSignal(
    std::vector<QLineSeries*>& retSeries,
    float& minX,
    float& maxX,
    float& minY,
    float& maxY) {
  GenerateValuesAllLaps();

  for (const auto& valuesThisLap : valuesAllLaps) {
    // QT will perform delete on this, so naked new is ok
    QLineSeries* seriesMain = new QLineSeries();

    for (const auto& point : valuesThisLap) {
      seriesMain->append(static_cast<qreal>(point.Distance),
                         static_cast<qreal>(point.Value));
    }

    QPen pen = seriesMain->pen();
    pen.setWidth(1);
    pen.setBrush(QBrush("black"));  // or just pen.setColor("red");
    seriesMain->setPen(pen);
    seriesMain->setPointLabelsVisible(false);

    retSeries.push_back(seriesMain);
  }

  float mean;
  float stddev;
  float minVal, maxVal, minDist, maxDist;
  FindMeanAndStdDevTelemetryData(valuesAllLaps, mean, stddev, minVal, maxVal,
                                 minDist, maxDist);

  minX = minDist;
  maxX = maxDist;
  minY = minVal;
  maxY = maxVal;

  qDebug() << "Mean = " << mean << " StdDev = " << stddev;
}

void SignalEditorManager::GetSeriesForCurrentSignalHistogram(
    QBarSeries& retSeries,
    float& minX,
    float& maxX,
    float& minY,
    float& maxY) {
  GenerateValuesAllLaps();

  float mean;
  float stddev;
  float minVal, maxVal, minDist, maxDist;
  FindMeanAndStdDevTelemetryData(valuesAllLaps, mean, stddev, minVal, maxVal,
                                 minDist, maxDist);

  minX = minDist;
  maxX = maxDist;
  minY = minVal;
  maxY = maxVal;

  qDebug() << "Mean = " << mean << " StdDev = " << stddev;

  size_t BinCount = 20;

  std::vector<int32_t> HistogramBins(BinCount, 0);

  float BinCountF = static_cast<float>(BinCount);

  float valueRange = maxVal - minVal;

  for (const auto& valuesThisLap : valuesAllLaps) {
    for (const auto& point : valuesThisLap) {
      size_t binNumber = static_cast<size_t>(
          floor(BinCountF * ((point.Value - minY) / valueRange)));

      if (binNumber >= BinCount)
        binNumber = BinCount - 1;

      HistogramBins[binNumber]++;
    }
  }

  QBarSet* set0 = new QBarSet("FormulaName");  // QT should later delete this

  qDebug() << "hist = ";
  for (auto binVal : HistogramBins) {
    *set0 << binVal;
    qDebug() << binVal;
  }
  qDebug() << "___ end \n";

  retSeries.append(set0);
}

void SignalEditorManager::GetSeriesForRanges(
    std::vector<QLineSeries*>& retSeries,
    float minX,
    float maxX) const {
  if (currentSignal.name.size() == 0)
    throw IrsfException(IrsfError::NoSignalSelected);

  QLineSeries* seriesMain = new QLineSeries();

  seriesMain->append(static_cast<qreal>(minX),
                     static_cast<qreal>(currentSignal.range1.min));
  seriesMain->append(static_cast<qreal>(maxX),
                     static_cast<qreal>(currentSignal.range1.min));

  QPen pen = seriesMain->pen();
  pen.setWidth(2);
  pen.setBrush(QBrush("red"));
  seriesMain->setPen(pen);
  seriesMain->setPointLabelsVisible(false);

  retSeries.push_back(seriesMain);

  //---

  seriesMain = new QLineSeries();

  seriesMain->append(static_cast<qreal>(minX),
                     static_cast<qreal>(currentSignal.range1.max));
  seriesMain->append(static_cast<qreal>(maxX),
                     static_cast<qreal>(currentSignal.range1.max));

  QPen pen2 = seriesMain->pen();
  pen2.setWidth(2);
  pen2.setBrush(QBrush("green"));
  seriesMain->setPen(pen2);
  seriesMain->setPointLabelsVisible(false);

  retSeries.push_back(seriesMain);

  //---------- second range

  if (currentSignal.secondRangeActive) {
    seriesMain = new QLineSeries();

    seriesMain->append(static_cast<qreal>(minX),
                       static_cast<qreal>(currentSignal.range2.min));
    seriesMain->append(static_cast<qreal>(maxX),
                       static_cast<qreal>(currentSignal.range2.min));

    pen = seriesMain->pen();
    pen.setWidth(2);
    pen.setBrush(QBrush("green"));
    seriesMain->setPen(pen);
    seriesMain->setPointLabelsVisible(false);

    retSeries.push_back(seriesMain);

    //---

    seriesMain = new QLineSeries();

    seriesMain->append(static_cast<qreal>(minX),
                       static_cast<qreal>(currentSignal.range2.max));
    seriesMain->append(static_cast<qreal>(maxX),
                       static_cast<qreal>(currentSignal.range2.max));

    pen2 = seriesMain->pen();
    pen2.setWidth(2);
    pen2.setBrush(QBrush("red"));
    seriesMain->setPen(pen2);
    seriesMain->setPointLabelsVisible(false);

    retSeries.push_back(seriesMain);
  }
}

void SignalEditorManager::SaveSignal(const std::string& name) {
  if (name == "") {
    throw IrsfException(IrsfError::InvalidName);
  }

  currentSignal.name = name;

  return signalDbManager->SaveSignal(currentSignal);
}

void SignalEditorManager::CheckCurrentSignalIsValid() const {
  if (currentSignal.range1.min >= currentSignal.range1.max)
    throw IrsfException(IrsfError::InvalidInputRange1);

  if (currentSignal.secondRangeActive) {
    if (currentSignal.range1.min <= currentSignal.range2.max)
      throw IrsfException(IrsfError::SignalRangesOverlap);

    if (currentSignal.range2.min >= currentSignal.range2.max)
      throw IrsfException(IrsfError::InvalidInputRange2);
  }

  if (currentSignal.formulaName.size() == 0)
    throw IrsfException(IrsfError::FormulaIsEmpty);

  if (currentSignal.sound.soundFileName.size() == 0) {
    throw IrsfException(IrsfError::InvalidSoundFileName);
  }
}

void SignalEditorManager::PlaySoundSample(float volumeMultiplier) const {
  liveManager->InitializeAudioOnly();

  liveManager->PlaySoundSample(volumeMultiplier);
}

void SignalEditorManager::StopSoundSample() const {
  liveManager->StopAudioOnly();
}

void SignalEditorManager::InitializeCurrentSignal() noexcept {
  currentSignal.name = "";
  currentSignal.trackId = 0;
  currentSignal.trackConfigId = 0;
  currentSignal.formulaName = "None";
  currentSignal.range1.min = 0.0;
  currentSignal.range1.max = 1.0;
  currentSignal.secondRangeActive = false;
  currentSignal.range2.min = 0.0;
  currentSignal.range2.max = -1.0;
  currentSignal.useFullTrack = true;
  currentSignal.trackSectorId = kIdNotSelected;
  currentSignal.sound.soundFileName = "None";
  currentSignal.sound.soundVolume = 1.0;
  currentSignal.sound.curve = SoundVolumeCurve::Linear;
}

void SignalEditorManager::GenerateValuesAllLaps() {
  TrackSector ts;
  std::vector<TelemetryChartDataPoint> valuesThisLap;
  std::vector<int32_t> LapNumbersInData;

  float startDistance = 0.0;
  float endDistance = FLT_MAX;

  if (currentSignal.useFullTrack == false) {
    auto tsret = trackDataManager->GetTrackSector(currentSignal.trackSectorId);

    if (tsret.has_value()) {
      ts = tsret.value();

      startDistance = ts.startDistance;
      endDistance = ts.endDistance;
    }
  }

  auto lam = [&](auto& lapInfo) { return lapInfo.first; };

  auto& li = telemetryViewerManager->GetActiveData()->LapIndex;

  std::transform(li.begin(), li.end(), std::back_inserter(LapNumbersInData),
                 lam);

  valuesAllLaps.clear();

  IrsfSignal* cs = &currentSignal;

  for (const auto& lapNumber : LapNumbersInData) {
    valuesThisLap.clear();

    try {
      formulaOfflineCalculator->CalculateFormulaForRangeOneLap(
          telemetryViewerManager->GetActiveData(), cs, startDistance,
          endDistance, lapNumber, valuesThisLap);
    } catch (IrsfException& err) {
      if (err.GetError() != IrsfError::NoValuesInSelectedTelemetryRange) {
        throw;
      }

    } catch (...) {
      throw;
    }

    valuesAllLaps.push_back(valuesThisLap);
  }
}

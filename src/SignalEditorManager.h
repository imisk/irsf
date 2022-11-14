
#ifndef SIGNALEDITORMANAGER_H
#define SIGNALEDITORMANAGER_H

#include "AppDbManager.h"
#include "FormulaDbManager.h"
#include "FormulaEvaluator.h"
#include "FormulaOfflineCalculator.h"
#include "LiveManager.h"
#include "QBarSeries"
#include "QBarSet"
#include "SignalDbManager.h"
#include "TelemetryViewerManager.h"
#include "TrackDataManager.h"

namespace irsf {
/*
 * Signal editor class for all functionality of the signal editor window.
 * Edits signals, various utility functions, and updates the editor visual chart
 */
class SignalEditorManager {
 public:
  explicit SignalEditorManager(TrackDataManager* tdm,
                               SignalDbManager* sdm,
                               FormulaDbManager* fdm,
                               AppDbManager* adm) noexcept;

  virtual ~SignalEditorManager() noexcept;

  void Initialize();

  std::vector<Formula*>& GetFormulaList() noexcept;

  TrackDataManager* GetTrackDataManager() const noexcept;

  SignalDbManager* GetSignalDbManager() const noexcept;

  void GetTrackAndTrackConfigName(
      std::string& retTrackAndConfigName) const noexcept;

  void SetActiveTelemetryFile(const QString& fileName);

  bool CheckTelemetryLoaded() const noexcept;

  void GetSeriesForCurrentSignal(std::vector<QLineSeries*>& retSeries,
                                 float& minX,
                                 float& maxX,
                                 float& minY,
                                 float& maxY);

  void GetSeriesForCurrentSignalHistogram(QBarSeries& retSeries,
                                          float& minX,
                                          float& maxX,
                                          float& minY,
                                          float& maxY);

  // Draw the red/green lines to show active ranges
  void GetSeriesForRanges(std::vector<QLineSeries*>& retSeries,
                          float minX,
                          float maxX) const;

  // Save the current signal to database
  void SaveSignal(const std::string& name);

  IrsfSignal currentSignal;

  Formula* currentFormula{nullptr};

  // List of values for each lap for data that is currently displayed
  std::vector<std::vector<TelemetryChartDataPoint>> valuesAllLaps;

  void CheckCurrentSignalIsValid() const;

  // Plays single sound sample
  void PlaySoundSample(float volumeMultiplier) const;

  void StopSoundSample() const;

 private:
  // Give default values to currentSignal
  void InitializeCurrentSignal() noexcept;

  // Generate values for the signal for all laps, which will
  // be used to display the telemetry chart.
  void GenerateValuesAllLaps();

  FormulaDbManager* formulaDbManager;
  SignalDbManager* signalDbManager;
  TrackDataManager* trackDataManager;
  AppDbManager* appDbManager;

  std::unique_ptr<TelemetryViewerManager> telemetryViewerManager;

  std::unique_ptr<FormulaEvaluator> formulaEvaluator;
  std::unique_ptr<FormulaOfflineCalculator> formulaOfflineCalculator;
  std::unique_ptr<LiveManager> liveManager;
};
}  // namespace irsf
#endif  // SIGNALEDITORMANAGER_H

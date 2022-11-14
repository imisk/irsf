#ifndef UTILITIES_H
#define UTILITIES_H

#include <sstream>
#include <string>
#include <vector>
#include "IrsfCommon.h"

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <limits>
namespace irsf {

/*
 * kVariableProcessedIdStart
 * all values which are equal or larger than this value belong to the Processed
 * variable id types (to be implemented)
 * note: I don't like this system. Should be different enum classes.
 */
constexpr int32_t kVariableProcessedIdStart = 2000;

VariableId GetVariableIdFromVariableName(const std::string& name) noexcept;

std::string GetVariableNameFromVariableId(const VariableId& id) noexcept;

std::vector<std::string> GetNamesOfAllInputVariableRawAndDerived();

void NormaliseFloatVector(std::vector<TelemetryChartDataPoint>& values,
                          float maxValue) noexcept;

/*
 * get only a single lap data series for a given VariableId
 * (one lap, one distance range, one variable, normalized on/off)
 */
void GetSingleDataSeries(TelemetryData* data,
                         std::vector<TelemetryChartDataPoint>& retValues,
                         int32_t lapNumber,
                         float minimumDistance,
                         float maximumDistance,
                         VariableId varId,
                         bool isNormalized);

/* Creates data series based on TelemetryData data and
 * the assigned options, and sets these series to show
 * in the chart.
 */
void CreateDataSeriesFromTelemetry(
    TelemetryViewerOptionsForChart& options,
    QChart* chart,
    TelemetryData* data,
    const std::vector<QBrush>& variableIdColours);

/* Create a list of ints from the input string which
 * is in a comma delimited format.
 */
void CreateIntListFromCommaDelimitedText(std::vector<int32_t>& retVector,
                                         QString& inString);

void FindMaxValueOfVariable(TelemetryData* data,
                            VariableId varId,
                            float& retValue);

bool IsVariableIdForProcessedVariable(VariableId varId) noexcept;

void FindMeanAndStdDevTelemetryData(
    std::vector<std::vector<TelemetryChartDataPoint>> data,
    float& retMean,
    float& retStdDev,
    float& retMinValue,
    float& retMaxValue,
    float& retMinDist,
    float& retMaxDist) noexcept;

std::string BrakeMarkerToString(BrakeMarker& bm);
}  // namespace irsf

#endif  // UTILITIES_H

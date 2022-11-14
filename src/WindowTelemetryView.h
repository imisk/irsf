#ifndef WINDOWTELEMETRYVIEW_H
#define WINDOWTELEMETRYVIEW_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

// QT_CHARTS_USE_NAMESPACE

namespace Ui {
class WindowTelemetryView;
}

class WindowTelemetryView final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowTelemetryView(QWidget* parent = nullptr);
  ~WindowTelemetryView() final;

  void SetChart(QChartView* c);

 private slots:
  void on_WindowTelemetryView_accepted();

 private:
  Ui::WindowTelemetryView* ui;

  QChartView* chart;
};

#endif  // WINDOWTELEMETRYVIEW_H

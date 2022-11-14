
#include "WindowTelemetryView.h"
#include "ErrorMessageBoxUtility.h"
#include "QDebug"
#include "ui_WindowTelemetryView.h"

using namespace irsf;

WindowTelemetryView::WindowTelemetryView(QWidget* parent)
    : QDialog(parent), ui(new Ui::WindowTelemetryView) {
  ui->setupUi(this);
}

WindowTelemetryView::~WindowTelemetryView() {
  delete ui;
}

void WindowTelemetryView::SetChart(QChartView* c) {
  chart = c;

  chart->setRubberBand(QChartView::RectangleRubberBand);

  QVBoxLayout* layoutDialog = new QVBoxLayout(this);
  QWidget* widget = new QWidget();
  QVBoxLayout* layoutWidget = new QVBoxLayout(widget);

  layoutDialog->addWidget(widget);
  layoutWidget->addWidget(c);
}

void WindowTelemetryView::on_WindowTelemetryView_accepted() {
  try {
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

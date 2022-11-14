/********************************************************************************
** Form generated from reading UI file 'WindowTelemetryViewerOptions.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWTELEMETRYVIEWEROPTIONS_H
#define UI_WINDOWTELEMETRYVIEWEROPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowTelemetryViewerOptions
{
public:
    QPushButton *btn_ShowChart;
    QLabel *lbl_LoadedTelemetry;
    QLabel *lbl_CurrentTelemetryFilename;
    QPushButton *btn_LoadTelemetry;
    QGroupBox *group_AddVariable;
    QComboBox *cb_AddVariable;
    QPushButton *btn_AddVariable;
    QListWidget *lb_VariablesOnChart;
    QLabel *lbl_AddedVars;
    QGroupBox *group_Lap;
    QCheckBox *cb_Laps_AllLaps;
    QLineEdit *le_Laps;
    QGroupBox *group_XAxis;
    QLineEdit *le_DistanceStart;
    QLineEdit *le_DistanceEnd;
    QLabel *lbl_DistanceStart;
    QLabel *lbl_DistanceEnd;
    QPushButton *btn_DistanceMax;
    QPushButton *btn_DistanceZoomIn;
    QPushButton *btn_DistanceZoomOut;
    QPushButton *btn_DistanceLeft;
    QPushButton *btn_DistanceRight;
    QPushButton *btn_ClearVariables;

    void setupUi(QDialog *WindowTelemetryViewerOptions)
    {
        if (WindowTelemetryViewerOptions->objectName().isEmpty())
            WindowTelemetryViewerOptions->setObjectName(QString::fromUtf8("WindowTelemetryViewerOptions"));
        WindowTelemetryViewerOptions->resize(404, 436);
        btn_ShowChart = new QPushButton(WindowTelemetryViewerOptions);
        btn_ShowChart->setObjectName(QString::fromUtf8("btn_ShowChart"));
        btn_ShowChart->setGeometry(QRect(270, 50, 111, 31));
        lbl_LoadedTelemetry = new QLabel(WindowTelemetryViewerOptions);
        lbl_LoadedTelemetry->setObjectName(QString::fromUtf8("lbl_LoadedTelemetry"));
        lbl_LoadedTelemetry->setGeometry(QRect(20, 20, 101, 21));
        lbl_CurrentTelemetryFilename = new QLabel(WindowTelemetryViewerOptions);
        lbl_CurrentTelemetryFilename->setObjectName(QString::fromUtf8("lbl_CurrentTelemetryFilename"));
        lbl_CurrentTelemetryFilename->setGeometry(QRect(120, 20, 411, 21));
        btn_LoadTelemetry = new QPushButton(WindowTelemetryViewerOptions);
        btn_LoadTelemetry->setObjectName(QString::fromUtf8("btn_LoadTelemetry"));
        btn_LoadTelemetry->setGeometry(QRect(20, 50, 90, 22));
        group_AddVariable = new QGroupBox(WindowTelemetryViewerOptions);
        group_AddVariable->setObjectName(QString::fromUtf8("group_AddVariable"));
        group_AddVariable->setGeometry(QRect(20, 90, 221, 91));
        cb_AddVariable = new QComboBox(group_AddVariable);
        cb_AddVariable->setObjectName(QString::fromUtf8("cb_AddVariable"));
        cb_AddVariable->setGeometry(QRect(10, 30, 201, 22));
        btn_AddVariable = new QPushButton(group_AddVariable);
        btn_AddVariable->setObjectName(QString::fromUtf8("btn_AddVariable"));
        btn_AddVariable->setGeometry(QRect(130, 60, 80, 22));
        lb_VariablesOnChart = new QListWidget(WindowTelemetryViewerOptions);
        lb_VariablesOnChart->setObjectName(QString::fromUtf8("lb_VariablesOnChart"));
        lb_VariablesOnChart->setGeometry(QRect(20, 220, 221, 171));
        lbl_AddedVars = new QLabel(WindowTelemetryViewerOptions);
        lbl_AddedVars->setObjectName(QString::fromUtf8("lbl_AddedVars"));
        lbl_AddedVars->setGeometry(QRect(20, 200, 111, 16));
        group_Lap = new QGroupBox(WindowTelemetryViewerOptions);
        group_Lap->setObjectName(QString::fromUtf8("group_Lap"));
        group_Lap->setGeometry(QRect(250, 90, 141, 91));
        cb_Laps_AllLaps = new QCheckBox(group_Lap);
        cb_Laps_AllLaps->setObjectName(QString::fromUtf8("cb_Laps_AllLaps"));
        cb_Laps_AllLaps->setGeometry(QRect(10, 60, 72, 20));
        le_Laps = new QLineEdit(group_Lap);
        le_Laps->setObjectName(QString::fromUtf8("le_Laps"));
        le_Laps->setGeometry(QRect(10, 30, 101, 21));
        group_XAxis = new QGroupBox(WindowTelemetryViewerOptions);
        group_XAxis->setObjectName(QString::fromUtf8("group_XAxis"));
        group_XAxis->setGeometry(QRect(250, 200, 141, 151));
        le_DistanceStart = new QLineEdit(group_XAxis);
        le_DistanceStart->setObjectName(QString::fromUtf8("le_DistanceStart"));
        le_DistanceStart->setGeometry(QRect(60, 30, 71, 21));
        le_DistanceEnd = new QLineEdit(group_XAxis);
        le_DistanceEnd->setObjectName(QString::fromUtf8("le_DistanceEnd"));
        le_DistanceEnd->setGeometry(QRect(60, 60, 71, 21));
        lbl_DistanceStart = new QLabel(group_XAxis);
        lbl_DistanceStart->setObjectName(QString::fromUtf8("lbl_DistanceStart"));
        lbl_DistanceStart->setGeometry(QRect(20, 30, 47, 14));
        lbl_DistanceEnd = new QLabel(group_XAxis);
        lbl_DistanceEnd->setObjectName(QString::fromUtf8("lbl_DistanceEnd"));
        lbl_DistanceEnd->setGeometry(QRect(20, 60, 47, 14));
        btn_DistanceMax = new QPushButton(group_XAxis);
        btn_DistanceMax->setObjectName(QString::fromUtf8("btn_DistanceMax"));
        btn_DistanceMax->setGeometry(QRect(20, 90, 41, 22));
        btn_DistanceZoomIn = new QPushButton(group_XAxis);
        btn_DistanceZoomIn->setObjectName(QString::fromUtf8("btn_DistanceZoomIn"));
        btn_DistanceZoomIn->setGeometry(QRect(100, 90, 21, 22));
        btn_DistanceZoomOut = new QPushButton(group_XAxis);
        btn_DistanceZoomOut->setObjectName(QString::fromUtf8("btn_DistanceZoomOut"));
        btn_DistanceZoomOut->setGeometry(QRect(70, 90, 21, 22));
        btn_DistanceLeft = new QPushButton(group_XAxis);
        btn_DistanceLeft->setObjectName(QString::fromUtf8("btn_DistanceLeft"));
        btn_DistanceLeft->setGeometry(QRect(20, 120, 51, 22));
        btn_DistanceRight = new QPushButton(group_XAxis);
        btn_DistanceRight->setObjectName(QString::fromUtf8("btn_DistanceRight"));
        btn_DistanceRight->setGeometry(QRect(80, 120, 51, 22));
        btn_ClearVariables = new QPushButton(WindowTelemetryViewerOptions);
        btn_ClearVariables->setObjectName(QString::fromUtf8("btn_ClearVariables"));
        btn_ClearVariables->setGeometry(QRect(160, 400, 80, 22));

        retranslateUi(WindowTelemetryViewerOptions);

        QMetaObject::connectSlotsByName(WindowTelemetryViewerOptions);
    } // setupUi

    void retranslateUi(QDialog *WindowTelemetryViewerOptions)
    {
        WindowTelemetryViewerOptions->setWindowTitle(QCoreApplication::translate("WindowTelemetryViewerOptions", "Telemetry viewer options", nullptr));
        btn_ShowChart->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Show Chart", nullptr));
        lbl_LoadedTelemetry->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Loaded telemetry:", nullptr));
        lbl_CurrentTelemetryFilename->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "None", nullptr));
        btn_LoadTelemetry->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Load Telemetry", nullptr));
        group_AddVariable->setTitle(QCoreApplication::translate("WindowTelemetryViewerOptions", "Add variable to chart:", nullptr));
        btn_AddVariable->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Add", nullptr));
        lbl_AddedVars->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Variables on chart:", nullptr));
        group_Lap->setTitle(QCoreApplication::translate("WindowTelemetryViewerOptions", "Laps to show: (, delim)", nullptr));
        cb_Laps_AllLaps->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "All laps", nullptr));
#if QT_CONFIG(tooltip)
        le_Laps->setToolTip(QCoreApplication::translate("WindowTelemetryViewerOptions", "You can specify certain lap with a comma (,) delimited list. Lap 0 is the first lap.", nullptr));
#endif // QT_CONFIG(tooltip)
        le_Laps->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "1", nullptr));
        group_XAxis->setTitle(QCoreApplication::translate("WindowTelemetryViewerOptions", "Distance to show:", nullptr));
        lbl_DistanceStart->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Start:", nullptr));
        lbl_DistanceEnd->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "End:", nullptr));
        btn_DistanceMax->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Max", nullptr));
        btn_DistanceZoomIn->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "+", nullptr));
        btn_DistanceZoomOut->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "-", nullptr));
        btn_DistanceLeft->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "<--", nullptr));
        btn_DistanceRight->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "-->", nullptr));
        btn_ClearVariables->setText(QCoreApplication::translate("WindowTelemetryViewerOptions", "Clear all", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowTelemetryViewerOptions: public Ui_WindowTelemetryViewerOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWTELEMETRYVIEWEROPTIONS_H

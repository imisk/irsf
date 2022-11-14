/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *btn_TelemetryViewer;
    QPushButton *btn_FormulaEditor;
    QPushButton *btn_TrackListEditor;
    QPushButton *btn_SignalEditor;
    QPushButton *btn_TsEditor;
    QPushButton *btn_Live;
    QPushButton *btn_SignalSetEditor;
    QPushButton *btn_BrakeMarkerEditor;
    QPushButton *btn_Config;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(537, 412);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 20, 111, 31));
        btn_TelemetryViewer = new QPushButton(centralwidget);
        btn_TelemetryViewer->setObjectName(QString::fromUtf8("btn_TelemetryViewer"));
        btn_TelemetryViewer->setGeometry(QRect(250, 20, 121, 41));
        btn_FormulaEditor = new QPushButton(centralwidget);
        btn_FormulaEditor->setObjectName(QString::fromUtf8("btn_FormulaEditor"));
        btn_FormulaEditor->setGeometry(QRect(330, 90, 101, 31));
        btn_TrackListEditor = new QPushButton(centralwidget);
        btn_TrackListEditor->setObjectName(QString::fromUtf8("btn_TrackListEditor"));
        btn_TrackListEditor->setGeometry(QRect(330, 150, 121, 22));
        btn_SignalEditor = new QPushButton(centralwidget);
        btn_SignalEditor->setObjectName(QString::fromUtf8("btn_SignalEditor"));
        btn_SignalEditor->setGeometry(QRect(330, 200, 80, 22));
        btn_TsEditor = new QPushButton(centralwidget);
        btn_TsEditor->setObjectName(QString::fromUtf8("btn_TsEditor"));
        btn_TsEditor->setGeometry(QRect(330, 240, 80, 22));
        btn_Live = new QPushButton(centralwidget);
        btn_Live->setObjectName(QString::fromUtf8("btn_Live"));
        btn_Live->setGeometry(QRect(60, 170, 80, 22));
        btn_SignalSetEditor = new QPushButton(centralwidget);
        btn_SignalSetEditor->setObjectName(QString::fromUtf8("btn_SignalSetEditor"));
        btn_SignalSetEditor->setGeometry(QRect(330, 280, 101, 31));
        btn_BrakeMarkerEditor = new QPushButton(centralwidget);
        btn_BrakeMarkerEditor->setObjectName(QString::fromUtf8("btn_BrakeMarkerEditor"));
        btn_BrakeMarkerEditor->setGeometry(QRect(60, 240, 141, 24));
        btn_Config = new QPushButton(centralwidget);
        btn_Config->setObjectName(QString::fromUtf8("btn_Config"));
        btn_Config->setGeometry(QRect(60, 290, 131, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 537, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Run TestBed", nullptr));
        btn_TelemetryViewer->setText(QCoreApplication::translate("MainWindow", "Telemetry Viewer", nullptr));
        btn_FormulaEditor->setText(QCoreApplication::translate("MainWindow", "Formula Editor", nullptr));
        btn_TrackListEditor->setText(QCoreApplication::translate("MainWindow", "Track List Editor", nullptr));
        btn_SignalEditor->setText(QCoreApplication::translate("MainWindow", "Signal Editor", nullptr));
        btn_TsEditor->setText(QCoreApplication::translate("MainWindow", "TS edit", nullptr));
        btn_Live->setText(QCoreApplication::translate("MainWindow", "Live", nullptr));
        btn_SignalSetEditor->setText(QCoreApplication::translate("MainWindow", "Signal Set Editor", nullptr));
        btn_BrakeMarkerEditor->setText(QCoreApplication::translate("MainWindow", "Brake marker editor", nullptr));
        btn_Config->setText(QCoreApplication::translate("MainWindow", "App config", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

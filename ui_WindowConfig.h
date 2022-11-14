/********************************************************************************
** Form generated from reading UI file 'WindowConfig.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWCONFIG_H
#define UI_WINDOWCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_WindowConfig
{
public:
    QGroupBox *groupBox;
    QListWidget *lb_TelSelected;
    QLabel *lbl_Sel;
    QPushButton *btn_TelAdd;
    QPushButton *btn_TelRemove;
    QLabel *lbl_Avail;
    QListWidget *lb_TelAvailable;
    QPushButton *btn_TelDefault;
    QLineEdit *le_MaxTicksInMemory;
    QLabel *label_9;
    QGroupBox *groupBox_2;
    QLineEdit *le_FrameCount;
    QLabel *label;
    QLineEdit *le_Channels;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *le_SampleRate;
    QGroupBox *groupBox_3;
    QLabel *label_4;
    QLineEdit *le_DelayBetweenBeeps;
    QLineEdit *le_LoopLength;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *le_Latency;
    QLabel *label_7;
    QLineEdit *le_NextLapDetection;
    QLabel *label_8;
    QSlider *hs_Volume;
    QLabel *lbl_Volume;
    QGroupBox *gb_Marker;
    QLineEdit *le_FileNameMarker;
    QGroupBox *gb_PreMarker;
    QLineEdit *le_FileNamePreMarker;
    QPushButton *btn_ResetAllToDefault;
    QPushButton *btn_Save;

    void setupUi(QDialog *WindowConfig)
    {
        if (WindowConfig->objectName().isEmpty())
            WindowConfig->setObjectName(QString::fromUtf8("WindowConfig"));
        WindowConfig->resize(830, 588);
        groupBox = new QGroupBox(WindowConfig);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 531, 351));
        lb_TelSelected = new QListWidget(groupBox);
        lb_TelSelected->setObjectName(QString::fromUtf8("lb_TelSelected"));
        lb_TelSelected->setGeometry(QRect(10, 50, 221, 251));
        lbl_Sel = new QLabel(groupBox);
        lbl_Sel->setObjectName(QString::fromUtf8("lbl_Sel"));
        lbl_Sel->setGeometry(QRect(10, 30, 61, 16));
        btn_TelAdd = new QPushButton(groupBox);
        btn_TelAdd->setObjectName(QString::fromUtf8("btn_TelAdd"));
        btn_TelAdd->setGeometry(QRect(240, 90, 41, 24));
        btn_TelRemove = new QPushButton(groupBox);
        btn_TelRemove->setObjectName(QString::fromUtf8("btn_TelRemove"));
        btn_TelRemove->setGeometry(QRect(240, 120, 41, 24));
        lbl_Avail = new QLabel(groupBox);
        lbl_Avail->setObjectName(QString::fromUtf8("lbl_Avail"));
        lbl_Avail->setGeometry(QRect(290, 30, 61, 16));
        lb_TelAvailable = new QListWidget(groupBox);
        lb_TelAvailable->setObjectName(QString::fromUtf8("lb_TelAvailable"));
        lb_TelAvailable->setGeometry(QRect(290, 50, 221, 251));
        btn_TelDefault = new QPushButton(groupBox);
        btn_TelDefault->setObjectName(QString::fromUtf8("btn_TelDefault"));
        btn_TelDefault->setGeometry(QRect(10, 310, 221, 24));
        le_MaxTicksInMemory = new QLineEdit(groupBox);
        le_MaxTicksInMemory->setObjectName(QString::fromUtf8("le_MaxTicksInMemory"));
        le_MaxTicksInMemory->setGeometry(QRect(432, 310, 81, 24));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(290, 320, 131, 16));
        groupBox_2 = new QGroupBox(WindowConfig);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 380, 321, 151));
        le_FrameCount = new QLineEdit(groupBox_2);
        le_FrameCount->setObjectName(QString::fromUtf8("le_FrameCount"));
        le_FrameCount->setGeometry(QRect(90, 30, 61, 24));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 81, 16));
        le_Channels = new QLineEdit(groupBox_2);
        le_Channels->setObjectName(QString::fromUtf8("le_Channels"));
        le_Channels->setGeometry(QRect(90, 60, 61, 24));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 81, 16));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 100, 71, 16));
        le_SampleRate = new QLineEdit(groupBox_2);
        le_SampleRate->setObjectName(QString::fromUtf8("le_SampleRate"));
        le_SampleRate->setGeometry(QRect(90, 90, 61, 24));
        groupBox_3 = new QGroupBox(WindowConfig);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(570, 20, 231, 351));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 100, 121, 16));
        le_DelayBetweenBeeps = new QLineEdit(groupBox_3);
        le_DelayBetweenBeeps->setObjectName(QString::fromUtf8("le_DelayBetweenBeeps"));
        le_DelayBetweenBeeps->setGeometry(QRect(140, 90, 61, 24));
        le_LoopLength = new QLineEdit(groupBox_3);
        le_LoopLength->setObjectName(QString::fromUtf8("le_LoopLength"));
        le_LoopLength->setGeometry(QRect(140, 30, 61, 24));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 70, 121, 16));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 40, 81, 16));
        le_Latency = new QLineEdit(groupBox_3);
        le_Latency->setObjectName(QString::fromUtf8("le_Latency"));
        le_Latency->setGeometry(QRect(140, 60, 61, 24));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 130, 121, 16));
        le_NextLapDetection = new QLineEdit(groupBox_3);
        le_NextLapDetection->setObjectName(QString::fromUtf8("le_NextLapDetection"));
        le_NextLapDetection->setGeometry(QRect(140, 120, 61, 24));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 160, 121, 16));
        hs_Volume = new QSlider(groupBox_3);
        hs_Volume->setObjectName(QString::fromUtf8("hs_Volume"));
        hs_Volume->setGeometry(QRect(10, 180, 201, 16));
        hs_Volume->setValue(50);
        hs_Volume->setOrientation(Qt::Horizontal);
        lbl_Volume = new QLabel(groupBox_3);
        lbl_Volume->setObjectName(QString::fromUtf8("lbl_Volume"));
        lbl_Volume->setGeometry(QRect(140, 160, 49, 16));
        gb_Marker = new QGroupBox(groupBox_3);
        gb_Marker->setObjectName(QString::fromUtf8("gb_Marker"));
        gb_Marker->setGeometry(QRect(10, 200, 211, 61));
        le_FileNameMarker = new QLineEdit(gb_Marker);
        le_FileNameMarker->setObjectName(QString::fromUtf8("le_FileNameMarker"));
        le_FileNameMarker->setGeometry(QRect(10, 30, 191, 24));
        le_FileNameMarker->setReadOnly(false);
        gb_PreMarker = new QGroupBox(groupBox_3);
        gb_PreMarker->setObjectName(QString::fromUtf8("gb_PreMarker"));
        gb_PreMarker->setGeometry(QRect(10, 270, 211, 61));
        le_FileNamePreMarker = new QLineEdit(gb_PreMarker);
        le_FileNamePreMarker->setObjectName(QString::fromUtf8("le_FileNamePreMarker"));
        le_FileNamePreMarker->setGeometry(QRect(10, 30, 191, 24));
        le_FileNamePreMarker->setReadOnly(false);
        btn_ResetAllToDefault = new QPushButton(WindowConfig);
        btn_ResetAllToDefault->setObjectName(QString::fromUtf8("btn_ResetAllToDefault"));
        btn_ResetAllToDefault->setGeometry(QRect(640, 550, 181, 24));
        btn_Save = new QPushButton(WindowConfig);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        btn_Save->setGeometry(QRect(10, 550, 181, 24));

        retranslateUi(WindowConfig);

        QMetaObject::connectSlotsByName(WindowConfig);
    } // setupUi

    void retranslateUi(QDialog *WindowConfig)
    {
        WindowConfig->setWindowTitle(QCoreApplication::translate("WindowConfig", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WindowConfig", "Telemetry recording: variable selection", nullptr));
        lbl_Sel->setText(QCoreApplication::translate("WindowConfig", "Selected:", nullptr));
        btn_TelAdd->setText(QCoreApplication::translate("WindowConfig", "<<", nullptr));
        btn_TelRemove->setText(QCoreApplication::translate("WindowConfig", ">>", nullptr));
        lbl_Avail->setText(QCoreApplication::translate("WindowConfig", "Available:", nullptr));
        btn_TelDefault->setText(QCoreApplication::translate("WindowConfig", "Reset to default", nullptr));
#if QT_CONFIG(tooltip)
        le_MaxTicksInMemory->setToolTip(QCoreApplication::translate("WindowConfig", "<html><head/><body><p>When recording telemetry, how many maximum ticks (frames) to hold in memory before writing to disk. Lower number means more frequent disk writes.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_9->setText(QCoreApplication::translate("WindowConfig", "Max ticks in memory:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WindowConfig", "Sound:", nullptr));
#if QT_CONFIG(tooltip)
        le_FrameCount->setToolTip(QCoreApplication::translate("WindowConfig", "Lower values reduce latency but might introduce audio problems. ", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("WindowConfig", "Frame count:", nullptr));
#if QT_CONFIG(tooltip)
        le_Channels->setToolTip(QCoreApplication::translate("WindowConfig", "2 for stereo 1 for mono", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("WindowConfig", "Channels:", nullptr));
        label_3->setText(QCoreApplication::translate("WindowConfig", "Sample rate:", nullptr));
#if QT_CONFIG(tooltip)
        le_SampleRate->setToolTip(QCoreApplication::translate("WindowConfig", "this should match the sample rate of your audio files", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QCoreApplication::translate("WindowConfig", "Brake marker options:", nullptr));
        label_4->setText(QCoreApplication::translate("WindowConfig", "Delay between beeps:", nullptr));
#if QT_CONFIG(tooltip)
        le_DelayBetweenBeeps->setToolTip(QCoreApplication::translate("WindowConfig", "Time delay between beeps in milliseconds.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        le_LoopLength->setToolTip(QCoreApplication::translate("WindowConfig", "<html><head/><body><p>How many refresh frames does your marker audio file (loop) last ? If your marker sound is being cut too soon, increase this. If your marker sound starts looping, decrease this.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("WindowConfig", "Expected latency (ms):", nullptr));
        label_6->setText(QCoreApplication::translate("WindowConfig", "Loop length:", nullptr));
#if QT_CONFIG(tooltip)
        le_Latency->setToolTip(QCoreApplication::translate("WindowConfig", "Expected latency of your sound card. Integrated sound cards are around 200ms, VR headsets and dedicated sound cards are around 10-15. ", nullptr));
#endif // QT_CONFIG(tooltip)
        label_7->setText(QCoreApplication::translate("WindowConfig", "Next lap detection (m):", nullptr));
#if QT_CONFIG(tooltip)
        le_NextLapDetection->setToolTip(QCoreApplication::translate("WindowConfig", "Once lap distance is between 0 and this value, next lap is detected. Don't place markers before this distance.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_8->setText(QCoreApplication::translate("WindowConfig", "Volume multiplier:", nullptr));
        lbl_Volume->setText(QCoreApplication::translate("WindowConfig", "0", nullptr));
        gb_Marker->setTitle(QCoreApplication::translate("WindowConfig", "Marker WAV file:", nullptr));
#if QT_CONFIG(tooltip)
        le_FileNameMarker->setToolTip(QCoreApplication::translate("WindowConfig", "For example \"marker.wav\" located in the sounds folder", nullptr));
#endif // QT_CONFIG(tooltip)
        gb_PreMarker->setTitle(QCoreApplication::translate("WindowConfig", "Pre-Marker WAV file:", nullptr));
#if QT_CONFIG(tooltip)
        le_FileNamePreMarker->setToolTip(QCoreApplication::translate("WindowConfig", "For example \"marker.wav\" located in the sounds folder", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_ResetAllToDefault->setText(QCoreApplication::translate("WindowConfig", "Reset all to default", nullptr));
        btn_Save->setText(QCoreApplication::translate("WindowConfig", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowConfig: public Ui_WindowConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWCONFIG_H

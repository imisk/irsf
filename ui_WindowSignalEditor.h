/********************************************************************************
** Form generated from reading UI file 'WindowSignalEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWSIGNALEDITOR_H
#define UI_WINDOWSIGNALEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowSignalEditor
{
public:
    QGroupBox *gb_Signal;
    QLabel *lbl_Signal_Name;
    QLineEdit *le_Signal_Name;
    QPushButton *btn_Signal_Save;
    QPushButton *btn_Signal_Load;
    QGroupBox *gb_Formula;
    QLabel *lbl_Formula;
    QPushButton *btn_Formula_Select;
    QGroupBox *gb_SignalDistance;
    QRadioButton *rb_SignalDistance_FullTrack;
    QRadioButton *rb_SignalDistance_TrackSector;
    QLabel *lbl_TrackSectorName;
    QPushButton *btn_SelectTrackSector;
    QGroupBox *gb_Range1;
    QLabel *lbl_Range1min;
    QLabel *lbl_Range1max;
    QLineEdit *le_Range1max;
    QLineEdit *le_Range1min;
    QPushButton *btn_Range1auto;
    QGroupBox *gb_Range2;
    QLabel *lbl_Range2min;
    QLabel *lbl_Range2max;
    QLineEdit *le_Range2max;
    QLineEdit *le_Range2min;
    QCheckBox *cb_Range2enabled;
    QPushButton *btn_Range2auto;
    QGroupBox *gb_Telemetry;
    QLabel *lbl_Telemetry;
    QPushButton *btn_LoadTelemetry;
    QGroupBox *gb_Sound;
    QPushButton *btn_SoundSelect;
    QLabel *lbl_VolumeCurve;
    QPushButton *btn_Curve1;
    QLabel *lbl_Volume;
    QSlider *hs_Volume;
    QPushButton *btn_Curve2;
    QPushButton *btn_Curve3;
    QPushButton *btn_Curve4;
    QPushButton *btn_Curve5;
    QPushButton *btn_SoundPlay;
    QLineEdit *le_SoundFilePath;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *gb_ChartType;
    QRadioButton *rb_ChartTypeDistance;
    QRadioButton *rb_ChartTypeHistogram;
    QGroupBox *gb_Track;
    QPushButton *btn_TrackSelect;
    QLineEdit *le_TrackName;

    void setupUi(QDialog *WindowSignalEditor)
    {
        if (WindowSignalEditor->objectName().isEmpty())
            WindowSignalEditor->setObjectName(QString::fromUtf8("WindowSignalEditor"));
        WindowSignalEditor->resize(934, 609);
        gb_Signal = new QGroupBox(WindowSignalEditor);
        gb_Signal->setObjectName(QString::fromUtf8("gb_Signal"));
        gb_Signal->setGeometry(QRect(20, 30, 191, 91));
        lbl_Signal_Name = new QLabel(gb_Signal);
        lbl_Signal_Name->setObjectName(QString::fromUtf8("lbl_Signal_Name"));
        lbl_Signal_Name->setGeometry(QRect(10, 20, 47, 14));
        le_Signal_Name = new QLineEdit(gb_Signal);
        le_Signal_Name->setObjectName(QString::fromUtf8("le_Signal_Name"));
        le_Signal_Name->setGeometry(QRect(50, 20, 131, 21));
        btn_Signal_Save = new QPushButton(gb_Signal);
        btn_Signal_Save->setObjectName(QString::fromUtf8("btn_Signal_Save"));
        btn_Signal_Save->setGeometry(QRect(10, 60, 80, 22));
        btn_Signal_Save->setFocusPolicy(Qt::NoFocus);
        btn_Signal_Save->setAutoDefault(false);
        btn_Signal_Load = new QPushButton(gb_Signal);
        btn_Signal_Load->setObjectName(QString::fromUtf8("btn_Signal_Load"));
        btn_Signal_Load->setGeometry(QRect(100, 60, 80, 22));
        btn_Signal_Load->setFocusPolicy(Qt::ClickFocus);
        btn_Signal_Load->setAutoDefault(false);
        gb_Formula = new QGroupBox(WindowSignalEditor);
        gb_Formula->setObjectName(QString::fromUtf8("gb_Formula"));
        gb_Formula->setGeometry(QRect(20, 190, 191, 81));
        lbl_Formula = new QLabel(gb_Formula);
        lbl_Formula->setObjectName(QString::fromUtf8("lbl_Formula"));
        lbl_Formula->setGeometry(QRect(20, 20, 181, 16));
        btn_Formula_Select = new QPushButton(gb_Formula);
        btn_Formula_Select->setObjectName(QString::fromUtf8("btn_Formula_Select"));
        btn_Formula_Select->setGeometry(QRect(50, 50, 111, 22));
        btn_Formula_Select->setAutoDefault(false);
        gb_SignalDistance = new QGroupBox(WindowSignalEditor);
        gb_SignalDistance->setObjectName(QString::fromUtf8("gb_SignalDistance"));
        gb_SignalDistance->setGeometry(QRect(20, 280, 191, 111));
        rb_SignalDistance_FullTrack = new QRadioButton(gb_SignalDistance);
        rb_SignalDistance_FullTrack->setObjectName(QString::fromUtf8("rb_SignalDistance_FullTrack"));
        rb_SignalDistance_FullTrack->setGeometry(QRect(10, 20, 121, 20));
        rb_SignalDistance_TrackSector = new QRadioButton(gb_SignalDistance);
        rb_SignalDistance_TrackSector->setObjectName(QString::fromUtf8("rb_SignalDistance_TrackSector"));
        rb_SignalDistance_TrackSector->setGeometry(QRect(10, 40, 111, 20));
        rb_SignalDistance_TrackSector->setChecked(true);
        lbl_TrackSectorName = new QLabel(gb_SignalDistance);
        lbl_TrackSectorName->setObjectName(QString::fromUtf8("lbl_TrackSectorName"));
        lbl_TrackSectorName->setGeometry(QRect(50, 60, 131, 16));
        btn_SelectTrackSector = new QPushButton(gb_SignalDistance);
        btn_SelectTrackSector->setObjectName(QString::fromUtf8("btn_SelectTrackSector"));
        btn_SelectTrackSector->setGeometry(QRect(40, 80, 141, 22));
        btn_SelectTrackSector->setFocusPolicy(Qt::NoFocus);
        btn_SelectTrackSector->setAutoDefault(false);
        gb_Range1 = new QGroupBox(WindowSignalEditor);
        gb_Range1->setObjectName(QString::fromUtf8("gb_Range1"));
        gb_Range1->setGeometry(QRect(220, 29, 121, 91));
        lbl_Range1min = new QLabel(gb_Range1);
        lbl_Range1min->setObjectName(QString::fromUtf8("lbl_Range1min"));
        lbl_Range1min->setGeometry(QRect(10, 54, 47, 14));
        lbl_Range1max = new QLabel(gb_Range1);
        lbl_Range1max->setObjectName(QString::fromUtf8("lbl_Range1max"));
        lbl_Range1max->setGeometry(QRect(10, 34, 47, 14));
        le_Range1max = new QLineEdit(gb_Range1);
        le_Range1max->setObjectName(QString::fromUtf8("le_Range1max"));
        le_Range1max->setGeometry(QRect(40, 30, 71, 21));
        le_Range1min = new QLineEdit(gb_Range1);
        le_Range1min->setObjectName(QString::fromUtf8("le_Range1min"));
        le_Range1min->setGeometry(QRect(40, 50, 71, 21));
        btn_Range1auto = new QPushButton(gb_Range1);
        btn_Range1auto->setObjectName(QString::fromUtf8("btn_Range1auto"));
        btn_Range1auto->setGeometry(QRect(90, 70, 21, 20));
        btn_Range1auto->setFocusPolicy(Qt::NoFocus);
        gb_Range2 = new QGroupBox(WindowSignalEditor);
        gb_Range2->setObjectName(QString::fromUtf8("gb_Range2"));
        gb_Range2->setGeometry(QRect(220, 190, 121, 101));
        lbl_Range2min = new QLabel(gb_Range2);
        lbl_Range2min->setObjectName(QString::fromUtf8("lbl_Range2min"));
        lbl_Range2min->setGeometry(QRect(10, 64, 47, 14));
        lbl_Range2max = new QLabel(gb_Range2);
        lbl_Range2max->setObjectName(QString::fromUtf8("lbl_Range2max"));
        lbl_Range2max->setGeometry(QRect(10, 44, 47, 14));
        le_Range2max = new QLineEdit(gb_Range2);
        le_Range2max->setObjectName(QString::fromUtf8("le_Range2max"));
        le_Range2max->setEnabled(false);
        le_Range2max->setGeometry(QRect(40, 40, 71, 21));
        le_Range2min = new QLineEdit(gb_Range2);
        le_Range2min->setObjectName(QString::fromUtf8("le_Range2min"));
        le_Range2min->setEnabled(false);
        le_Range2min->setGeometry(QRect(40, 60, 71, 21));
        cb_Range2enabled = new QCheckBox(gb_Range2);
        cb_Range2enabled->setObjectName(QString::fromUtf8("cb_Range2enabled"));
        cb_Range2enabled->setGeometry(QRect(10, 20, 72, 20));
        btn_Range2auto = new QPushButton(gb_Range2);
        btn_Range2auto->setObjectName(QString::fromUtf8("btn_Range2auto"));
        btn_Range2auto->setGeometry(QRect(90, 80, 21, 20));
        btn_Range2auto->setFocusPolicy(Qt::NoFocus);
        gb_Telemetry = new QGroupBox(WindowSignalEditor);
        gb_Telemetry->setObjectName(QString::fromUtf8("gb_Telemetry"));
        gb_Telemetry->setGeometry(QRect(20, 400, 321, 51));
        lbl_Telemetry = new QLabel(gb_Telemetry);
        lbl_Telemetry->setObjectName(QString::fromUtf8("lbl_Telemetry"));
        lbl_Telemetry->setGeometry(QRect(10, 20, 261, 16));
        btn_LoadTelemetry = new QPushButton(gb_Telemetry);
        btn_LoadTelemetry->setObjectName(QString::fromUtf8("btn_LoadTelemetry"));
        btn_LoadTelemetry->setGeometry(QRect(269, 20, 41, 22));
        btn_LoadTelemetry->setFocusPolicy(Qt::NoFocus);
        btn_LoadTelemetry->setAutoDefault(false);
        gb_Sound = new QGroupBox(WindowSignalEditor);
        gb_Sound->setObjectName(QString::fromUtf8("gb_Sound"));
        gb_Sound->setGeometry(QRect(20, 470, 321, 111));
        btn_SoundSelect = new QPushButton(gb_Sound);
        btn_SoundSelect->setObjectName(QString::fromUtf8("btn_SoundSelect"));
        btn_SoundSelect->setGeometry(QRect(260, 21, 41, 22));
        btn_SoundSelect->setFocusPolicy(Qt::NoFocus);
        btn_SoundSelect->setAutoDefault(false);
        lbl_VolumeCurve = new QLabel(gb_Sound);
        lbl_VolumeCurve->setObjectName(QString::fromUtf8("lbl_VolumeCurve"));
        lbl_VolumeCurve->setGeometry(QRect(10, 50, 81, 16));
        btn_Curve1 = new QPushButton(gb_Sound);
        btn_Curve1->setObjectName(QString::fromUtf8("btn_Curve1"));
        btn_Curve1->setGeometry(QRect(90, 50, 24, 24));
        btn_Curve1->setAutoDefault(false);
        lbl_Volume = new QLabel(gb_Sound);
        lbl_Volume->setObjectName(QString::fromUtf8("lbl_Volume"));
        lbl_Volume->setGeometry(QRect(10, 80, 47, 14));
        hs_Volume = new QSlider(gb_Sound);
        hs_Volume->setObjectName(QString::fromUtf8("hs_Volume"));
        hs_Volume->setGeometry(QRect(90, 80, 160, 16));
        hs_Volume->setMaximum(100);
        hs_Volume->setValue(100);
        hs_Volume->setOrientation(Qt::Horizontal);
        btn_Curve2 = new QPushButton(gb_Sound);
        btn_Curve2->setObjectName(QString::fromUtf8("btn_Curve2"));
        btn_Curve2->setGeometry(QRect(120, 50, 21, 22));
        btn_Curve2->setAutoDefault(false);
        btn_Curve3 = new QPushButton(gb_Sound);
        btn_Curve3->setObjectName(QString::fromUtf8("btn_Curve3"));
        btn_Curve3->setGeometry(QRect(150, 50, 21, 22));
        btn_Curve3->setAutoDefault(false);
        btn_Curve4 = new QPushButton(gb_Sound);
        btn_Curve4->setObjectName(QString::fromUtf8("btn_Curve4"));
        btn_Curve4->setGeometry(QRect(180, 50, 21, 22));
        btn_Curve4->setAutoDefault(false);
        btn_Curve5 = new QPushButton(gb_Sound);
        btn_Curve5->setObjectName(QString::fromUtf8("btn_Curve5"));
        btn_Curve5->setGeometry(QRect(210, 50, 21, 22));
        btn_Curve5->setAutoDefault(false);
        btn_SoundPlay = new QPushButton(gb_Sound);
        btn_SoundPlay->setObjectName(QString::fromUtf8("btn_SoundPlay"));
        btn_SoundPlay->setGeometry(QRect(270, 60, 31, 31));
        btn_SoundPlay->setFocusPolicy(Qt::NoFocus);
        btn_SoundPlay->setAutoDefault(false);
        le_SoundFilePath = new QLineEdit(gb_Sound);
        le_SoundFilePath->setObjectName(QString::fromUtf8("le_SoundFilePath"));
        le_SoundFilePath->setGeometry(QRect(10, 20, 241, 24));
        le_SoundFilePath->setReadOnly(true);
        verticalLayoutWidget = new QWidget(WindowSignalEditor);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(360, 20, 551, 561));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gb_ChartType = new QGroupBox(WindowSignalEditor);
        gb_ChartType->setObjectName(QString::fromUtf8("gb_ChartType"));
        gb_ChartType->setGeometry(QRect(220, 300, 121, 91));
        rb_ChartTypeDistance = new QRadioButton(gb_ChartType);
        rb_ChartTypeDistance->setObjectName(QString::fromUtf8("rb_ChartTypeDistance"));
        rb_ChartTypeDistance->setGeometry(QRect(10, 30, 85, 20));
        rb_ChartTypeHistogram = new QRadioButton(gb_ChartType);
        rb_ChartTypeHistogram->setObjectName(QString::fromUtf8("rb_ChartTypeHistogram"));
        rb_ChartTypeHistogram->setGeometry(QRect(10, 60, 85, 20));
        gb_Track = new QGroupBox(WindowSignalEditor);
        gb_Track->setObjectName(QString::fromUtf8("gb_Track"));
        gb_Track->setGeometry(QRect(20, 130, 321, 51));
        btn_TrackSelect = new QPushButton(gb_Track);
        btn_TrackSelect->setObjectName(QString::fromUtf8("btn_TrackSelect"));
        btn_TrackSelect->setGeometry(QRect(269, 20, 41, 22));
        btn_TrackSelect->setAutoDefault(false);
        le_TrackName = new QLineEdit(gb_Track);
        le_TrackName->setObjectName(QString::fromUtf8("le_TrackName"));
        le_TrackName->setGeometry(QRect(10, 20, 251, 21));
        le_TrackName->setReadOnly(true);

        retranslateUi(WindowSignalEditor);

        QMetaObject::connectSlotsByName(WindowSignalEditor);
    } // setupUi

    void retranslateUi(QDialog *WindowSignalEditor)
    {
        WindowSignalEditor->setWindowTitle(QCoreApplication::translate("WindowSignalEditor", "Signal Editor", nullptr));
        gb_Signal->setTitle(QCoreApplication::translate("WindowSignalEditor", "Signal", nullptr));
        lbl_Signal_Name->setText(QCoreApplication::translate("WindowSignalEditor", "Name:", nullptr));
        le_Signal_Name->setText(QString());
        btn_Signal_Save->setText(QCoreApplication::translate("WindowSignalEditor", "Save", nullptr));
        btn_Signal_Load->setText(QCoreApplication::translate("WindowSignalEditor", "Load", nullptr));
        gb_Formula->setTitle(QCoreApplication::translate("WindowSignalEditor", "Currently selected formula:", nullptr));
        lbl_Formula->setText(QCoreApplication::translate("WindowSignalEditor", "None", nullptr));
        btn_Formula_Select->setText(QCoreApplication::translate("WindowSignalEditor", "Select Formula", nullptr));
        gb_SignalDistance->setTitle(QCoreApplication::translate("WindowSignalEditor", "Signal distance range:", nullptr));
        rb_SignalDistance_FullTrack->setText(QCoreApplication::translate("WindowSignalEditor", "Full track distance", nullptr));
        rb_SignalDistance_TrackSector->setText(QCoreApplication::translate("WindowSignalEditor", "Track Sector", nullptr));
        lbl_TrackSectorName->setText(QCoreApplication::translate("WindowSignalEditor", "No Track Sector selected", nullptr));
        btn_SelectTrackSector->setText(QCoreApplication::translate("WindowSignalEditor", "Select Track Sector", nullptr));
        gb_Range1->setTitle(QCoreApplication::translate("WindowSignalEditor", "Range 1", nullptr));
        lbl_Range1min->setText(QCoreApplication::translate("WindowSignalEditor", "Min:", nullptr));
        lbl_Range1max->setText(QCoreApplication::translate("WindowSignalEditor", "Max:", nullptr));
        le_Range1max->setText(QString());
        le_Range1min->setText(QString());
        btn_Range1auto->setText(QCoreApplication::translate("WindowSignalEditor", "A", nullptr));
        gb_Range2->setTitle(QCoreApplication::translate("WindowSignalEditor", "Range 2 (negative)", nullptr));
        lbl_Range2min->setText(QCoreApplication::translate("WindowSignalEditor", "Min:", nullptr));
        lbl_Range2max->setText(QCoreApplication::translate("WindowSignalEditor", "Max:", nullptr));
        le_Range2max->setText(QString());
        le_Range2min->setText(QString());
        cb_Range2enabled->setText(QCoreApplication::translate("WindowSignalEditor", "Enabled", nullptr));
        btn_Range2auto->setText(QCoreApplication::translate("WindowSignalEditor", "A", nullptr));
        gb_Telemetry->setTitle(QCoreApplication::translate("WindowSignalEditor", "Display telemetry:", nullptr));
        lbl_Telemetry->setText(QCoreApplication::translate("WindowSignalEditor", "None", nullptr));
        btn_LoadTelemetry->setText(QCoreApplication::translate("WindowSignalEditor", "Load", nullptr));
        gb_Sound->setTitle(QCoreApplication::translate("WindowSignalEditor", "Sound:", nullptr));
        btn_SoundSelect->setText(QCoreApplication::translate("WindowSignalEditor", "Select", nullptr));
        lbl_VolumeCurve->setText(QCoreApplication::translate("WindowSignalEditor", "Volume curve:", nullptr));
        btn_Curve1->setText(QString());
        lbl_Volume->setText(QCoreApplication::translate("WindowSignalEditor", "Volume:", nullptr));
        btn_Curve2->setText(QString());
        btn_Curve3->setText(QString());
        btn_Curve4->setText(QString());
        btn_Curve5->setText(QString());
        btn_SoundPlay->setText(QString());
        gb_ChartType->setTitle(QCoreApplication::translate("WindowSignalEditor", "Chart type:", nullptr));
        rb_ChartTypeDistance->setText(QCoreApplication::translate("WindowSignalEditor", "Distance", nullptr));
        rb_ChartTypeHistogram->setText(QCoreApplication::translate("WindowSignalEditor", "Histogram", nullptr));
        gb_Track->setTitle(QCoreApplication::translate("WindowSignalEditor", "Selected track:", nullptr));
        btn_TrackSelect->setText(QCoreApplication::translate("WindowSignalEditor", "Select", nullptr));
        le_TrackName->setText(QCoreApplication::translate("WindowSignalEditor", "None", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowSignalEditor: public Ui_WindowSignalEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWSIGNALEDITOR_H

/********************************************************************************
** Form generated from reading UI file 'WindowLive.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWLIVE_H
#define UI_WINDOWLIVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowLive
{
public:
    QPushButton *btn_Activate;
    QPushButton *btn_Stop;
    QGroupBox *gb_SignalSet;
    QLabel *label_Name;
    QPushButton *btn_Select;
    QLabel *label_Track;
    QLineEdit *le_Track;
    QLineEdit *le_SignalSetName;
    QCheckBox *cb_RecordTelemetry;
    QLabel *label_Status;
    QLabel *lbl_Status;
    QGroupBox *gb_BMSet;
    QComboBox *cb_BrakeMarkerSets;
    QLineEdit *le_Track_bm;
    QLabel *label_Track_bm;

    void setupUi(QDialog *WindowLive)
    {
        if (WindowLive->objectName().isEmpty())
            WindowLive->setObjectName(QString::fromUtf8("WindowLive"));
        WindowLive->resize(360, 462);
        btn_Activate = new QPushButton(WindowLive);
        btn_Activate->setObjectName(QString::fromUtf8("btn_Activate"));
        btn_Activate->setGeometry(QRect(20, 280, 121, 71));
        btn_Stop = new QPushButton(WindowLive);
        btn_Stop->setObjectName(QString::fromUtf8("btn_Stop"));
        btn_Stop->setGeometry(QRect(220, 280, 121, 71));
        gb_SignalSet = new QGroupBox(WindowLive);
        gb_SignalSet->setObjectName(QString::fromUtf8("gb_SignalSet"));
        gb_SignalSet->setGeometry(QRect(20, 20, 321, 121));
        label_Name = new QLabel(gb_SignalSet);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        label_Name->setGeometry(QRect(10, 64, 47, 14));
        btn_Select = new QPushButton(gb_SignalSet);
        btn_Select->setObjectName(QString::fromUtf8("btn_Select"));
        btn_Select->setGeometry(QRect(10, 30, 301, 22));
        label_Track = new QLabel(gb_SignalSet);
        label_Track->setObjectName(QString::fromUtf8("label_Track"));
        label_Track->setGeometry(QRect(13, 94, 47, 14));
        le_Track = new QLineEdit(gb_SignalSet);
        le_Track->setObjectName(QString::fromUtf8("le_Track"));
        le_Track->setGeometry(QRect(50, 90, 261, 21));
        le_Track->setReadOnly(true);
        le_SignalSetName = new QLineEdit(gb_SignalSet);
        le_SignalSetName->setObjectName(QString::fromUtf8("le_SignalSetName"));
        le_SignalSetName->setGeometry(QRect(50, 60, 261, 21));
        le_SignalSetName->setReadOnly(true);
        cb_RecordTelemetry = new QCheckBox(WindowLive);
        cb_RecordTelemetry->setObjectName(QString::fromUtf8("cb_RecordTelemetry"));
        cb_RecordTelemetry->setGeometry(QRect(30, 360, 141, 20));
        label_Status = new QLabel(WindowLive);
        label_Status->setObjectName(QString::fromUtf8("label_Status"));
        label_Status->setGeometry(QRect(30, 430, 47, 14));
        QFont font;
        font.setPointSize(12);
        label_Status->setFont(font);
        lbl_Status = new QLabel(WindowLive);
        lbl_Status->setObjectName(QString::fromUtf8("lbl_Status"));
        lbl_Status->setGeometry(QRect(90, 430, 231, 20));
        lbl_Status->setFont(font);
        gb_BMSet = new QGroupBox(WindowLive);
        gb_BMSet->setObjectName(QString::fromUtf8("gb_BMSet"));
        gb_BMSet->setGeometry(QRect(20, 150, 321, 101));
        cb_BrakeMarkerSets = new QComboBox(gb_BMSet);
        cb_BrakeMarkerSets->setObjectName(QString::fromUtf8("cb_BrakeMarkerSets"));
        cb_BrakeMarkerSets->setGeometry(QRect(10, 30, 301, 24));
        le_Track_bm = new QLineEdit(gb_BMSet);
        le_Track_bm->setObjectName(QString::fromUtf8("le_Track_bm"));
        le_Track_bm->setGeometry(QRect(50, 60, 261, 21));
        le_Track_bm->setReadOnly(true);
        label_Track_bm = new QLabel(gb_BMSet);
        label_Track_bm->setObjectName(QString::fromUtf8("label_Track_bm"));
        label_Track_bm->setGeometry(QRect(10, 64, 47, 14));

        retranslateUi(WindowLive);

        QMetaObject::connectSlotsByName(WindowLive);
    } // setupUi

    void retranslateUi(QDialog *WindowLive)
    {
        WindowLive->setWindowTitle(QCoreApplication::translate("WindowLive", "IRSF - Main", nullptr));
        btn_Activate->setText(QCoreApplication::translate("WindowLive", "Activate", nullptr));
        btn_Stop->setText(QCoreApplication::translate("WindowLive", "Stop", nullptr));
        gb_SignalSet->setTitle(QCoreApplication::translate("WindowLive", "Signal set:", nullptr));
        label_Name->setText(QCoreApplication::translate("WindowLive", "Name:", nullptr));
        btn_Select->setText(QCoreApplication::translate("WindowLive", "Select", nullptr));
        label_Track->setText(QCoreApplication::translate("WindowLive", "Track:", nullptr));
        cb_RecordTelemetry->setText(QCoreApplication::translate("WindowLive", "Record Telemetry", nullptr));
        label_Status->setText(QCoreApplication::translate("WindowLive", "Status:", nullptr));
        lbl_Status->setText(QCoreApplication::translate("WindowLive", "...", nullptr));
        gb_BMSet->setTitle(QCoreApplication::translate("WindowLive", "Brake marker set:", nullptr));
        label_Track_bm->setText(QCoreApplication::translate("WindowLive", "Track:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowLive: public Ui_WindowLive {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWLIVE_H

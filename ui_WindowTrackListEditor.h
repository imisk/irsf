/********************************************************************************
** Form generated from reading UI file 'WindowTrackListEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWTRACKLISTEDITOR_H
#define UI_WINDOWTRACKLISTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowTrackListEditor
{
public:
    QListWidget *lb_Tracks;
    QLabel *lbl_Track;
    QListWidget *lb_TrackConfigs;
    QLabel *lbl_TrackConfigs;
    QLabel *lbl_SelectedTrackId;
    QLabel *lbl_SelectedTrackIdInput;
    QLabel *lbl_SelectedConfigId;
    QLabel *lbl_SelectedConfigIdInput;
    QGroupBox *gr_AddNewTrack;
    QLabel *lbl_AddNewTrack_TrackName;
    QLineEdit *le_AddNewTrack_NameInput;
    QPushButton *btn_AddNewTrack_Add;
    QPushButton *btn_DeleteTrack;
    QPushButton *btn_DeleteTrackConfig;
    QGroupBox *gr_AddNewTrackConfig;
    QLabel *lbl_AddNewTrackConfig_ConfigName;
    QLineEdit *le_AddNewTrackConfig_NameInput;
    QPushButton *btn_AddNewTrackConfig_Add;
    QLabel *lbl_AddNewTrackConfig_Length;
    QLineEdit *le_AddNewTrackConfig_LengthInput;
    QPushButton *btn_Select;

    void setupUi(QDialog *WindowTrackListEditor)
    {
        if (WindowTrackListEditor->objectName().isEmpty())
            WindowTrackListEditor->setObjectName(QString::fromUtf8("WindowTrackListEditor"));
        WindowTrackListEditor->resize(986, 497);
        lb_Tracks = new QListWidget(WindowTrackListEditor);
        lb_Tracks->setObjectName(QString::fromUtf8("lb_Tracks"));
        lb_Tracks->setGeometry(QRect(20, 40, 461, 171));
        lbl_Track = new QLabel(WindowTrackListEditor);
        lbl_Track->setObjectName(QString::fromUtf8("lbl_Track"));
        lbl_Track->setGeometry(QRect(20, 20, 47, 14));
        lb_TrackConfigs = new QListWidget(WindowTrackListEditor);
        lb_TrackConfigs->setObjectName(QString::fromUtf8("lb_TrackConfigs"));
        lb_TrackConfigs->setGeometry(QRect(20, 250, 461, 161));
        lbl_TrackConfigs = new QLabel(WindowTrackListEditor);
        lbl_TrackConfigs->setObjectName(QString::fromUtf8("lbl_TrackConfigs"));
        lbl_TrackConfigs->setGeometry(QRect(20, 230, 171, 16));
        lbl_SelectedTrackId = new QLabel(WindowTrackListEditor);
        lbl_SelectedTrackId->setObjectName(QString::fromUtf8("lbl_SelectedTrackId"));
        lbl_SelectedTrackId->setGeometry(QRect(20, 420, 131, 21));
        QFont font;
        font.setPointSize(12);
        lbl_SelectedTrackId->setFont(font);
        lbl_SelectedTrackId->setTextFormat(Qt::AutoText);
        lbl_SelectedTrackIdInput = new QLabel(WindowTrackListEditor);
        lbl_SelectedTrackIdInput->setObjectName(QString::fromUtf8("lbl_SelectedTrackIdInput"));
        lbl_SelectedTrackIdInput->setGeometry(QRect(160, 420, 41, 21));
        lbl_SelectedTrackIdInput->setFont(font);
        lbl_SelectedTrackIdInput->setTextFormat(Qt::AutoText);
        lbl_SelectedConfigId = new QLabel(WindowTrackListEditor);
        lbl_SelectedConfigId->setObjectName(QString::fromUtf8("lbl_SelectedConfigId"));
        lbl_SelectedConfigId->setGeometry(QRect(210, 420, 191, 21));
        lbl_SelectedConfigId->setFont(font);
        lbl_SelectedConfigId->setTextFormat(Qt::AutoText);
        lbl_SelectedConfigIdInput = new QLabel(WindowTrackListEditor);
        lbl_SelectedConfigIdInput->setObjectName(QString::fromUtf8("lbl_SelectedConfigIdInput"));
        lbl_SelectedConfigIdInput->setGeometry(QRect(400, 420, 41, 21));
        lbl_SelectedConfigIdInput->setFont(font);
        lbl_SelectedConfigIdInput->setTextFormat(Qt::AutoText);
        gr_AddNewTrack = new QGroupBox(WindowTrackListEditor);
        gr_AddNewTrack->setObjectName(QString::fromUtf8("gr_AddNewTrack"));
        gr_AddNewTrack->setGeometry(QRect(510, 70, 461, 71));
        lbl_AddNewTrack_TrackName = new QLabel(gr_AddNewTrack);
        lbl_AddNewTrack_TrackName->setObjectName(QString::fromUtf8("lbl_AddNewTrack_TrackName"));
        lbl_AddNewTrack_TrackName->setGeometry(QRect(10, 30, 71, 16));
        le_AddNewTrack_NameInput = new QLineEdit(gr_AddNewTrack);
        le_AddNewTrack_NameInput->setObjectName(QString::fromUtf8("le_AddNewTrack_NameInput"));
        le_AddNewTrack_NameInput->setGeometry(QRect(80, 30, 281, 21));
        btn_AddNewTrack_Add = new QPushButton(gr_AddNewTrack);
        btn_AddNewTrack_Add->setObjectName(QString::fromUtf8("btn_AddNewTrack_Add"));
        btn_AddNewTrack_Add->setGeometry(QRect(370, 30, 80, 22));
        btn_DeleteTrack = new QPushButton(WindowTrackListEditor);
        btn_DeleteTrack->setObjectName(QString::fromUtf8("btn_DeleteTrack"));
        btn_DeleteTrack->setGeometry(QRect(510, 40, 171, 22));
        btn_DeleteTrackConfig = new QPushButton(WindowTrackListEditor);
        btn_DeleteTrackConfig->setObjectName(QString::fromUtf8("btn_DeleteTrackConfig"));
        btn_DeleteTrackConfig->setGeometry(QRect(700, 40, 171, 22));
        gr_AddNewTrackConfig = new QGroupBox(WindowTrackListEditor);
        gr_AddNewTrackConfig->setObjectName(QString::fromUtf8("gr_AddNewTrackConfig"));
        gr_AddNewTrackConfig->setGeometry(QRect(510, 150, 461, 91));
        lbl_AddNewTrackConfig_ConfigName = new QLabel(gr_AddNewTrackConfig);
        lbl_AddNewTrackConfig_ConfigName->setObjectName(QString::fromUtf8("lbl_AddNewTrackConfig_ConfigName"));
        lbl_AddNewTrackConfig_ConfigName->setGeometry(QRect(10, 30, 111, 16));
        le_AddNewTrackConfig_NameInput = new QLineEdit(gr_AddNewTrackConfig);
        le_AddNewTrackConfig_NameInput->setObjectName(QString::fromUtf8("le_AddNewTrackConfig_NameInput"));
        le_AddNewTrackConfig_NameInput->setGeometry(QRect(120, 30, 241, 21));
        btn_AddNewTrackConfig_Add = new QPushButton(gr_AddNewTrackConfig);
        btn_AddNewTrackConfig_Add->setObjectName(QString::fromUtf8("btn_AddNewTrackConfig_Add"));
        btn_AddNewTrackConfig_Add->setGeometry(QRect(370, 30, 80, 22));
        lbl_AddNewTrackConfig_Length = new QLabel(gr_AddNewTrackConfig);
        lbl_AddNewTrackConfig_Length->setObjectName(QString::fromUtf8("lbl_AddNewTrackConfig_Length"));
        lbl_AddNewTrackConfig_Length->setGeometry(QRect(10, 60, 71, 16));
        le_AddNewTrackConfig_LengthInput = new QLineEdit(gr_AddNewTrackConfig);
        le_AddNewTrackConfig_LengthInput->setObjectName(QString::fromUtf8("le_AddNewTrackConfig_LengthInput"));
        le_AddNewTrackConfig_LengthInput->setGeometry(QRect(120, 60, 113, 21));
        btn_Select = new QPushButton(WindowTrackListEditor);
        btn_Select->setObjectName(QString::fromUtf8("btn_Select"));
        btn_Select->setGeometry(QRect(20, 450, 461, 31));

        retranslateUi(WindowTrackListEditor);

        QMetaObject::connectSlotsByName(WindowTrackListEditor);
    } // setupUi

    void retranslateUi(QDialog *WindowTrackListEditor)
    {
        WindowTrackListEditor->setWindowTitle(QCoreApplication::translate("WindowTrackListEditor", "Track database", nullptr));
        lbl_Track->setText(QCoreApplication::translate("WindowTrackListEditor", "Track:", nullptr));
        lbl_TrackConfigs->setText(QCoreApplication::translate("WindowTrackListEditor", "Available configurations for track:", nullptr));
        lbl_SelectedTrackId->setText(QCoreApplication::translate("WindowTrackListEditor", "Selected track ID:", nullptr));
        lbl_SelectedTrackIdInput->setText(QCoreApplication::translate("WindowTrackListEditor", "-", nullptr));
        lbl_SelectedConfigId->setText(QCoreApplication::translate("WindowTrackListEditor", "Selected configuration ID:", nullptr));
        lbl_SelectedConfigIdInput->setText(QCoreApplication::translate("WindowTrackListEditor", "-", nullptr));
        gr_AddNewTrack->setTitle(QCoreApplication::translate("WindowTrackListEditor", "Add new track:", nullptr));
        lbl_AddNewTrack_TrackName->setText(QCoreApplication::translate("WindowTrackListEditor", "Track name:", nullptr));
        btn_AddNewTrack_Add->setText(QCoreApplication::translate("WindowTrackListEditor", "Add", nullptr));
        btn_DeleteTrack->setText(QCoreApplication::translate("WindowTrackListEditor", "Delete selected track", nullptr));
        btn_DeleteTrackConfig->setText(QCoreApplication::translate("WindowTrackListEditor", "Delete selected track config", nullptr));
        gr_AddNewTrackConfig->setTitle(QCoreApplication::translate("WindowTrackListEditor", "Add new track configuration:", nullptr));
        lbl_AddNewTrackConfig_ConfigName->setText(QCoreApplication::translate("WindowTrackListEditor", "Configuration name:", nullptr));
        btn_AddNewTrackConfig_Add->setText(QCoreApplication::translate("WindowTrackListEditor", "Add", nullptr));
        lbl_AddNewTrackConfig_Length->setText(QCoreApplication::translate("WindowTrackListEditor", "Length (m):", nullptr));
        btn_Select->setText(QCoreApplication::translate("WindowTrackListEditor", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowTrackListEditor: public Ui_WindowTrackListEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWTRACKLISTEDITOR_H

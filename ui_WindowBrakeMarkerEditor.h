/********************************************************************************
** Form generated from reading UI file 'WindowBrakeMarkerEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWBRAKEMARKEREDITOR_H
#define UI_WINDOWBRAKEMARKEREDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowBrakeMarkerEditor
{
public:
    QComboBox *cb_SetList;
    QLabel *lbl_SelBrMaSe;
    QGroupBox *gb_CurrentSet;
    QLabel *lbl_Name;
    QLineEdit *le_CurrentSetName;
    QPushButton *btn_Save;
    QPushButton *btn_Rename;
    QPushButton *btn_Delete;
    QListWidget *lb_Markers;
    QGroupBox *gb_Marker;
    QLabel *lbl_Distance;
    QLabel *lbl_Speed;
    QLineEdit *le_Distance;
    QLineEdit *le_Speed;
    QPushButton *btn_AddNewMarker;
    QPushButton *btn_DelMarker;
    QLabel *lbl_ExistingMarkers;
    QLabel *lbl_Track;
    QLineEdit *le_Track;
    QPushButton *btn_SelectTrack;

    void setupUi(QDialog *WindowBrakeMarkerEditor)
    {
        if (WindowBrakeMarkerEditor->objectName().isEmpty())
            WindowBrakeMarkerEditor->setObjectName(QString::fromUtf8("WindowBrakeMarkerEditor"));
        WindowBrakeMarkerEditor->resize(534, 485);
        cb_SetList = new QComboBox(WindowBrakeMarkerEditor);
        cb_SetList->setObjectName(QString::fromUtf8("cb_SetList"));
        cb_SetList->setGeometry(QRect(20, 40, 501, 24));
        lbl_SelBrMaSe = new QLabel(WindowBrakeMarkerEditor);
        lbl_SelBrMaSe->setObjectName(QString::fromUtf8("lbl_SelBrMaSe"));
        lbl_SelBrMaSe->setGeometry(QRect(20, 20, 181, 16));
        gb_CurrentSet = new QGroupBox(WindowBrakeMarkerEditor);
        gb_CurrentSet->setObjectName(QString::fromUtf8("gb_CurrentSet"));
        gb_CurrentSet->setGeometry(QRect(20, 70, 501, 391));
        lbl_Name = new QLabel(gb_CurrentSet);
        lbl_Name->setObjectName(QString::fromUtf8("lbl_Name"));
        lbl_Name->setGeometry(QRect(10, 30, 49, 16));
        le_CurrentSetName = new QLineEdit(gb_CurrentSet);
        le_CurrentSetName->setObjectName(QString::fromUtf8("le_CurrentSetName"));
        le_CurrentSetName->setGeometry(QRect(70, 30, 401, 24));
        btn_Save = new QPushButton(gb_CurrentSet);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        btn_Save->setGeometry(QRect(20, 70, 141, 24));
        btn_Rename = new QPushButton(gb_CurrentSet);
        btn_Rename->setObjectName(QString::fromUtf8("btn_Rename"));
        btn_Rename->setGeometry(QRect(180, 70, 141, 24));
        btn_Delete = new QPushButton(gb_CurrentSet);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(340, 70, 141, 24));
        lb_Markers = new QListWidget(gb_CurrentSet);
        lb_Markers->setObjectName(QString::fromUtf8("lb_Markers"));
        lb_Markers->setGeometry(QRect(20, 180, 311, 192));
        gb_Marker = new QGroupBox(gb_CurrentSet);
        gb_Marker->setObjectName(QString::fromUtf8("gb_Marker"));
        gb_Marker->setGeometry(QRect(340, 160, 141, 211));
        lbl_Distance = new QLabel(gb_Marker);
        lbl_Distance->setObjectName(QString::fromUtf8("lbl_Distance"));
        lbl_Distance->setGeometry(QRect(10, 30, 61, 16));
        lbl_Speed = new QLabel(gb_Marker);
        lbl_Speed->setObjectName(QString::fromUtf8("lbl_Speed"));
        lbl_Speed->setGeometry(QRect(10, 80, 101, 16));
        le_Distance = new QLineEdit(gb_Marker);
        le_Distance->setObjectName(QString::fromUtf8("le_Distance"));
        le_Distance->setGeometry(QRect(10, 50, 113, 24));
        le_Speed = new QLineEdit(gb_Marker);
        le_Speed->setObjectName(QString::fromUtf8("le_Speed"));
        le_Speed->setGeometry(QRect(10, 100, 113, 24));
        btn_AddNewMarker = new QPushButton(gb_Marker);
        btn_AddNewMarker->setObjectName(QString::fromUtf8("btn_AddNewMarker"));
        btn_AddNewMarker->setGeometry(QRect(10, 136, 113, 24));
        btn_DelMarker = new QPushButton(gb_Marker);
        btn_DelMarker->setObjectName(QString::fromUtf8("btn_DelMarker"));
        btn_DelMarker->setGeometry(QRect(10, 170, 113, 24));
        lbl_ExistingMarkers = new QLabel(gb_CurrentSet);
        lbl_ExistingMarkers->setObjectName(QString::fromUtf8("lbl_ExistingMarkers"));
        lbl_ExistingMarkers->setGeometry(QRect(20, 160, 111, 16));
        lbl_Track = new QLabel(gb_CurrentSet);
        lbl_Track->setObjectName(QString::fromUtf8("lbl_Track"));
        lbl_Track->setGeometry(QRect(20, 110, 41, 16));
        le_Track = new QLineEdit(gb_CurrentSet);
        le_Track->setObjectName(QString::fromUtf8("le_Track"));
        le_Track->setGeometry(QRect(70, 110, 321, 24));
        le_Track->setReadOnly(true);
        btn_SelectTrack = new QPushButton(gb_CurrentSet);
        btn_SelectTrack->setObjectName(QString::fromUtf8("btn_SelectTrack"));
        btn_SelectTrack->setGeometry(QRect(400, 110, 80, 24));

        retranslateUi(WindowBrakeMarkerEditor);

        QMetaObject::connectSlotsByName(WindowBrakeMarkerEditor);
    } // setupUi

    void retranslateUi(QDialog *WindowBrakeMarkerEditor)
    {
        WindowBrakeMarkerEditor->setWindowTitle(QCoreApplication::translate("WindowBrakeMarkerEditor", "Brake marker editor", nullptr));
        lbl_SelBrMaSe->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Selected brake marker set:", nullptr));
        gb_CurrentSet->setTitle(QCoreApplication::translate("WindowBrakeMarkerEditor", "Current set:", nullptr));
        lbl_Name->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Name:", nullptr));
        btn_Save->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Create new", nullptr));
        btn_Rename->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Rename", nullptr));
        btn_Delete->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Delete", nullptr));
        gb_Marker->setTitle(QCoreApplication::translate("WindowBrakeMarkerEditor", "Marker", nullptr));
        lbl_Distance->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Distance:", nullptr));
        lbl_Speed->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Speed (kph):", nullptr));
        btn_AddNewMarker->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Add new", nullptr));
        btn_DelMarker->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Delete selected", nullptr));
        lbl_ExistingMarkers->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Existing markers:", nullptr));
        lbl_Track->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Track:", nullptr));
        btn_SelectTrack->setText(QCoreApplication::translate("WindowBrakeMarkerEditor", "Select track", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowBrakeMarkerEditor: public Ui_WindowBrakeMarkerEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWBRAKEMARKEREDITOR_H

/********************************************************************************
** Form generated from reading UI file 'WindowTrackSectorEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWTRACKSECTOREDITOR_H
#define UI_WINDOWTRACKSECTOREDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowTrackSectorEditor
{
public:
    QGroupBox *gb_TrackSelection;
    QLineEdit *le_TrackName;
    QPushButton *btn_TrackSelect;
    QListWidget *lb_MainList;
    QPushButton *btn_Remove;
    QPushButton *btn_SelectTs;
    QLabel *lbl_LbHeading;
    QGroupBox *gb_AddNew;
    QLabel *lbl_Name;
    QLabel *lbl_Start;
    QLabel *lbl_End;
    QLineEdit *le_Name;
    QLineEdit *le_Start;
    QLineEdit *le_End;
    QPushButton *btn_Add;

    void setupUi(QDialog *WindowTrackSectorEditor)
    {
        if (WindowTrackSectorEditor->objectName().isEmpty())
            WindowTrackSectorEditor->setObjectName(QString::fromUtf8("WindowTrackSectorEditor"));
        WindowTrackSectorEditor->resize(392, 430);
        gb_TrackSelection = new QGroupBox(WindowTrackSectorEditor);
        gb_TrackSelection->setObjectName(QString::fromUtf8("gb_TrackSelection"));
        gb_TrackSelection->setGeometry(QRect(10, 10, 371, 71));
        le_TrackName = new QLineEdit(gb_TrackSelection);
        le_TrackName->setObjectName(QString::fromUtf8("le_TrackName"));
        le_TrackName->setGeometry(QRect(20, 30, 271, 21));
        le_TrackName->setReadOnly(true);
        btn_TrackSelect = new QPushButton(gb_TrackSelection);
        btn_TrackSelect->setObjectName(QString::fromUtf8("btn_TrackSelect"));
        btn_TrackSelect->setGeometry(QRect(299, 30, 61, 22));
        lb_MainList = new QListWidget(WindowTrackSectorEditor);
        lb_MainList->setObjectName(QString::fromUtf8("lb_MainList"));
        lb_MainList->setGeometry(QRect(10, 110, 371, 171));
        btn_Remove = new QPushButton(WindowTrackSectorEditor);
        btn_Remove->setObjectName(QString::fromUtf8("btn_Remove"));
        btn_Remove->setGeometry(QRect(10, 290, 80, 22));
        btn_SelectTs = new QPushButton(WindowTrackSectorEditor);
        btn_SelectTs->setObjectName(QString::fromUtf8("btn_SelectTs"));
        btn_SelectTs->setGeometry(QRect(270, 290, 111, 22));
        lbl_LbHeading = new QLabel(WindowTrackSectorEditor);
        lbl_LbHeading->setObjectName(QString::fromUtf8("lbl_LbHeading"));
        lbl_LbHeading->setGeometry(QRect(20, 90, 81, 16));
        gb_AddNew = new QGroupBox(WindowTrackSectorEditor);
        gb_AddNew->setObjectName(QString::fromUtf8("gb_AddNew"));
        gb_AddNew->setGeometry(QRect(10, 320, 371, 91));
        lbl_Name = new QLabel(gb_AddNew);
        lbl_Name->setObjectName(QString::fromUtf8("lbl_Name"));
        lbl_Name->setGeometry(QRect(10, 30, 47, 14));
        lbl_Start = new QLabel(gb_AddNew);
        lbl_Start->setObjectName(QString::fromUtf8("lbl_Start"));
        lbl_Start->setGeometry(QRect(10, 60, 47, 14));
        lbl_End = new QLabel(gb_AddNew);
        lbl_End->setObjectName(QString::fromUtf8("lbl_End"));
        lbl_End->setGeometry(QRect(140, 60, 47, 14));
        le_Name = new QLineEdit(gb_AddNew);
        le_Name->setObjectName(QString::fromUtf8("le_Name"));
        le_Name->setGeometry(QRect(50, 30, 241, 21));
        le_Start = new QLineEdit(gb_AddNew);
        le_Start->setObjectName(QString::fromUtf8("le_Start"));
        le_Start->setGeometry(QRect(50, 60, 71, 21));
        le_End = new QLineEdit(gb_AddNew);
        le_End->setObjectName(QString::fromUtf8("le_End"));
        le_End->setGeometry(QRect(170, 60, 71, 21));
        btn_Add = new QPushButton(gb_AddNew);
        btn_Add->setObjectName(QString::fromUtf8("btn_Add"));
        btn_Add->setGeometry(QRect(300, 30, 61, 22));

        retranslateUi(WindowTrackSectorEditor);

        QMetaObject::connectSlotsByName(WindowTrackSectorEditor);
    } // setupUi

    void retranslateUi(QDialog *WindowTrackSectorEditor)
    {
        WindowTrackSectorEditor->setWindowTitle(QCoreApplication::translate("WindowTrackSectorEditor", "Track Sectors", nullptr));
        gb_TrackSelection->setTitle(QCoreApplication::translate("WindowTrackSectorEditor", "Selected track and configuration:", nullptr));
        le_TrackName->setText(QCoreApplication::translate("WindowTrackSectorEditor", "None", nullptr));
        btn_TrackSelect->setText(QCoreApplication::translate("WindowTrackSectorEditor", "Select", nullptr));
        btn_Remove->setText(QCoreApplication::translate("WindowTrackSectorEditor", "Remove", nullptr));
        btn_SelectTs->setText(QCoreApplication::translate("WindowTrackSectorEditor", "Select", nullptr));
        lbl_LbHeading->setText(QCoreApplication::translate("WindowTrackSectorEditor", "Track Sectors:", nullptr));
        gb_AddNew->setTitle(QCoreApplication::translate("WindowTrackSectorEditor", "Add new track sector:", nullptr));
        lbl_Name->setText(QCoreApplication::translate("WindowTrackSectorEditor", "Name:", nullptr));
        lbl_Start->setText(QCoreApplication::translate("WindowTrackSectorEditor", "Start:", nullptr));
        lbl_End->setText(QCoreApplication::translate("WindowTrackSectorEditor", "End:", nullptr));
        btn_Add->setText(QCoreApplication::translate("WindowTrackSectorEditor", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowTrackSectorEditor: public Ui_WindowTrackSectorEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWTRACKSECTOREDITOR_H

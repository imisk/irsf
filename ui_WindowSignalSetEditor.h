/********************************************************************************
** Form generated from reading UI file 'WindowSignalSetEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWSIGNALSETEDITOR_H
#define UI_WINDOWSIGNALSETEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowSignalSetEditor
{
public:
    QGroupBox *gb_SelectedSet;
    QLabel *lbl_NameTitle;
    QLabel *lbl_Signals;
    QLineEdit *le_Name;
    QPushButton *btn_Save;
    QListWidget *lb_Signals;
    QPushButton *btn_AddSignal;
    QPushButton *btn_RemoveSignal;
    QGroupBox *gb_Track;
    QPushButton *btn_TrackSelect;
    QLineEdit *le_TrackName;
    QGroupBox *gb_AvailableSets;
    QListWidget *lb_AvailableSets;
    QPushButton *btn_DeleteSet;
    QPushButton *btn_Select;

    void setupUi(QDialog *WindowSignalSetEditor)
    {
        if (WindowSignalSetEditor->objectName().isEmpty())
            WindowSignalSetEditor->setObjectName(QString::fromUtf8("WindowSignalSetEditor"));
        WindowSignalSetEditor->resize(649, 418);
        gb_SelectedSet = new QGroupBox(WindowSignalSetEditor);
        gb_SelectedSet->setObjectName(QString::fromUtf8("gb_SelectedSet"));
        gb_SelectedSet->setGeometry(QRect(310, 10, 321, 381));
        lbl_NameTitle = new QLabel(gb_SelectedSet);
        lbl_NameTitle->setObjectName(QString::fromUtf8("lbl_NameTitle"));
        lbl_NameTitle->setGeometry(QRect(10, 30, 31, 16));
        lbl_Signals = new QLabel(gb_SelectedSet);
        lbl_Signals->setObjectName(QString::fromUtf8("lbl_Signals"));
        lbl_Signals->setGeometry(QRect(10, 120, 47, 14));
        le_Name = new QLineEdit(gb_SelectedSet);
        le_Name->setObjectName(QString::fromUtf8("le_Name"));
        le_Name->setGeometry(QRect(50, 30, 171, 21));
        btn_Save = new QPushButton(gb_SelectedSet);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        btn_Save->setGeometry(QRect(230, 30, 80, 22));
        lb_Signals = new QListWidget(gb_SelectedSet);
        lb_Signals->setObjectName(QString::fromUtf8("lb_Signals"));
        lb_Signals->setGeometry(QRect(10, 140, 301, 191));
        btn_AddSignal = new QPushButton(gb_SelectedSet);
        btn_AddSignal->setObjectName(QString::fromUtf8("btn_AddSignal"));
        btn_AddSignal->setGeometry(QRect(10, 340, 101, 22));
        btn_RemoveSignal = new QPushButton(gb_SelectedSet);
        btn_RemoveSignal->setObjectName(QString::fromUtf8("btn_RemoveSignal"));
        btn_RemoveSignal->setGeometry(QRect(209, 340, 101, 22));
        gb_Track = new QGroupBox(gb_SelectedSet);
        gb_Track->setObjectName(QString::fromUtf8("gb_Track"));
        gb_Track->setGeometry(QRect(10, 60, 301, 51));
        btn_TrackSelect = new QPushButton(gb_Track);
        btn_TrackSelect->setObjectName(QString::fromUtf8("btn_TrackSelect"));
        btn_TrackSelect->setGeometry(QRect(250, 20, 41, 22));
        btn_TrackSelect->setAutoDefault(false);
        le_TrackName = new QLineEdit(gb_Track);
        le_TrackName->setObjectName(QString::fromUtf8("le_TrackName"));
        le_TrackName->setGeometry(QRect(10, 20, 231, 21));
        le_TrackName->setReadOnly(true);
        gb_AvailableSets = new QGroupBox(WindowSignalSetEditor);
        gb_AvailableSets->setObjectName(QString::fromUtf8("gb_AvailableSets"));
        gb_AvailableSets->setGeometry(QRect(10, 10, 291, 381));
        lb_AvailableSets = new QListWidget(gb_AvailableSets);
        lb_AvailableSets->setObjectName(QString::fromUtf8("lb_AvailableSets"));
        lb_AvailableSets->setGeometry(QRect(10, 30, 271, 301));
        btn_DeleteSet = new QPushButton(gb_AvailableSets);
        btn_DeleteSet->setObjectName(QString::fromUtf8("btn_DeleteSet"));
        btn_DeleteSet->setGeometry(QRect(10, 340, 151, 22));
        btn_Select = new QPushButton(gb_AvailableSets);
        btn_Select->setObjectName(QString::fromUtf8("btn_Select"));
        btn_Select->setGeometry(QRect(170, 340, 101, 22));

        retranslateUi(WindowSignalSetEditor);

        QMetaObject::connectSlotsByName(WindowSignalSetEditor);
    } // setupUi

    void retranslateUi(QDialog *WindowSignalSetEditor)
    {
        WindowSignalSetEditor->setWindowTitle(QCoreApplication::translate("WindowSignalSetEditor", "Dialog", nullptr));
        gb_SelectedSet->setTitle(QCoreApplication::translate("WindowSignalSetEditor", "Currently selected set:", nullptr));
        lbl_NameTitle->setText(QCoreApplication::translate("WindowSignalSetEditor", "Name:", nullptr));
        lbl_Signals->setText(QCoreApplication::translate("WindowSignalSetEditor", "Signals:", nullptr));
        le_Name->setText(QCoreApplication::translate("WindowSignalSetEditor", "None", nullptr));
        btn_Save->setText(QCoreApplication::translate("WindowSignalSetEditor", "Create new", nullptr));
        btn_AddSignal->setText(QCoreApplication::translate("WindowSignalSetEditor", "Add Signal", nullptr));
        btn_RemoveSignal->setText(QCoreApplication::translate("WindowSignalSetEditor", "Remove Signal", nullptr));
        gb_Track->setTitle(QCoreApplication::translate("WindowSignalSetEditor", "Selected track:", nullptr));
        btn_TrackSelect->setText(QCoreApplication::translate("WindowSignalSetEditor", "Select", nullptr));
        le_TrackName->setText(QCoreApplication::translate("WindowSignalSetEditor", "None", nullptr));
        gb_AvailableSets->setTitle(QCoreApplication::translate("WindowSignalSetEditor", "Available sets:", nullptr));
        btn_DeleteSet->setText(QCoreApplication::translate("WindowSignalSetEditor", "Delete selected Signal Set", nullptr));
        btn_Select->setText(QCoreApplication::translate("WindowSignalSetEditor", "SELECT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowSignalSetEditor: public Ui_WindowSignalSetEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWSIGNALSETEDITOR_H

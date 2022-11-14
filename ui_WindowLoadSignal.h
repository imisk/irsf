/********************************************************************************
** Form generated from reading UI file 'WindowLoadSignal.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWLOADSIGNAL_H
#define UI_WINDOWLOADSIGNAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowLoadSignal
{
public:
    QListWidget *lb_Main;
    QPushButton *btn_Select;
    QPushButton *btn_Delete;
    QPushButton *btn_Cancel;

    void setupUi(QDialog *WindowLoadSignal)
    {
        if (WindowLoadSignal->objectName().isEmpty())
            WindowLoadSignal->setObjectName(QString::fromUtf8("WindowLoadSignal"));
        WindowLoadSignal->resize(400, 303);
        lb_Main = new QListWidget(WindowLoadSignal);
        lb_Main->setObjectName(QString::fromUtf8("lb_Main"));
        lb_Main->setGeometry(QRect(10, 30, 371, 231));
        btn_Select = new QPushButton(WindowLoadSignal);
        btn_Select->setObjectName(QString::fromUtf8("btn_Select"));
        btn_Select->setGeometry(QRect(10, 270, 80, 22));
        btn_Delete = new QPushButton(WindowLoadSignal);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(130, 270, 80, 22));
        btn_Cancel = new QPushButton(WindowLoadSignal);
        btn_Cancel->setObjectName(QString::fromUtf8("btn_Cancel"));
        btn_Cancel->setGeometry(QRect(300, 270, 80, 22));

        retranslateUi(WindowLoadSignal);

        QMetaObject::connectSlotsByName(WindowLoadSignal);
    } // setupUi

    void retranslateUi(QDialog *WindowLoadSignal)
    {
        WindowLoadSignal->setWindowTitle(QCoreApplication::translate("WindowLoadSignal", "Select signal", nullptr));
        btn_Select->setText(QCoreApplication::translate("WindowLoadSignal", "Load", nullptr));
        btn_Delete->setText(QCoreApplication::translate("WindowLoadSignal", "Delete", nullptr));
        btn_Cancel->setText(QCoreApplication::translate("WindowLoadSignal", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowLoadSignal: public Ui_WindowLoadSignal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWLOADSIGNAL_H

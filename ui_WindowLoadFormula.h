/********************************************************************************
** Form generated from reading UI file 'WindowLoadFormula.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWLOADFORMULA_H
#define UI_WINDOWLOADFORMULA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowLoadFormula
{
public:
    QListWidget *lb_Formulas;
    QLabel *lbl_SelectFormula;
    QPushButton *btn_Load;
    QPushButton *btn_Delete;
    QPushButton *btn_Cancel;

    void setupUi(QDialog *WindowLoadFormula)
    {
        if (WindowLoadFormula->objectName().isEmpty())
            WindowLoadFormula->setObjectName(QString::fromUtf8("WindowLoadFormula"));
        WindowLoadFormula->resize(310, 290);
        lb_Formulas = new QListWidget(WindowLoadFormula);
        lb_Formulas->setObjectName(QString::fromUtf8("lb_Formulas"));
        lb_Formulas->setGeometry(QRect(10, 30, 291, 211));
        lbl_SelectFormula = new QLabel(WindowLoadFormula);
        lbl_SelectFormula->setObjectName(QString::fromUtf8("lbl_SelectFormula"));
        lbl_SelectFormula->setGeometry(QRect(20, 10, 81, 16));
        btn_Load = new QPushButton(WindowLoadFormula);
        btn_Load->setObjectName(QString::fromUtf8("btn_Load"));
        btn_Load->setGeometry(QRect(10, 250, 80, 22));
        btn_Delete = new QPushButton(WindowLoadFormula);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));
        btn_Delete->setGeometry(QRect(100, 250, 80, 22));
        btn_Cancel = new QPushButton(WindowLoadFormula);
        btn_Cancel->setObjectName(QString::fromUtf8("btn_Cancel"));
        btn_Cancel->setGeometry(QRect(220, 250, 80, 22));

        retranslateUi(WindowLoadFormula);

        QMetaObject::connectSlotsByName(WindowLoadFormula);
    } // setupUi

    void retranslateUi(QDialog *WindowLoadFormula)
    {
        WindowLoadFormula->setWindowTitle(QCoreApplication::translate("WindowLoadFormula", "Dialog", nullptr));
        lbl_SelectFormula->setText(QCoreApplication::translate("WindowLoadFormula", "Select formula:", nullptr));
        btn_Load->setText(QCoreApplication::translate("WindowLoadFormula", "Load", nullptr));
        btn_Delete->setText(QCoreApplication::translate("WindowLoadFormula", "Delete", nullptr));
        btn_Cancel->setText(QCoreApplication::translate("WindowLoadFormula", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowLoadFormula: public Ui_WindowLoadFormula {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWLOADFORMULA_H

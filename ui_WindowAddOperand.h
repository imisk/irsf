/********************************************************************************
** Form generated from reading UI file 'WindowAddOperand.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWADDOPERAND_H
#define UI_WINDOWADDOPERAND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_WindowAddOperand
{
public:
    QLabel *lbl_SelectValue;
    QGroupBox *group_Processing;
    QRadioButton *rb_None;
    QRadioButton *rb_Average;
    QSpinBox *sb_AverageParameter;
    QRadioButton *rb_Delta;
    QLabel *lbl_Symbol;
    QLineEdit *le_Symbol;
    QPushButton *btn_AddToVariableList;
    QPushButton *btn_Cancel;
    QListWidget *lb_Variables;

    void setupUi(QDialog *WindowAddOperand)
    {
        if (WindowAddOperand->objectName().isEmpty())
            WindowAddOperand->setObjectName(QString::fromUtf8("WindowAddOperand"));
        WindowAddOperand->resize(472, 403);
        lbl_SelectValue = new QLabel(WindowAddOperand);
        lbl_SelectValue->setObjectName(QString::fromUtf8("lbl_SelectValue"));
        lbl_SelectValue->setGeometry(QRect(20, 10, 81, 16));
        group_Processing = new QGroupBox(WindowAddOperand);
        group_Processing->setObjectName(QString::fromUtf8("group_Processing"));
        group_Processing->setGeometry(QRect(300, 10, 151, 121));
        rb_None = new QRadioButton(group_Processing);
        rb_None->setObjectName(QString::fromUtf8("rb_None"));
        rb_None->setGeometry(QRect(10, 30, 85, 20));
        rb_None->setChecked(true);
        rb_Average = new QRadioButton(group_Processing);
        rb_Average->setObjectName(QString::fromUtf8("rb_Average"));
        rb_Average->setGeometry(QRect(10, 60, 85, 20));
        sb_AverageParameter = new QSpinBox(group_Processing);
        sb_AverageParameter->setObjectName(QString::fromUtf8("sb_AverageParameter"));
        sb_AverageParameter->setGeometry(QRect(80, 60, 51, 22));
        rb_Delta = new QRadioButton(group_Processing);
        rb_Delta->setObjectName(QString::fromUtf8("rb_Delta"));
        rb_Delta->setGeometry(QRect(10, 90, 85, 20));
        lbl_Symbol = new QLabel(WindowAddOperand);
        lbl_Symbol->setObjectName(QString::fromUtf8("lbl_Symbol"));
        lbl_Symbol->setGeometry(QRect(300, 220, 47, 14));
        le_Symbol = new QLineEdit(WindowAddOperand);
        le_Symbol->setObjectName(QString::fromUtf8("le_Symbol"));
        le_Symbol->setGeometry(QRect(300, 240, 71, 51));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        le_Symbol->setFont(font);
        le_Symbol->setMaxLength(2);
        btn_AddToVariableList = new QPushButton(WindowAddOperand);
        btn_AddToVariableList->setObjectName(QString::fromUtf8("btn_AddToVariableList"));
        btn_AddToVariableList->setGeometry(QRect(380, 340, 71, 51));
        btn_Cancel = new QPushButton(WindowAddOperand);
        btn_Cancel->setObjectName(QString::fromUtf8("btn_Cancel"));
        btn_Cancel->setGeometry(QRect(20, 370, 51, 22));
        lb_Variables = new QListWidget(WindowAddOperand);
        lb_Variables->setObjectName(QString::fromUtf8("lb_Variables"));
        lb_Variables->setGeometry(QRect(20, 30, 261, 331));

        retranslateUi(WindowAddOperand);

        QMetaObject::connectSlotsByName(WindowAddOperand);
    } // setupUi

    void retranslateUi(QDialog *WindowAddOperand)
    {
        WindowAddOperand->setWindowTitle(QCoreApplication::translate("WindowAddOperand", "Dialog", nullptr));
        lbl_SelectValue->setText(QCoreApplication::translate("WindowAddOperand", "Select value:", nullptr));
        group_Processing->setTitle(QCoreApplication::translate("WindowAddOperand", "Processing:", nullptr));
        rb_None->setText(QCoreApplication::translate("WindowAddOperand", "None", nullptr));
        rb_Average->setText(QCoreApplication::translate("WindowAddOperand", "Average", nullptr));
        rb_Delta->setText(QCoreApplication::translate("WindowAddOperand", "Delta", nullptr));
        lbl_Symbol->setText(QCoreApplication::translate("WindowAddOperand", "Symbol:", nullptr));
        btn_AddToVariableList->setText(QCoreApplication::translate("WindowAddOperand", "Add", nullptr));
        btn_Cancel->setText(QCoreApplication::translate("WindowAddOperand", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowAddOperand: public Ui_WindowAddOperand {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWADDOPERAND_H

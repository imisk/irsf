/********************************************************************************
** Form generated from reading UI file 'WindowFormulaEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWFORMULAEDITOR_H
#define UI_WINDOWFORMULAEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WindowFormulaEditor
{
public:
    QGroupBox *group_WriteToFormula;
    QPushButton *btn_AddPlus;
    QPushButton *btn_AddMinus;
    QPushButton *btn_AddMultiply;
    QPushButton *btn_AddDivide;
    QPushButton *btn_AddOpenBracket;
    QPushButton *btn_AddCloseBracket;
    QPushButton *btn_AddValueToList;
    QLabel *lbl_Values;
    QPushButton *btn_AddOperand;
    QPushButton *btn_AddAbs;
    QListWidget *lb_Variables;
    QGroupBox *group_CurrentFormula;
    QLabel *lbl_Name;
    QLineEdit *le_FormulaName;
    QLineEdit *le_CurrentFormula;
    QLabel *lbl_Equation;
    QPushButton *btn_SaveFormula;
    QPushButton *btn_ClearFormula;
    QPushButton *btn_LoadFormula;
    QPushButton *btn_Evaluate;

    void setupUi(QDialog *WindowFormulaEditor)
    {
        if (WindowFormulaEditor->objectName().isEmpty())
            WindowFormulaEditor->setObjectName(QString::fromUtf8("WindowFormulaEditor"));
        WindowFormulaEditor->resize(582, 409);
        group_WriteToFormula = new QGroupBox(WindowFormulaEditor);
        group_WriteToFormula->setObjectName(QString::fromUtf8("group_WriteToFormula"));
        group_WriteToFormula->setGeometry(QRect(10, 180, 561, 211));
        btn_AddPlus = new QPushButton(group_WriteToFormula);
        btn_AddPlus->setObjectName(QString::fromUtf8("btn_AddPlus"));
        btn_AddPlus->setGeometry(QRect(10, 30, 31, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        btn_AddPlus->setFont(font);
        btn_AddPlus->setText(QString::fromUtf8("+"));
        btn_AddMinus = new QPushButton(group_WriteToFormula);
        btn_AddMinus->setObjectName(QString::fromUtf8("btn_AddMinus"));
        btn_AddMinus->setGeometry(QRect(50, 30, 31, 31));
        btn_AddMinus->setFont(font);
        btn_AddMinus->setText(QString::fromUtf8("-"));
        btn_AddMultiply = new QPushButton(group_WriteToFormula);
        btn_AddMultiply->setObjectName(QString::fromUtf8("btn_AddMultiply"));
        btn_AddMultiply->setGeometry(QRect(90, 30, 31, 31));
        btn_AddMultiply->setFont(font);
        btn_AddMultiply->setText(QString::fromUtf8("*"));
        btn_AddDivide = new QPushButton(group_WriteToFormula);
        btn_AddDivide->setObjectName(QString::fromUtf8("btn_AddDivide"));
        btn_AddDivide->setGeometry(QRect(130, 30, 31, 31));
        btn_AddDivide->setFont(font);
        btn_AddDivide->setText(QString::fromUtf8("/"));
        btn_AddOpenBracket = new QPushButton(group_WriteToFormula);
        btn_AddOpenBracket->setObjectName(QString::fromUtf8("btn_AddOpenBracket"));
        btn_AddOpenBracket->setGeometry(QRect(170, 30, 31, 31));
        btn_AddOpenBracket->setFont(font);
        btn_AddOpenBracket->setText(QString::fromUtf8("("));
        btn_AddCloseBracket = new QPushButton(group_WriteToFormula);
        btn_AddCloseBracket->setObjectName(QString::fromUtf8("btn_AddCloseBracket"));
        btn_AddCloseBracket->setGeometry(QRect(210, 30, 31, 31));
        btn_AddCloseBracket->setFont(font);
        btn_AddCloseBracket->setText(QString::fromUtf8(")"));
        btn_AddValueToList = new QPushButton(group_WriteToFormula);
        btn_AddValueToList->setObjectName(QString::fromUtf8("btn_AddValueToList"));
        btn_AddValueToList->setGeometry(QRect(10, 180, 141, 22));
        lbl_Values = new QLabel(group_WriteToFormula);
        lbl_Values->setObjectName(QString::fromUtf8("lbl_Values"));
        lbl_Values->setGeometry(QRect(10, 70, 47, 14));
        btn_AddOperand = new QPushButton(group_WriteToFormula);
        btn_AddOperand->setObjectName(QString::fromUtf8("btn_AddOperand"));
        btn_AddOperand->setEnabled(false);
        btn_AddOperand->setGeometry(QRect(350, 110, 41, 41));
        btn_AddOperand->setFont(font);
        btn_AddOperand->setText(QString::fromUtf8(""));
        btn_AddAbs = new QPushButton(group_WriteToFormula);
        btn_AddAbs->setObjectName(QString::fromUtf8("btn_AddAbs"));
        btn_AddAbs->setGeometry(QRect(250, 30, 41, 31));
        btn_AddAbs->setFont(font);
        btn_AddAbs->setText(QString::fromUtf8("Abs"));
        lb_Variables = new QListWidget(group_WriteToFormula);
        lb_Variables->setObjectName(QString::fromUtf8("lb_Variables"));
        lb_Variables->setGeometry(QRect(10, 90, 331, 81));
        group_CurrentFormula = new QGroupBox(WindowFormulaEditor);
        group_CurrentFormula->setObjectName(QString::fromUtf8("group_CurrentFormula"));
        group_CurrentFormula->setGeometry(QRect(10, 20, 561, 151));
        lbl_Name = new QLabel(group_CurrentFormula);
        lbl_Name->setObjectName(QString::fromUtf8("lbl_Name"));
        lbl_Name->setGeometry(QRect(310, 30, 47, 14));
        le_FormulaName = new QLineEdit(group_CurrentFormula);
        le_FormulaName->setObjectName(QString::fromUtf8("le_FormulaName"));
        le_FormulaName->setGeometry(QRect(360, 30, 191, 21));
        le_CurrentFormula = new QLineEdit(group_CurrentFormula);
        le_CurrentFormula->setObjectName(QString::fromUtf8("le_CurrentFormula"));
        le_CurrentFormula->setGeometry(QRect(10, 70, 541, 41));
        le_CurrentFormula->setBaseSize(QSize(0, 0));
        le_CurrentFormula->setFont(font);
        le_CurrentFormula->setText(QString::fromUtf8("(A+B)/C"));
        le_CurrentFormula->setFrame(true);
        le_CurrentFormula->setReadOnly(true);
        lbl_Equation = new QLabel(group_CurrentFormula);
        lbl_Equation->setObjectName(QString::fromUtf8("lbl_Equation"));
        lbl_Equation->setGeometry(QRect(10, 50, 51, 16));
        btn_SaveFormula = new QPushButton(group_CurrentFormula);
        btn_SaveFormula->setObjectName(QString::fromUtf8("btn_SaveFormula"));
        btn_SaveFormula->setGeometry(QRect(390, 120, 80, 22));
        btn_ClearFormula = new QPushButton(group_CurrentFormula);
        btn_ClearFormula->setObjectName(QString::fromUtf8("btn_ClearFormula"));
        btn_ClearFormula->setGeometry(QRect(90, 120, 80, 22));
        btn_LoadFormula = new QPushButton(group_CurrentFormula);
        btn_LoadFormula->setObjectName(QString::fromUtf8("btn_LoadFormula"));
        btn_LoadFormula->setGeometry(QRect(290, 120, 80, 22));
        btn_Evaluate = new QPushButton(group_CurrentFormula);
        btn_Evaluate->setObjectName(QString::fromUtf8("btn_Evaluate"));
        btn_Evaluate->setGeometry(QRect(190, 120, 80, 22));

        retranslateUi(WindowFormulaEditor);

        QMetaObject::connectSlotsByName(WindowFormulaEditor);
    } // setupUi

    void retranslateUi(QDialog *WindowFormulaEditor)
    {
        WindowFormulaEditor->setWindowTitle(QCoreApplication::translate("WindowFormulaEditor", "Dialog", nullptr));
        group_WriteToFormula->setTitle(QCoreApplication::translate("WindowFormulaEditor", "Add to formula:", nullptr));
        btn_AddValueToList->setText(QCoreApplication::translate("WindowFormulaEditor", "Add value to list", nullptr));
        lbl_Values->setText(QCoreApplication::translate("WindowFormulaEditor", "Values:", nullptr));
        group_CurrentFormula->setTitle(QCoreApplication::translate("WindowFormulaEditor", "Current formula:", nullptr));
        lbl_Name->setText(QCoreApplication::translate("WindowFormulaEditor", "Name:", nullptr));
#if QT_CONFIG(tooltip)
        le_CurrentFormula->setToolTip(QCoreApplication::translate("WindowFormulaEditor", "Current formula", nullptr));
#endif // QT_CONFIG(tooltip)
        lbl_Equation->setText(QCoreApplication::translate("WindowFormulaEditor", "Equation:", nullptr));
        btn_SaveFormula->setText(QCoreApplication::translate("WindowFormulaEditor", "Save", nullptr));
        btn_ClearFormula->setText(QCoreApplication::translate("WindowFormulaEditor", "Clear", nullptr));
        btn_LoadFormula->setText(QCoreApplication::translate("WindowFormulaEditor", "Load", nullptr));
        btn_Evaluate->setText(QCoreApplication::translate("WindowFormulaEditor", "Evaluate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowFormulaEditor: public Ui_WindowFormulaEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWFORMULAEDITOR_H

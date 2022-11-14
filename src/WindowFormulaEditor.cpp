
#include "WindowFormulaEditor.h"
#include "ErrorMessageBoxUtility.h"
#include "QDebug"
#include "ui_WindowFormulaEditor.h"

using namespace irsf;

WindowFormulaEditor::WindowFormulaEditor(FormulaDbManager* fdm, QWidget* parent)
    : QDialog(parent), ui(new Ui::WindowFormulaEditor) {
  ui->setupUi(this);

  mngr = std::make_unique<FormulaEditorManager>(fdm);
}

WindowFormulaEditor::~WindowFormulaEditor() {
  delete ui;
}

void WindowFormulaEditor::Init() {
  windowAddOperand = std::make_unique<WindowAddOperand>(mngr.get(), this);

  windowLoadFormula = std::make_unique<WindowLoadFormula>(this);

  connect(windowAddOperand.get(), SIGNAL(addButtonClicked()), this,
          SLOT(slotRefreshLB()));

  connect(windowLoadFormula.get(), SIGNAL(loadButtonClicked()), this,
          SLOT(slotRefreshWindow()));

  connect(windowLoadFormula.get(), SIGNAL(selectedFormulaChanged()), this,
          SLOT(slotRefreshWindow()));

  connect(windowLoadFormula.get(), &WindowLoadFormula::deleteButtonClicked,
          this, &WindowFormulaEditor::slotDeleteFormula);
}

void WindowFormulaEditor::slotRefreshLB() {
  try {
    if (mngr->GetCurrentFormula() == nullptr)
      return;

    ui->lb_Variables->clear();

    for (const auto& operand : mngr->GetCurrentFormula()->operandsInList) {
      QString itm(operand.GetListBoxName().c_str());
      ui->lb_Variables->addItem(itm);
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::slotRefreshWindow() {
  try {
    Formula* sel = windowLoadFormula->GetSelectedFormula();

    *mngr->GetCurrentFormula() = *sel;  // copy the values into current

    if (mngr->GetCurrentFormula() == nullptr)
      return;

    QString qs;
    qs = mngr->GetEquationText();
    ui->le_CurrentFormula->setText(qs);

    ui->le_FormulaName->setText(
        QString(mngr->GetCurrentFormula()->name.c_str()));

    slotRefreshLB();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::slotDeleteFormula() {
  try {
    std::cout << "Delete formula: " << mngr->GetCurrentFormula()->name
              << std::endl;

    mngr->DeleteCurrentFormula();

    windowLoadFormula->RefreshFormulaList(mngr->GetFormulaList());

    windowLoadFormula->SelectFirstFormula(mngr->GetFormulaList());

    slotRefreshWindow();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddValueToList_clicked() {
  windowAddOperand->show();
}

void WindowFormulaEditor::on_btn_ClearFormula_clicked() {
  try {
    mngr->ClearCurrentFormula();
    ui->le_CurrentFormula->setText("");
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_lb_Variables_currentTextChanged(
    const QString& currentText) {
  try {
    for (auto& operand : mngr->GetCurrentFormula()->operandsInList) {
      if (operand.GetListBoxName() == currentText.toStdString()) {
        mngr->SetCurrentlySelectedOperand(&operand);

        ui->btn_AddOperand->setText(QString(operand.GetSymbol().c_str()));

        break;
      }
    }

    ui->btn_AddOperand->setEnabled(true);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddPlus_clicked() {
  try {
    QString qs;
    mngr->AddOperatorToFormula(OperatorId::Add, qs);
    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddOperand_clicked() {
  try {
    QString qs;

    mngr->AddOperandToFormula(*mngr->GetCurrentlySelectedOperand(), qs);

    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddMinus_clicked() {
  try {
    QString qs;
    mngr->AddOperatorToFormula(OperatorId::Subtract, qs);
    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddMultiply_clicked() {
  try {
    QString qs;
    mngr->AddOperatorToFormula(OperatorId::Multiply, qs);
    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddDivide_clicked() {
  try {
    QString qs;
    mngr->AddOperatorToFormula(OperatorId::Divide, qs);
    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddOpenBracket_clicked() {
  try {
    QString qs;
    mngr->AddOperatorToFormula(OperatorId::OpenBracket, qs);
    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddCloseBracket_clicked() {
  try {
    QString qs;
    mngr->AddOperatorToFormula(OperatorId::CloseBracket, qs);
    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_AddAbs_clicked() {
  try {
    QString qs;
    mngr->AddOperatorToFormula(OperatorId::Absolute, qs);
    ui->le_CurrentFormula->setText(qs);
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_Evaluate_clicked() {
  try {
    mngr->EvaluateCurrentFormula();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_SaveFormula_clicked() {
  try {
    mngr->EvaluateCurrentFormula();

    QString fName = ui->le_FormulaName->text();
    mngr->SaveCurrentFormula(fName);

    QString msg = "Formula saved";
    ShowMessageBox(msg);

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowFormulaEditor::on_btn_LoadFormula_clicked() {
  try {
    windowLoadFormula->RefreshFormulaList(mngr->GetFormulaList());
    windowLoadFormula->show();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

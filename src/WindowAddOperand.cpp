
#include "WindowAddOperand.h"
#include "ErrorMessageBoxUtility.h"
#include "ui_WindowAddOperand.h"
#include "Utilities.h"

using namespace irsf;

WindowAddOperand::WindowAddOperand(FormulaEditorManager* manager,
                                   QWidget* parent)
    : QDialog(parent), ui(new Ui::WindowAddOperand), mngr(manager) {
  ui->setupUi(this);

  std::vector<std::string> varList;

  varList = GetNamesOfAllInputVariableRawAndDerived();

  for (const auto& s : varList) {
    ui->lb_Variables->addItem(QString(s.c_str()));
  }
}

WindowAddOperand::~WindowAddOperand() {
  delete ui;
}

void WindowAddOperand::on_btn_AddToVariableList_clicked() {
  try {
    std::string curSymbol = ui->le_Symbol->text().toStdString();

    if (curSymbol.size() == 0)
      throw IrsfException(IrsfError::NoSymbolWasInput);

    bool symbolExists = false;
    bool finished = false;
    size_t i = 0;

    while (!finished) {
      const auto& operand = mngr->GetCurrentFormula()->operandsInList[i];
      if (operand.GetSymbol() == curSymbol) {
        symbolExists = true;
        finished = true;
      }

      ++i;
      if (i == mngr->GetCurrentFormula()->operandsInList.size())
        finished = true;
    }

    if (symbolExists)
      throw IrsfException(IrsfError::SymbolAlreadyExists);

    VariableId selectedVariable = GetVariableIdFromVariableName(
        ui->lb_Variables->currentItem()->text().toStdString());

    if (selectedVariable == VariableId::VariableUnknown)
      throw IrsfException(IrsfError::NoVariableSelected);

    InputVariableDescriptor inVarDesc;

    if (ui->rb_None->isChecked()) {
      inVarDesc.variableId = selectedVariable;
    } else {
      if (ui->rb_Average->isChecked()) {
        int32_t AveragePeriod = ui->sb_AverageParameter->text().toInt();

        if (AveragePeriod == 0)
          throw IrsfException(IrsfError::InvalidInputForAveragePeriod);

        inVarDesc.variableId = VariableId::ProcessedAverage;
        inVarDesc.variableIdForProcessing = selectedVariable;
        inVarDesc.parameterForProcessing = AveragePeriod;

      } else if (ui->rb_Delta->isChecked()) {
        inVarDesc.variableId = VariableId::ProcessedDelta;
        inVarDesc.variableIdForProcessing = selectedVariable;
      }
    }

    FormulaOperand fo(curSymbol, inVarDesc);

    mngr->GetCurrentFormula()->operandsInList.push_back(fo);

    addButtonClicked();

    this->hide();

  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

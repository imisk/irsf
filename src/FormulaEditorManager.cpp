
#include "FormulaEditorManager.h"
#include "FormulaOperator.h"
#include "QDebug"
using namespace irsf;

FormulaEditorManager::FormulaEditorManager(FormulaDbManager* fdm) noexcept
    : db(fdm) {
  currentFormula->name = "";
}

void FormulaEditorManager::ClearCurrentFormula() noexcept {
  if (currentFormula) {
    currentFormula->currentFormulaInfix.clear();
  }
}

void FormulaEditorManager::AddOperatorToFormula(OperatorId op,
                                                QString& updatedEquationText) {
  if (currentFormula) {
    auto fop = std::make_unique<FormulaOperator>(op);
    currentFormula->currentFormulaInfix.emplace_back(std::move(fop));

    //.updatedEquationText = ":to-be-implemented-";
    updatedEquationText = GetEquationText();
  }
}

void FormulaEditorManager::AddOperandToFormula(FormulaOperand op,
                                               QString& updatedEquationText) {
  if (currentFormula) {
    auto o = std::make_unique<FormulaOperand>(op);

    currentFormula->currentFormulaInfix.emplace_back(std::move(o));

    updatedEquationText = GetEquationText();
  }
}

void FormulaEditorManager::EvaluateCurrentFormula() {
  evaluator->CheckFormulaValidity(currentFormula->GetCurrentFormulaInfix());
}

Formula* FormulaEditorManager::GetCurrentFormula() const noexcept {
  return currentFormula.get();
}

void FormulaEditorManager::SetCurrentlySelectedOperand(
    FormulaOperand* f) noexcept {
  currentlySelectedOperand = f;
}

FormulaOperand* FormulaEditorManager::GetCurrentlySelectedOperand()
    const noexcept {
  return currentlySelectedOperand;
}

void FormulaEditorManager::SaveCurrentFormula(QString& formulaName) const {
  std::cout << "fem : SaveCurrentFormula __ name = "
            << formulaName.toStdString() << std::endl;

  if (formulaName.size() == 0)
    throw IrsfException(IrsfException(IrsfError::InvalidName));

  Formula* fromDb = db->GetFormulaWithName(formulaName.toStdString());

  // if this is a formula with a new name
  if (fromDb == nullptr) {
    currentFormula->name = formulaName.toStdString();

    db->SaveFormula(currentFormula.get(), true);

    std::cout << "Saving new formula with name: " << currentFormula->name
              << std::endl;
  } else {
    /*
     * otherwise, use the current one (basically just re-save the database)
     * copy the updated parameters from the current
     */
    *fromDb = *currentFormula;

    db->SaveFormula(nullptr, false);

    std::cout << "Overwriting existing formula with name: "
              << currentFormula->name << std::endl;
  }
}

void FormulaEditorManager::DeleteCurrentFormula() {
  db->DeleteFormula(currentFormula->name);
}

std::vector<Formula*> FormulaEditorManager::GetFormulaList() const noexcept {
  return db->GetFormulaList();
}

QString FormulaEditorManager::GetEquationText() const noexcept {
  QString retEquation = "";

  bool trailingBracket = false;

  for (auto& symbol : currentFormula->currentFormulaInfix) {
    if (symbol->IsOperand() == true) {
      const auto operand = dynamic_cast<FormulaOperand*>(symbol.get());

      if (operand) {
        retEquation += QString(operand->GetSymbol().c_str());

        if (trailingBracket)
          retEquation += ")";
        trailingBracket = false;
      }

    } else {
      const auto* op = dynamic_cast<FormulaOperator*>(symbol.get());

      if (op) {
        switch (op->GetOperatorId()) {
          case OperatorId::Add:
            retEquation += "+";
            break;
          case OperatorId::Subtract:
            retEquation += "-";
            break;
          case OperatorId::Divide:
            retEquation += "/";
            break;
          case OperatorId::Multiply:
            retEquation += "*";
            break;
          case OperatorId::OpenBracket:
            retEquation += "(";
            break;
          case OperatorId::CloseBracket:
            retEquation += ")";
            break;
          case OperatorId::Absolute:
            retEquation += "Abs(";
            trailingBracket = true;
            break;
          case OperatorId::Unknown:
            break;
        }
      }
    }
  }

  return retEquation;
}

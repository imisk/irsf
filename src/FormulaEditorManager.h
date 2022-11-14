#ifndef FORMULAEDITORMANAGER_H
#define FORMULAEDITORMANAGER_H

#include <iostream>
#include <vector>
#include "Formula.h"
#include "FormulaDbManager.h"
#include "FormulaEvaluator.h"
#include "FormulaInputVariableFactory.h"
#include "FormulaOperand.h"
#include "IrsfCommon.h"
namespace irsf {
/*
 * Used to edit formulas
 */
class FormulaEditorManager {
 public:
  explicit FormulaEditorManager(FormulaDbManager* fdm) noexcept;

  void ClearCurrentFormula() noexcept;

  void AddOperatorToFormula(OperatorId op, QString& updatedEquationText);

  void AddOperandToFormula(FormulaOperand op, QString& updatedEquationText);

  /*
   * Evaluates currentFormula
   */
  void EvaluateCurrentFormula();

  Formula* GetCurrentFormula() const noexcept;

  void SetCurrentlySelectedOperand(FormulaOperand* f) noexcept;

  FormulaOperand* GetCurrentlySelectedOperand() const noexcept;

  void SaveCurrentFormula(QString& formulaName) const;

  void DeleteCurrentFormula();

  std::vector<Formula*> GetFormulaList() const noexcept;

  /*
   * Returns readable equation text for currentFormula
   */
  QString GetEquationText() const noexcept;

 private:
  FormulaOperand* currentlySelectedOperand{nullptr};

  std::unique_ptr<Formula> currentFormula{std::make_unique<Formula>()};

  std::unique_ptr<FormulaInputVariableFactory> factory{
      std::make_unique<FormulaInputVariableFactory>()};

  std::unique_ptr<FormulaEvaluator> evaluator{
      std::make_unique<FormulaEvaluator>()};

  FormulaDbManager* db;
};
}  // namespace irsf
#endif  // FORMULAEDITORMANAGER_H

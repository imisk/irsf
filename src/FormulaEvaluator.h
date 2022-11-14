#ifndef FORMULAEVALUATOR_H
#define FORMULAEVALUATOR_H

#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include "InputVariableInterface.h"
#include "IrsfCommon.h"
namespace irsf {

/*
 * Formula evaluation and validity checking
 */
class FormulaEvaluator {
 public:
  explicit FormulaEvaluator() noexcept;

  /* Check if the supplied infix formula is valid and can be interpreted.
   * To be valid, it must make sense (ie not having two operators one
   * after another)
   * Returns IrsfError::OK if valid.
   */
  void CheckFormulaValidity(
      const std::vector<FormulaSymbolBase*>& infixFormula);

  void InfixToPostfix(
      std::vector<FormulaSymbolBase*> infixFormula,
      std::vector<FormulaSymbolBase*>& postfixFormula) const noexcept;

  void EvaluateFormula(
      std::vector<FormulaSymbolEvaluated*>& postfixFormulaEvaluated,
      float* evaluatedValue) const;

  /* Convert the postfix formula from descriptive objects to evaluated
   * (real) objects.
   * This one is for mock values, just to test the evaluation without
   * connecting to the iRacing SDK.
   */
  void CreateFormulaEvaluatedMockValues(
      std::vector<FormulaSymbolBase*>& postfixFormula,
      std::vector<SymbEvaluated>& postfixFormulaEvaluated);

  /* Convert the postfix formula from descriptive objects
   * to evaluated (real) objects.
   */
  void CreateFormulaEvaluatedValues(
      std::vector<iVarInterface_sp>& inputVariables,
      std::vector<FormulaSymbolBase*>& postfixFormula,
      std::vector<SymbEvaluated>& postfixFormulaEvaluated,
      std::vector<FormulaSymbolEvaluated*>& postfixFormulaEvaluated_p);

 private:
  int32_t GetPrecedence(OperatorId opId) const noexcept;

  std::vector<std::shared_ptr<float>> mockValueStore;
};
}  // namespace irsf
#endif  // FORMULAEVALUATOR_H

#ifndef FORMULAOPERAND_H
#define FORMULAOPERAND_H

#include <string>
#include "IrsfCommon.h"
namespace irsf {
/*
 * FormulaOperand is a symbol in a formula, assigned to an input value
 */
class FormulaOperand : public FormulaSymbolBase {
  friend class FormulaDbManager;

 public:
  explicit FormulaOperand(const std::string& operandSymbol,
                          InputVariableDescriptor inVarDesc) noexcept;

  FormulaOperand(const FormulaOperand& other);

  FormulaOperand& operator=(const FormulaOperand& other) noexcept;

  FormulaOperand(FormulaOperand&& other) noexcept;

  FormulaOperand& operator=(FormulaOperand&& other) noexcept;

  ~FormulaOperand() override = default;

  // Symbol for the formula editor (a few letters that represent a variableId)
  std::string GetSymbol() const noexcept;

  // Get the descriptive name shown in list of values
  std::string GetOperandDisplayName() const noexcept;

  std::string GetListBoxName() const noexcept;

  VariableId GetVariableId() const noexcept;

 private:
  std::string symbol;

  InputVariableDescriptor inputVariableDescriptor;
};
}  // namespace irsf
#endif  // FORMULAOPERAND_H

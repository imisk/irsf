
#include "FormulaOperand.h"
#include "Utilities.h"

using namespace irsf;

FormulaOperand::FormulaOperand(const std::string& operandSymbol,
                               InputVariableDescriptor inVarDesc) noexcept
    : FormulaSymbolBase(true),
      symbol(operandSymbol),
      inputVariableDescriptor(inVarDesc) {}

FormulaOperand::FormulaOperand(const FormulaOperand& other)
    : FormulaSymbolBase(true),
      symbol(other.symbol),
      inputVariableDescriptor(other.inputVariableDescriptor) {}

std::string FormulaOperand::GetSymbol() const noexcept {
  return symbol;
}

std::string FormulaOperand::GetOperandDisplayName() const noexcept {
  std::string retName = "";

  if (IsVariableIdForProcessedVariable(inputVariableDescriptor.variableId)) {
    retName +=
        GetVariableNameFromVariableId(inputVariableDescriptor.variableId);
    retName += " (";
    retName += GetVariableNameFromVariableId(
        inputVariableDescriptor.variableIdForProcessing);
    retName += ")";
  } else {
    retName = GetVariableNameFromVariableId(inputVariableDescriptor.variableId);
  }

  return retName;
}

std::string FormulaOperand::GetListBoxName() const noexcept {
  std::string name = "";
  name += GetSymbol();
  name += " - ";
  name += GetOperandDisplayName();

  return name;
}

FormulaOperand& FormulaOperand::operator=(
    const FormulaOperand& other) noexcept {
  if (&other == this)
    return *this;

  symbol = other.symbol;
  inputVariableDescriptor = other.inputVariableDescriptor;
  isOperand = other.isOperand;

  return *this;
}

FormulaOperand::FormulaOperand(FormulaOperand&& other) noexcept
    : FormulaSymbolBase(true),
      symbol(other.symbol),
      inputVariableDescriptor(other.inputVariableDescriptor) {
  other.symbol = "";
}

FormulaOperand& FormulaOperand::operator=(FormulaOperand&& other) noexcept {
  symbol = other.symbol;
  inputVariableDescriptor = other.inputVariableDescriptor;
  isOperand = other.IsOperand();

  other.symbol = "";

  return *this;
}

VariableId FormulaOperand::GetVariableId() const noexcept {
  return inputVariableDescriptor.variableId;
}


#include "FormulaOperator.h"

using namespace irsf;

FormulaOperator::FormulaOperator(OperatorId opId) noexcept
    : FormulaSymbolBase(false), operatorId(opId) {}

OperatorId FormulaOperator::GetOperatorId() const noexcept {
  return operatorId;
}

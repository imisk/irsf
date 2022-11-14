#ifndef FORMULAOPERATOR_H
#define FORMULAOPERATOR_H

#include "IrsfCommon.h"  //
namespace irsf {
/*
 * One of the operators such as addition, subtraction, etc. Component of a
 * formula.
 */
class FormulaOperator : public FormulaSymbolBase {
 public:
  FormulaOperator() = delete;

  explicit FormulaOperator(OperatorId opId) noexcept;

  OperatorId GetOperatorId() const noexcept;

 private:
  OperatorId operatorId;
};
}  // namespace irsf
#endif  // FORMULAOPERATOR_H

#ifndef FORMULA_H
#define FORMULA_H

#include <algorithm>
#include <memory>
#include <vector>
#include "FormulaOperand.h"
#include "IrsfCommon.h"
#include "src/FormulaOperator.h"
namespace irsf {

class FormulaOperator;

struct Formula {
  // name is unique identifier
  std::string name;

  // List of variables you can choose
  std::vector<FormulaOperand> operandsInList;

  // The formula, written in infix. Index 0 is start (left).
  std::vector<std::unique_ptr<FormulaSymbolBase>> currentFormulaInfix;

  std::vector<FormulaSymbolBase*> GetCurrentFormulaInfix() noexcept {
    auto lam = [&](auto& up) { return up.get(); };

    std::vector<FormulaSymbolBase*> ret;

    std::transform(currentFormulaInfix.begin(), currentFormulaInfix.end(),
                   std::back_inserter(ret), lam);

    return ret;
  }

  Formula() noexcept : name("") {}

  Formula(const Formula& other) { *this = other; }

  Formula(Formula&& other)
      : name(other.name), operandsInList(other.operandsInList) {
    // warning: using copy in a move function is no longer the desirable
    // behaviour! fix it back the way it was (to-do)
    CopyCurrentFormulaInfix(other.currentFormulaInfix);

    other.operandsInList.clear();
    other.currentFormulaInfix.clear();
  }

  Formula& operator=(const Formula& other) {
    name = other.name;
    operandsInList = other.operandsInList;

    CopyCurrentFormulaInfix(other.currentFormulaInfix);

    return *this;
  }

  Formula& operator=(Formula&& other) {
    if (this != &other) {
      operandsInList.clear();
      currentFormulaInfix.clear();

      name = other.name;
      operandsInList = other.operandsInList;

      // warning: using copy in a move function is no longer the desirable
      // behaviour! fix it back (to-do)
      CopyCurrentFormulaInfix(other.currentFormulaInfix);

      other.operandsInList.clear();
      other.currentFormulaInfix.clear();
      other.name = "";
    }

    return *this;
  }

  ~Formula() {
    name = "";
    operandsInList.clear();
    currentFormulaInfix.clear();
  }

 private:
  void CopyCurrentFormulaInfix(
      const std::vector<std::unique_ptr<FormulaSymbolBase>>& source) {
    currentFormulaInfix.clear();

    for (auto& up : source) {
      if (up->IsOperand()) {
        FormulaOperand* op = dynamic_cast<FormulaOperand*>(up.get());
        if (!op)
          throw IrsfException(IrsfError::GeneralError);

        auto copy = std::make_unique<FormulaOperand>(*op);
        currentFormulaInfix.push_back(std::move(copy));
      } else {
        FormulaOperator* oper = dynamic_cast<FormulaOperator*>(up.get());
        if (!oper)
          throw IrsfException(IrsfError::GeneralError);

        auto copy = std::make_unique<FormulaOperator>(*oper);
        currentFormulaInfix.push_back(std::move(copy));
      }
    }
  }
};
}  // namespace irsf
#endif  // FORMULA_H

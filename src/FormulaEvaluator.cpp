

#include "FormulaEvaluator.h"
#include <algorithm>
#include "FormulaOperand.h"
#include "FormulaOperator.h"

using namespace irsf;

FormulaEvaluator::FormulaEvaluator() noexcept {}

void FormulaEvaluator::CheckFormulaValidity(
    const std::vector<FormulaSymbolBase*>& infixFormula) {
  std::vector<FormulaSymbolBase*> postfix;

  InfixToPostfix(infixFormula, postfix);

  std::cout << "\n\nPostfix formula: ";

  for (size_t i = 0; i < postfix.size(); i++) {
    auto fsb = postfix[i];

    if (fsb->IsOperand()) {
      auto num = dynamic_cast<FormulaOperand*>(fsb);
      if (num)
        std::cout << num->GetSymbol() << " ";
    } else {
      auto op = dynamic_cast<FormulaOperator*>(fsb);

      if (op) {
        switch (op->GetOperatorId()) {
          case OperatorId::Add:
            std::cout << "+ ";
            break;
          case OperatorId::Subtract:
            std::cout << "- ";
            break;
          case OperatorId::Divide:
            std::cout << "/ ";
            break;
          case OperatorId::Multiply:
            std::cout << "* ";
            break;
          case OperatorId::OpenBracket:
            std::cout << "( ";
            break;
          case OperatorId::CloseBracket:
            std::cout << ") ";
            break;
          case OperatorId::Absolute:
            std::cout << "Abs ";
            break;
          case OperatorId::Unknown:
            break;
        }
      }
    }
  }

  std::cout << std::endl;

  std::vector<SymbEvaluated> postfixEval;

  std::vector<FormulaSymbolEvaluated*> postfixEval_p;

  auto evalVal = std::make_unique<float>();

  CreateFormulaEvaluatedMockValues(postfix, postfixEval);

  auto lam = [](const SymbEvaluated& val) { return val.get(); };

  std::transform(postfixEval.cbegin(), postfixEval.cend(),
                 std::back_inserter(postfixEval_p), lam);

  *evalVal = 0.0f;

  EvaluateFormula(postfixEval_p, evalVal.get());

  std::cout << "Mock evaluated value is: " << *evalVal;
}

int32_t FormulaEvaluator::GetPrecedence(OperatorId opId) const noexcept {
  if (opId == OperatorId::Absolute) {
    return 3;
  } else if (opId == OperatorId::Multiply || opId == OperatorId::Divide) {
    return 2;
  } else if (opId == OperatorId::Add || opId == OperatorId::Subtract) {
    return 1;
  } else {
    return -1;
  }
}

void FormulaEvaluator::CreateFormulaEvaluatedMockValues(
    std::vector<FormulaSymbolBase*>& postfixFormula,
    std::vector<SymbEvaluated>& postfixFormulaEvaluated) {
  if (postfixFormula.size() == 0)
    throw IrsfException(IrsfError::FormulaIsEmpty);

  float nextValue = 2.0f;

  std::cout << "Assigning mock values to formula: \n";

  std::map<std::string, std::shared_ptr<float>> mapSymbolValue;

  mockValueStore.clear();

  for (size_t i = 0; i < postfixFormula.size(); i++) {
    if (postfixFormula[i]->IsOperand()) {
      FormulaOperand* num = dynamic_cast<FormulaOperand*>(postfixFormula[i]);

      if (num) {
        std::shared_ptr<float> curValue = nullptr;

        if (mapSymbolValue.count(num->GetSymbol()) != 0) {
          curValue = mapSymbolValue[num->GetSymbol()];
        } else {
          curValue = std::make_shared<float>();

          mockValueStore.push_back(curValue);

          *curValue = nextValue;

          mapSymbolValue.insert({num->GetSymbol(), curValue});
        }

        std::cout << num->GetSymbol() << " = " << *curValue << std::endl;

        auto fse = std::make_unique<FormulaSymbolEvaluated>();
        fse->val = curValue.get();

        postfixFormulaEvaluated.push_back(std::move(fse));

        nextValue += 1.0f;
      }

    } else {
      auto op = dynamic_cast<FormulaOperator*>(postfixFormula[i]);

      if (op) {
        auto fse = std::make_unique<FormulaSymbolEvaluated>();
        fse->val = op->GetOperatorId();

        postfixFormulaEvaluated.push_back(std::move(fse));
      }
    }
  }
}

void FormulaEvaluator::CreateFormulaEvaluatedValues(
    std::vector<iVarInterface_sp>& inputVariables,
    std::vector<FormulaSymbolBase*>& postfixFormula,
    std::vector<SymbEvaluated>& postfixFormulaEvaluated,
    std::vector<FormulaSymbolEvaluated*>& postfixFormulaEvaluated_p) {
  postfixFormulaEvaluated.clear();
  postfixFormulaEvaluated_p.clear();

  std::map<std::string, float*> mapSymbolValue;

  for (size_t i = 0; i < postfixFormula.size(); i++) {
    if (postfixFormula[i]->IsOperand()) {
      FormulaOperand* num = dynamic_cast<FormulaOperand*>(postfixFormula[i]);

      if (num) {
        float* curValue;

        if (mapSymbolValue.count(num->GetSymbol()) != 0) {
          curValue = mapSymbolValue[num->GetSymbol()];
        } else {
          bool varFound = false;

          /*
           * go through the list and find the right pointer from
           * iRacing
           */
          for (size_t j = 0; j < inputVariables.size(); j++) {
            if (inputVariables[j]->GetVariableId() == num->GetVariableId()) {
              curValue = inputVariables[j]->GetPointer();
              varFound = true;
            }
          }

          if (!varFound) {
            std::cout << "Error: could not find the required "
                         "VariableId among input variables. \n";
            throw IrsfException(IrsfError::MissingInputVariable);
          }

          //-------------------------

          mapSymbolValue.insert({num->GetSymbol(), curValue});
        }

        auto fse = std::make_unique<FormulaSymbolEvaluated>();
        fse->val = curValue;

        postfixFormulaEvaluated_p.push_back(fse.get());

        postfixFormulaEvaluated.push_back(std::move(fse));
      }

    } else {
      FormulaOperator* op = dynamic_cast<FormulaOperator*>(postfixFormula[i]);

      if (op) {
        auto fse = std::make_unique<FormulaSymbolEvaluated>();
        fse->val = op->GetOperatorId();

        postfixFormulaEvaluated_p.push_back(fse.get());

        postfixFormulaEvaluated.push_back(std::move(fse));
      }
    }
  }
}

void FormulaEvaluator::InfixToPostfix(
    std::vector<FormulaSymbolBase*> infixFormula,
    std::vector<FormulaSymbolBase*>& postfixFormula) const noexcept {
  std::stack<FormulaOperator*> st;

  size_t l = infixFormula.size();

  postfixFormula.clear();

  for (size_t i = 0; i < l; i++) {
    if (infixFormula[i]->IsOperand()) {
      postfixFormula.push_back(infixFormula[i]);
    } else {
      FormulaOperator* op = dynamic_cast<FormulaOperator*>(infixFormula[i]);

      if (op) {
        if (op->GetOperatorId() == OperatorId::OpenBracket) {
          st.push(op);
        } else if (op->GetOperatorId() == OperatorId::CloseBracket) {
          while (st.size() != 0 &&
                 st.top()->GetOperatorId() != OperatorId::OpenBracket) {
            FormulaOperator* c = st.top();
            st.pop();
            postfixFormula.push_back(c);
          }

          if (st.size() != 0) {
            if (st.top()->GetOperatorId() == OperatorId::OpenBracket) {
              st.pop();
            }
          }

        } else {  // If an operator is scanned

          while (st.size() != 0 &&
                 GetPrecedence(op->GetOperatorId()) <=
                     GetPrecedence(st.top()->GetOperatorId())) {
            FormulaOperator* c = st.top();
            st.pop();
            postfixFormula.push_back(c);
          }
          st.push(op);
        }
      }
    }
  }

  while (st.size() != 0) {
    FormulaOperator* c = st.top();
    st.pop();
    postfixFormula.push_back(c);
  }
}

void FormulaEvaluator::EvaluateFormula(
    std::vector<FormulaSymbolEvaluated*>& postfixFormulaEvaluated,
    float* evaluatedValue) const {
  std::stack<float> values;

  const auto& formula = postfixFormulaEvaluated;

  float v1 = 0.0f;
  float v2 = 0.0f;

  for (size_t i = 0; i < formula.size(); i++) {
    float** ptr = std::get_if<float*>(&formula[i]->val);

    if (ptr != nullptr) {
      float* operandValue = *ptr;
      values.push(*operandValue);
    } else {
      OperatorId* opId = std::get_if<OperatorId>(&formula[i]->val);

      switch (*opId) {
        case OperatorId::Add:
          if (values.size() < 2)
            throw IrsfException(IrsfError::FormulaEvaluationTooManyOperators);
          v1 = values.top();
          values.pop();
          v2 = values.top();
          values.pop();
          values.push(v1 + v2);
          break;

        case OperatorId::Subtract:
          if (values.size() < 2)
            throw IrsfException(IrsfError::FormulaEvaluationTooManyOperators);
          v1 = values.top();
          values.pop();
          v2 = values.top();
          values.pop();
          values.push(v2 - v1);
          break;

        case OperatorId::Divide:
          if (values.size() < 2)
            throw IrsfException(IrsfError::FormulaEvaluationTooManyOperators);
          v1 = values.top();
          values.pop();
          v2 = values.top();
          values.pop();
          values.push(v2 / v1);
          break;

        case OperatorId::Multiply:
          if (values.size() < 2)
            throw IrsfException(IrsfError::FormulaEvaluationTooManyOperators);
          v1 = values.top();
          values.pop();
          v2 = values.top();
          values.pop();
          values.push(v1 * v2);
          break;

        case OperatorId::Absolute:
          if (values.size() < 1)
            throw IrsfException(IrsfError::FormulaEvaluationTooManyOperators);
          v1 = values.top();
          values.pop();
          values.push(std::abs(v1));
          break;

        default:
          break;
      }
    }
  }

  if (values.size() != 1)
    throw IrsfException(IrsfError::FormulaEvaluationTooManyOperands);

  *evaluatedValue = values.top();
}

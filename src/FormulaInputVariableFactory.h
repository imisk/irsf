#ifndef FORMULAINPUTVARIABLEFACTORY_H
#define FORMULAINPUTVARIABLEFACTORY_H

#include "InputVariableInterface.h"
namespace irsf {
class FormulaInputVariableFactory {
 public:
  FormulaInputVariableFactory() noexcept;

  /*
   *  variableId: id of the variable to create
      retInputVar: the returned object
  */
  void CreateInputVariable(
      VariableId variableId,
      std::unique_ptr<InputVariableInterface>& retInputVar) const noexcept;

  void CreateInputVariableProcessed(
      VariableId processId,
      VariableId variableToProcess,
      int32_t optionalParameter,
      std::unique_ptr<InputVariableInterface>& retInputVar);
};
}  // namespace irsf
#endif  // FORMULAINPUTVARIABLEFACTORY_H

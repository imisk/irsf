#ifndef FORMULADBMANAGER_H
#define FORMULADBMANAGER_H

#include "Formula.h"

#include <fstream>

#include <iostream>
#include <memory>
#include "OUContainer.h"
#include "QDebug"

namespace irsf {

constexpr int32_t kCurrentFormulaDbFileVersion = 1;

/*
Class responsible for holding the data about user created formulas.

to-do : this class doesn't respect the single responsibility principle. kinda?
*/
class FormulaDbManager

{
 public:
  explicit FormulaDbManager();

  void SaveFormula(Formula* formula, bool formulaIsNew);

  Formula* GetFormulaWithName(const std::string& formulaName);

  std::vector<Formula*>& GetFormulaList() noexcept;

  void LoadDb();

  void RenameBakToMain();

  void DeleteFormula(const std::string& formulaName);

 private:
  void SaveDb();

  void SaveDbSingleFormula(const Formula* formula);

  void LoadDbSingleFormula(Formula& formula);

  void SaveDbOperand(FormulaOperand& op);

  void LoadDbOperand(FormulaOperand& op);

  OUContainer<Formula> ouAllFormulas;

  std::ifstream* loadFile;

  std::fstream* saveFile;
};
}  // namespace irsf

#endif  // FORMULADBMANAGER_H

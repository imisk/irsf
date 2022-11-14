#include "FormulaDbManager.h"
#include <QDir>
#include <QStandardPaths>
#include "BinaryReadWriteUtils.h"
namespace irsf {

FormulaDbManager::FormulaDbManager() {}

void FormulaDbManager::SaveFormula(Formula* formula, bool formulaIsNew) {
  if (formulaIsNew)
    ouAllFormulas.AddItem(*formula);

  SaveDb();
}

Formula* FormulaDbManager::GetFormulaWithName(const std::string& formulaName) {
  auto& db = ouAllFormulas.GetItemList();

  for (const auto& f : db) {
    if (f->name == formulaName) {
      return f;
    }
  }

  return nullptr;
}

std::vector<Formula*>& FormulaDbManager::GetFormulaList() noexcept {
  return ouAllFormulas.GetItemList();
}

void FormulaDbManager::SaveDb() {
  int32_t status = 0;

  auto vvvd = QDir::currentPath();
  std::cout << "currentPath = " << vvvd.toStdString() << std::endl;

  auto sPath =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  std::cout << "wPath = " << sPath.toStdString() << std::endl;

  status = rename("Formulas.idb", "Formulas_bak.idb");
  if (status != 0)
    std::cout << "Warning : could not rename file Formulas.idb to "
                 "Formulas_bak.idb \n";

  status = remove("Formulas.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file Formulas.idb \n";

  std::string fileName = "Formulas.idb";

  auto f = fstream_raii_write(fileName);
  saveFile = f.get();

  if (saveFile->is_open() == false)
    throw IrsfException(IrsfError::CannotOpenFile);

  // file version
  int32_t ver = kCurrentFormulaDbFileVersion;
  WriteBinary(*saveFile, &ver);

  //--- formula count
  size_t count = ouAllFormulas.GetItemList().size();
  WriteBinary(*saveFile, &count);

  // Save each one:
  auto& db = ouAllFormulas.GetItemList();
  for (size_t i = 0; i < db.size(); i++) {
    SaveDbSingleFormula(db[i]);
  }

  std::cout << "Formula database updated. \n";
}

void FormulaDbManager::LoadDb() {
  std::string fileName = "Formulas.idb";

  fstream_raii_read reading(fileName);
  loadFile = reading.get();

  if (loadFile->good() != true)
    throw IrsfException(IrsfError::FileNotFound);

  int32_t readFileVersion;
  ReadBinary(loadFile, &readFileVersion);

  size_t formulaCount;
  ReadBinary(loadFile, &formulaCount);

  std::cout << "Formula count = " << formulaCount << std::endl;

  ouAllFormulas.Clear();

  for (size_t i = 0; i < formulaCount; i++) {
    Formula f;
    LoadDbSingleFormula(f);

    ouAllFormulas.AddItem(f);
  }

  std::cout << "Finished loading formulas. \n";
}

void FormulaDbManager::RenameBakToMain() {
  int32_t status = 0;

  std::cout << "Renaming bak to main: Formulas.idb \n";

  status = remove("Formulas.idb");
  if (status != 0)
    std::cout << "Warning : could not delete file Formulas.idb \n";

  status = rename("Formulas_bak.idb", "Formulas.idb");
  if (status != 0)
    std::cout << "Warning : Could not rename file "
                 "Formulas_bak.idb to Formulas.idb \n";
}

void FormulaDbManager::DeleteFormula(const std::string& formulaName) {
  size_t i = 0;

  size_t deleteIndex = 0;
  bool found = false;
  bool finished = false;

  auto& db = ouAllFormulas.GetItemList();

  while (!finished) {
    if (db[i]->name == formulaName) {
      found = true;
      deleteIndex = i;
      finished = true;
    }
    ++i;
    if (i == db.size())
      finished = true;
  }

  if (found == true) {
    ouAllFormulas.EraseAtIndex(static_cast<std::streamsize>(deleteIndex));

    SaveDb();
  }
}

void FormulaDbManager::SaveDbSingleFormula(const Formula* formula) {
  Formula f = *formula;

  // Write the name of the formula

  size_t nameSize = f.name.size();
  WriteBinary(*saveFile, &nameSize);

  WriteBinaryCharArray(*saveFile, f.name.c_str(), f.name.size());

  // Operands in list - count
  size_t operandCount = f.operandsInList.size();
  WriteBinary(*saveFile, &operandCount);

  for (size_t i = 0; i < operandCount; i++) {
    SaveDbOperand(f.operandsInList[i]);
  }

  // currentFormulaInfix
  size_t curFormulaCount = f.currentFormulaInfix.size();
  WriteBinary(*saveFile, &curFormulaCount);

  for (size_t i = 0; i < curFormulaCount; i++) {
    bool isOp = f.currentFormulaInfix[i]->IsOperand();
    WriteBinary(*saveFile, &isOp);

    if (f.currentFormulaInfix[i]->IsOperand()) {
      FormulaOperand* sym =
          dynamic_cast<FormulaOperand*>(f.currentFormulaInfix[i].get());

      if (sym) {
        SaveDbOperand(*sym);
      } else {
        throw IrsfException(IrsfError::FormulaDbMemoryCorrupted);
      }

    } else {
      FormulaOperator* op =
          dynamic_cast<FormulaOperator*>(f.currentFormulaInfix[i].get());

      if (op) {
        OperatorId opId = op->GetOperatorId();
        WriteBinary(*saveFile, &opId);
      } else {
        throw IrsfException(IrsfError::FormulaDbMemoryCorrupted);
      }
    }
  }
}

void FormulaDbManager::LoadDbSingleFormula(Formula& formula) {
  size_t nameSize = 0;
  ReadBinary(loadFile, &nameSize);

  formula.name = std::string(nameSize, ' ');
  ReadBinaryCharArray(loadFile, &formula.name[0], nameSize);
  std::cout << "f.name = >" << formula.name << "<" << std::endl;

  size_t operandCount = 0;
  ReadBinary(loadFile, &operandCount);

  for (size_t i = 0; i < operandCount; i++) {
    FormulaOperand fop("", {});
    LoadDbOperand(fop);
    formula.operandsInList.push_back(fop);
  }

  size_t curFormulaCount = 0;
  ReadBinary(loadFile, &curFormulaCount);

  for (size_t i = 0; i < curFormulaCount; i++) {
    bool isOp = false;
    ReadBinary(loadFile, &isOp);

    if (isOp) {
      InputVariableDescriptor ivd = {};
      auto sym = std::make_unique<FormulaOperand>("", ivd);
      LoadDbOperand(*sym);
      formula.currentFormulaInfix.emplace_back(std::move(sym));
    } else {
      OperatorId opId;
      ReadBinary(loadFile, &opId);
      auto op = std::make_unique<FormulaOperator>(opId);
      formula.currentFormulaInfix.emplace_back(std::move(op));
    }
  }
}

void FormulaDbManager::SaveDbOperand(FormulaOperand& op) {
  // write op.symbol
  size_t symbolLen = op.symbol.size();
  WriteBinary(*saveFile, &symbolLen);

  WriteBinaryCharArray(*saveFile, op.symbol.c_str(), symbolLen);

  WriteBinary(*saveFile, &op.inputVariableDescriptor.variableId);

  WriteBinary(*saveFile, &op.inputVariableDescriptor.variableIdForProcessing);

  WriteBinary(*saveFile, &op.inputVariableDescriptor.parameterForProcessing);
}

void FormulaDbManager::LoadDbOperand(FormulaOperand& op) {
  size_t symbolLen = 0;
  ReadBinary(loadFile, &symbolLen);

  if (symbolLen > kMaxVariableAll)
    throw IrsfException(IrsfError::FormulaDatabaseCorrupted);

  op.symbol = std::string(symbolLen, ' ');
  ReadBinaryCharArray(loadFile, &op.symbol[0], symbolLen);

  ReadBinary(loadFile, &op.inputVariableDescriptor.variableId);
  ReadBinary(loadFile, &op.inputVariableDescriptor.variableIdForProcessing);
  ReadBinary(loadFile, &op.inputVariableDescriptor.parameterForProcessing);
}
}  // namespace irsf


#include "WindowLoadFormula.h"
#include "ErrorMessageBoxUtility.h"
#include "ui_WindowLoadFormula.h"

using namespace irsf;

WindowLoadFormula::WindowLoadFormula(QWidget* parent)
    : QDialog(parent), ui(new Ui::WindowLoadFormula) {
  ui->setupUi(this);
}

WindowLoadFormula::~WindowLoadFormula() {
  delete ui;
}

void WindowLoadFormula::RefreshFormulaList(std::vector<Formula*> list) {
  formulaList = list;

  std::cout << "RefreshFormulaList \n";
  ui->lb_Formulas->clear();

  for (size_t i = 0; i < list.size(); i++) {
    QString qs(list[i]->name.c_str());
    ui->lb_Formulas->addItem(qs);
  }
}

void WindowLoadFormula::SelectFirstFormula(
    std::vector<Formula*> list) noexcept {
  if (list.size() > 0) {
    selectedFormula = list[0];
  }
}

Formula* WindowLoadFormula::GetSelectedFormula() noexcept {
  return selectedFormula;
}

void WindowLoadFormula::on_btn_Load_clicked() {
  try {
    loadButtonClicked();

    this->hide();
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLoadFormula::on_btn_Cancel_clicked() {
  this->hide();
}

void WindowLoadFormula::on_lb_Formulas_currentTextChanged(
    const QString& currentText) {
  try {
    for (const auto& f : formulaList) {
      if (f->name == currentText.toStdString()) {
        selectedFormula = f;
        selectedFormulaChanged();
        break;
      }
    }
  } catch (IrsfException& err) {
    HandleErrorMessage(err);
  } catch (...) {
    HandleGeneralError();
  }
}

void WindowLoadFormula::on_btn_Delete_clicked() {
  deleteButtonClicked();
}

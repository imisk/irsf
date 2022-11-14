#ifndef WINDOWLOADFORMULA_H
#define WINDOWLOADFORMULA_H

#include <QDialog>
//#include "FormulaEditorManager.h"
#include <iostream>
#include "Formula.h"

namespace Ui {
class WindowLoadFormula;
}

class WindowLoadFormula final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowLoadFormula(QWidget* parent = nullptr);
  ~WindowLoadFormula() final;

  void RefreshFormulaList(std::vector<irsf::Formula*> list);

  void SelectFirstFormula(std::vector<irsf::Formula*> list) noexcept;

  irsf::Formula* GetSelectedFormula() noexcept;

 signals:

  void loadButtonClicked();
  void selectedFormulaChanged();
  void deleteButtonClicked();

 private slots:
  void on_btn_Load_clicked();

  void on_btn_Cancel_clicked();

  void on_lb_Formulas_currentTextChanged(const QString& currentText);

  void on_btn_Delete_clicked();

 private:
  Ui::WindowLoadFormula* ui;

  irsf::Formula* selectedFormula{nullptr};

  std::vector<irsf::Formula*> formulaList;
};

#endif  // WINDOWLOADFORMULA_H

#ifndef WINDOWFORMULAEDITOR_H
#define WINDOWFORMULAEDITOR_H

#include <QDialog>
#include <vector>
#include "FormulaEditorManager.h"
#include "WindowAddOperand.h"
#include "WindowLoadFormula.h"

namespace Ui {
class WindowFormulaEditor;
}

class WindowFormulaEditor final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowFormulaEditor(irsf::FormulaDbManager* fdm,
                               QWidget* parent = nullptr);
  ~WindowFormulaEditor() final;

  void Init();

 public slots:

  void slotRefreshLB();

  void slotRefreshWindow();

  /*
   * Delete currentFormula from database.
   */
  void slotDeleteFormula();

 private slots:

  void on_btn_AddValueToList_clicked();

  void on_btn_ClearFormula_clicked();

  void on_lb_Variables_currentTextChanged(const QString& currentText);

  void on_btn_AddPlus_clicked();

  void on_btn_AddOperand_clicked();

  void on_btn_AddMinus_clicked();

  void on_btn_AddMultiply_clicked();

  void on_btn_AddDivide_clicked();

  void on_btn_AddOpenBracket_clicked();

  void on_btn_AddCloseBracket_clicked();

  void on_btn_AddAbs_clicked();

  void on_btn_Evaluate_clicked();

  void on_btn_SaveFormula_clicked();

  void on_btn_LoadFormula_clicked();

 private:
  Ui::WindowFormulaEditor* ui;

  std::unique_ptr<WindowAddOperand> windowAddOperand;

  std::unique_ptr<irsf::FormulaEditorManager> mngr;

  std::unique_ptr<WindowLoadFormula> windowLoadFormula;
};

#endif  // WINDOWFORMULAEDITOR_H

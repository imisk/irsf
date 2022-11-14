#ifndef WINDOWADDOPERAND_H
#define WINDOWADDOPERAND_H

#include <QDialog>
#include <string>
#include <vector>
#include "FormulaEditorManager.h"

namespace Ui {
class WindowAddOperand;
}

class WindowAddOperand final : public QDialog {
  Q_OBJECT

 public:
  explicit WindowAddOperand(irsf::FormulaEditorManager* manager,
                            QWidget* parent = nullptr);
  ~WindowAddOperand() final;

 signals:

  void addButtonClicked();

 private slots:
  void on_btn_AddToVariableList_clicked();

 private:
  Ui::WindowAddOperand* ui;

  irsf::FormulaEditorManager* mngr;
};

#endif  // WINDOWADDOPERAND_H

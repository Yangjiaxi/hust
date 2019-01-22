#ifndef LABELSDIALOG_H
#define LABELSDIALOG_H

#include <QDialog>
#include "itemdatalist.h"

namespace Ui {
  class LabelsDialog;
}

class LabelsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit LabelsDialog(QWidget *parent = 0);
  ~LabelsDialog();

  void preSetLabels(ItemDataList* currentList);
  void getModLabels(ItemDataList *currentList);

private:
  Ui::LabelsDialog *ui;
};

#endif // LABELSDIALOG_H

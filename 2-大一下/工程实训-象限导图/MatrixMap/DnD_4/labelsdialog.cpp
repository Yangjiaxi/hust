#include "labelsdialog.h"
#include "ui_labelsdialog.h"

LabelsDialog::LabelsDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::LabelsDialog)
{
  ui->setupUi(this);
}

LabelsDialog::~LabelsDialog()
{
  delete ui;
}

void LabelsDialog::preSetLabels(ItemDataList *currentList)
{
  ui->txtXRight->setText(currentList->labelXRight);
  ui->txtXLeft->setText(currentList->labelXLeft);
  ui->txtYUp->setText(currentList->labelYUp);
  ui->txtYDown->setText(currentList->labelYDown);
}

void LabelsDialog::getModLabels(ItemDataList *currentList)
{
  currentList->labelXRight = ui->txtXRight->text();
  currentList->labelXLeft  = ui->txtXLeft->text();
  currentList->labelYUp    = ui->txtYUp->text();
  currentList->labelYDown  = ui->txtYDown->text();
}


#include "datedialog.h"
#include "ui_datedialog.h"
#include <QDebug>
#include <QDate>

DateDialog::DateDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DateDialog)
{
  ui->setupUi(this);
}

DateDialog::~DateDialog()
{
  qDebug() << "Date Dialog will be Deleted!";
  delete ui;
}

void DateDialog::setDate()
{
  ui->dateFrom->setDate(QDate::currentDate());
  ui->dateTo->setDate(QDate::currentDate());
}

QString DateDialog::getDate()
{
  QString strFrom = ui->dateFrom->date().toString("MM/dd");
  QString strTo = ui->dateTo->date().toString("MM/dd");
  QString dateResult = strFrom + '-' + strTo;
  return dateResult;
}

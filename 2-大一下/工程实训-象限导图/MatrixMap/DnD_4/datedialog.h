#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>

namespace Ui {
  class DateDialog;
}

class DateDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DateDialog(QWidget *parent = 0);
  ~DateDialog();

  void setDate();
  QString getDate();

private:
  Ui::DateDialog *ui;
};

#endif // DATEDIALOG_H

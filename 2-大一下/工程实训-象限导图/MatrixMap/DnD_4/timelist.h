#ifndef TIMELIST_H
#define TIMELIST_H

#include <QListWidget>
#include "fourlist.h"

class TimeList : public QListWidget
{
  Q_OBJECT
public:
  TimeList(QWidget *parent = nullptr);
  ~TimeList();
  FourList* timeListAdd(QString date);
  void timeListDel(int index);
  void timeListMod(int index, QString newDate);

  int getCurrentCount(); //获取当前在List内的item数量
  int timeItemCount; //总计数

  QVector<QString> nameList;
  QVector<FourList*> listList;
};

#endif // TIMELIST_H

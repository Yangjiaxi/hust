#include "timelist.h"
#include <QDebug>


TimeList::TimeList(QWidget *parent) :
  QListWidget(parent)
{
  timeItemCount = 0;
  nameList.clear();
  listList.clear();
  qDebug() << "Time List inited!";
}

TimeList::~TimeList()
{
  foreach(auto e, listList)
  {
    delete e;
  }
  qDebug() << "Time List Destroyed!";
}

FourList *TimeList::timeListAdd(QString date)
{
  qDebug() << "New Time List Item [Add] Requested!";
  FourList *aList = new FourList();
  QString name = date.trimmed();
  timeItemCount++;
  nameList.append(name);
  listList.append(aList);
  QListWidgetItem *aItem = new QListWidgetItem(name);
  addItem(aItem);
  return aList;
}

void TimeList::timeListDel(int index)
{
  qDebug() << "[IN] timeListDel";
  qDebug() << "Asking for delete in Time List!";
  qDebug() << "[timeList.cpp] Delete at :" << index;
  qDebug() << "Delete Name is : " << nameList.at(index);
  nameList.erase(nameList.begin() + index);
  delete listList.at(index);
  listList.erase(listList.begin() + index);
  qDebug() << "Time List Item Delete Complete!";
  qDebug() << "After Delete: "
           << getCurrentCount();
  qDebug() << "[OUT] timeListDel";
}

void TimeList::timeListMod(int index, QString newDate)
{
  nameList[index] = newDate;
}

int TimeList::getCurrentCount()
{
  int countA = nameList.count();
  int countB = listList.count();
  if (countA == countB)
  {
    return countA;
  }
  else
  {
    qDebug() << "[Fatal Error!] nameList.count() is not equal to listList.count()!!!"
             << countA << " : " << countB;
    exit(1);
  }
}






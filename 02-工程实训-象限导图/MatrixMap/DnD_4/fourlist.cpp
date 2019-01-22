#include "fourlist.h"
#include <QDebug>


FourList::FourList(QWidget *parent):
  QListWidget(parent)
{
  fourItemCount = 0;
  nameList.clear();
  listList.clear();
  qDebug() << "Four List inited!";
}

FourList::~FourList()
{
  foreach(auto e, listList)
  {
    delete e;
  }
  qDebug() << "Four List Destroyed!";
}

ItemDataList *FourList::fourListAdd(QString name)
{
  ItemDataList *aList = new ItemDataList();
  fourItemCount++; //总计数+1
  nameList.append(name);
  listList.append(aList);
  // setCurrentItem(aItem);  /// Problem Occurs HERE
  //qDebug() << "New List Init! Now should change the panel!";
  qDebug() << nameList;
  qDebug() << "******";
  qDebug() << listList;
  return aList;
}

void FourList::fourListDel(int index)
{
  //qDebug() << "Delete at Row : " << index;
  //qDebug() << "Delete Name is : " << nameList.at(index);
  nameList.erase(nameList.begin() + index);
  //qDebug() << "Name List Delete Complete!";
  delete listList.at(index);
  //qDebug() << "List List Data Delete Complete!";
  listList.erase(listList.begin() + index);
  //qDebug() << "List Item Delete Complete!";
  // qDebug() << "After Delete: " << listList.count() << "exist";
}

void FourList::fourListMod(int index, QString newName)
{
  nameList[index] = newName;
}

int FourList::getCurrentCount()
{
  int countA = nameList.count();
  int countB = listList.count();
  if(countA == countB)
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

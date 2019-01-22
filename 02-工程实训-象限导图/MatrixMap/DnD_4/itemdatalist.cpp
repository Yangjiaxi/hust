#include "itemdatalist.h"
#include "itemdata.h"
#include <QDebug>

ItemDataList::ItemDataList()
{
  itemList.empty();
  itemCount = 0;
  qDebug() << "List Init Complete!";
  labelXRight = QString("重要");
  labelXLeft = QString("不重要");
  labelYUp = QString("紧急");
  labelYDown = QString("不紧急");
  labelIndex = 0;
}

ItemDataList::~ItemDataList()
{
  for(auto e : itemList)
    delete e;
  qDebug() << "List Deleted!";
}

int ItemDataList::itemListAdd(QString _value, int _place)
{
  // qDebug() << "New item" << _value << _place;
  int index = itemCount;
  itemCount++;  //主键，记录总共被添加的数据数量
  ItemData *aItem = new ItemData(_value, _place);
  itemList[index] = aItem;
  return index;
}

void ItemDataList::itemListDel(int index)
{
  auto iter = itemList.find(index);
  // qDebug() << itemList;
  itemList.erase(iter);
  // qDebug() << itemList;
}

void ItemDataList::itemListModPlace(int index, int _place)
{
  // qDebug() << "New Place Received : " << _place;
  itemList[index]->setPlace(_place);
}

void ItemDataList::itemListModValue(int index, QString _value)
{
  // qDebug() << "New Value Received : " << _value;
  itemList[index]->setValue(_value);
}

void ItemDataList::showAll()
{
  qDebug() << "*****BEGIN*******";
  qDebug() << "Key" << "\t"
           << "Place" << "\t"
           << "Value";
  for(auto i = itemList.constBegin(); i != itemList.constEnd(); ++i)
  {
    qDebug() << i.key() << "\t"
             << i.value()->getPlace() << "\t"
             << i.value()->getValue();
  }
  qDebug() << "*****END*********";
}

void ItemDataList::on_itemPlaceChanged(int index)
{
  QString targetName = sender()->property("objectName").toString();
  qDebug() << "ItemList receive signal : at " << index;
  qDebug() << "Receiver: " << targetName;

  showAll();

  qDebug() << "Before At: " << itemList.value(index)->getPlace();
  int targetPlace = targetName[targetName.count() - 1].toLatin1() - '0';
  if(!(targetPlace <= 4 && targetPlace >=1))
  {
    targetPlace = 0;
  }
  qDebug() << "After At: " << targetPlace;
  itemListModPlace(index, targetPlace);
}

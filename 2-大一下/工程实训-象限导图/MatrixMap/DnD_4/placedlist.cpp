#include "placedlist.h"
#include <QDebug>


PlacedList::PlacedList(QWidget *parent) :
  QListWidget(parent)
{
}

void PlacedList::on_itemDel(int index)
{
  // qDebug() << "Item Del! At: " << index;
  int indexItem = indexList.indexOf(index);
  QListWidgetItem *item = this->item(indexItem);
  if(item)
  {
    this->indexList.erase(this->indexList.begin() + indexItem);
    this->removeItemWidget(item);
    delete item;
  }
}

void PlacedList::on_itemMod(QString value, int index)
{
  //qDebug() << "Placed List Item Modify: " << value << index;
  int indexItem = indexList.indexOf(index);
  //qDebug() << indexItem;
  // qDebug() << indexList;
  // qDebug() << this->item(indexItem)->text();
  this->item(indexItem)->setText(value);
}

void PlacedList::on_itemFlow(QString value, int dir, int index)
{
  // qDebug() << index << value;
  // qDebug() << "Data Received!";
  // qDebug() << value << "+" << dir;
  if(dir)
  {
    indexList.append(index);
    // qDebug() << "Add to Placed List!";
    this->addItem(value);
  }
  else
  {
    // qDebug() << "Delete in Placed List!";
    // qDebug() << indexList.indexOf(index);
    int keyIndex = indexList.indexOf(index);
    QListWidgetItem *item = this->findItems(value, Qt::MatchExactly).at(0);
    if(item)
    {
      this->removeItemWidget(item);
      delete item;
      indexList.erase(indexList.begin() + keyIndex);
      // qDebug() << indexList;
    }
  }
}


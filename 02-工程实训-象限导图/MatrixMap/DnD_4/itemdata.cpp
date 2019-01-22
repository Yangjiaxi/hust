#include "itemdata.h"
#include <QDebug>


ItemData::ItemData(QString _value, int _place) :
  value(_value), currentPlace(_place)
{
  qDebug() << "new item!" << this->value << this->currentPlace;
}

ItemData::~ItemData()
{
  qDebug() << "Item Deleted!";
}

QString ItemData::getValue() const
{
  return value;
}

int ItemData::getPlace() const
{
  return this->currentPlace;
}

void ItemData::setValue(QString data)
{
  this->value = data;
  qDebug() << "New Value!";
}

void ItemData::setPlace(int data)
{
  qDebug() << "Before At : " << this->currentPlace;
  this->currentPlace = data;
  qDebug() << "New Place!";
}




#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <QObject>

class ItemData : public QObject
{
  Q_OBJECT
private:
  QString value; //数据
  int currentPlace;  //当前位置 0 1 2 3 4

public:
  ItemData(QString _value, int _place);
  ~ItemData();
  QString getValue() const;
  int getPlace() const;
  void setValue(QString data);
  void setPlace(int data);
};

#endif // ITEMDATA_H


/*
 * 1. 在界面上进行修改，获得修改后的QString和int
 * 2. 利用它的"index"属性(人为添加)，传递参数请求底层数据修改
 * 3. 底层数据修改
 * 4. Deploy到listPlaced上
 *
 * 行为列表:
 * 1. 在listFree里修改->请求修改底层
 * 2. 在listD{}里修改->请求修改底层->Deploy到listPlaced上
 * 3. 拖动->请求修改底层
 * 4. 在listFree里添加一项->请求向底层添加数据
 *
*/

















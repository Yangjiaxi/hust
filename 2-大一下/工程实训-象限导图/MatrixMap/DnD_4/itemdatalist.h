#ifndef ITEMDATALIST_H
#define ITEMDATALIST_H

#include <QObject>
#include <QMap>
#include "itemdata.h"


//全表，最底层的表
class ItemDataList : public QObject
{
  Q_OBJECT
  //private:
  // <PriorKey::int, Data::ItemData>
  // PriorKey:主键，指元素是第几个被加入到表中的，创建后就固定下来
  // Data:条目对象
  // 条目对象间不会相互影响


public:
  ItemDataList();
  ~ItemDataList();
  int itemListAdd(QString _value, int _place); //在内部获得并返回元素的主键
  void itemListDel(int index);
  void itemListModPlace(int index, int _place);
  void itemListModValue(int index, QString _value);
  void showAll();

  int itemCount;
  QMap<int, ItemData* > itemList;

  int labelIndex;
  QString labelXRight;
  QString labelXLeft;
  QString labelYUp;
  QString labelYDown;

private slots:
  void on_itemPlaceChanged(int index);
};

#endif // ITEMDATALIST_H


/*对于表的操作
 * 1. 添加条目->获得元素的主键->申请新的条目->执行insert
 * 2. 删除条目->根据元素的主键删除对象
 * 3. 修改条目->根据元素的主键->申请修改条目内容
 */



















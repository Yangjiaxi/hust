#ifndef FOURLIST_H
#define FOURLIST_H

#include <QListWidget>
#include <itemdatalist.h>


/*
 * 表FourList类
 * 保存所有的itemDataList
 * 在左边的QListWidget
 * 在使用的时候会根据用户选择的一项，
 * 挂载到Widget的*itemList指针上去
 */
class FourList : public QListWidget
{
  Q_OBJECT
public:
  FourList(QWidget *parent = nullptr);
  ~FourList();
  ItemDataList* fourListAdd(QString name); //添加一个itemDataList
  void fourListDel(int index); //删除
  void fourListMod(int index, QString newName); //修改名字
  int getCurrentCount();
  int fourItemCount; //总计数
  //双击一个条目，切换到这个条目对应的四象限图

  QVector<QString> nameList; //保存list的名称
  QVector<ItemDataList*> listList;  //保存指向list的指针

private:

};

#endif // FOURLIST_H

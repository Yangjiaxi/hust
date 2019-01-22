#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "draggablelist.h"
#include "itemdatalist.h"
#include "fourlist.h"

namespace Ui {
  class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();
  void addToList(QString value);
  void deployContent();
  void clearAllList();
  void connectAll();
  void disconnectAll();
  void deployFourList();

  QString getNewDate();
  void labelsMod();
  void deployLabels();
  QString strMod(QString&);
  void init();
  void addLabels(const char *cxRight,
                 const char *cxLeft,
                 const char *cyUp,
                 const char *cyDown);

  void addDetail(const char *cstr);
  bool saveDateAsStream(QString& fileName);
  bool openDataAsStream(QString& fileName);
  void clearAll(); //清空所有组件以打开存档

private slots:
  void on_btnAddItem_clicked();
  void on_txtAddItem_returnPressed();

  void on_listFree_itemDoubleClicked(QListWidgetItem *item);
  void on_listD1_itemDoubleClicked(QListWidgetItem *item);
  void on_listD2_itemDoubleClicked(QListWidgetItem *item);
  void on_listD3_itemDoubleClicked(QListWidgetItem *item);
  void on_listD4_itemDoubleClicked(QListWidgetItem *item);

  void on_listFree_customContextMenuRequested(const QPoint &pos);
  void on_listD1_customContextMenuRequested(const QPoint &pos);
  void on_listD2_customContextMenuRequested(const QPoint &pos);
  void on_listD3_customContextMenuRequested(const QPoint &pos);
  void on_listD4_customContextMenuRequested(const QPoint &pos);

  void on_actListFreeDel_triggered();
  void on_actListD1Del_triggered();
  void on_actListD2Del_triggered();
  void on_actListD3Del_triggered();
  void on_actListD4Del_triggered();

  void on_listFree_itemChanged(QListWidgetItem *item);
  void on_listD1_itemChanged(QListWidgetItem *item);
  void on_listD2_itemChanged(QListWidgetItem *item);
  void on_listD3_itemChanged(QListWidgetItem *item);
  void on_listD4_itemChanged(QListWidgetItem *item);

  void on_btnAddFour_clicked();
  void on_listFour_currentRowChanged(int currentRow);
  void on_listFour_itemDoubleClicked(QListWidgetItem *item);
  void on_listFour_itemChanged(QListWidgetItem *item);
  void on_btnDelFour_clicked();

  void on_btnAddTime_clicked();
  void on_listTime_currentRowChanged(int currentRow);
  void on_listTime_itemDoubleClicked(QListWidgetItem *item);
  void on_listTime_customContextMenuRequested(const QPoint &pos);
  void on_actListTimeDel_triggered();

  void on_btnXLeft_clicked();
  void on_btnXRight_clicked();
  void on_btnYUp_clicked();
  void on_btnYDown_clicked();

  void on_listLabel_currentRowChanged(int currentRow);

  void on_btnSave_clicked();
  void on_btnImport_clicked();

private:
  Ui::Widget *ui;
  void callContextMenu(const QPoint &pos, DraggableList* listCaller);
  FourList *fourList; //当前四象限图的列表对应的时间点，当timeList的currentRow被改变时，重新挂载
  ItemDataList *itemList; // 当前四象限图对应的底层数据，当fourList的currentRow被改变时，重新挂载
  QMap<int, DraggableList*> listMap; //用于快速定位 0->free 1->D1 2->D2 ...
  QVector<QVector<QString>> labelsSet; //保存预设的四个标签
  QVector<QString> detailSet; //保存标签的描述
};

#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"
#include "placedlist.h"
#include "itemdata.h"
#include "itemdatalist.h"
#include "datedialog.h"
#include "labelsdialog.h"
#include <QDebug>
#include <QPoint>
#include <QMenu>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDateEdit>
#include <QFile>
#include <QFileDialog>
#include <QDir>

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  setFixedSize(1400, 840);
  setWindowTitle("象限导图");
  setWindowIcon(QIcon(":/images/swot.ico"));

  init();
}

Widget::~Widget()
{
  delete ui;
}

void Widget::init()
{
  listMap[0] = ui->listFree;
  listMap[1] = ui->listD1;
  listMap[2] = ui->listD2;
  listMap[3] = ui->listD3;
  listMap[4] = ui->listD4;

  // addLabels("", "", "", "");
  // addDetail("");
  addLabels("重要", "不重要", "紧急", "不紧急");
  addDetail("重要紧急四象限：分好优先级，遇事不焦虑");

  addLabels("可能性大", "可能性小", "损失小", "损失大");
  addDetail("风险管理模型：风险分清楚，应对不糊涂");

  addLabels("优势", "劣势", "机会", "威胁");
  addDetail("swot分析：优势放杠杆，劣势求逆转");

  addLabels("数量多", "数量少", "交货期长", "交货期短");
  addDetail("订单数量-货期模型：资源配置佳，效益最大化");

  addLabels("实力强", "实力弱", "吸引力强", "吸引力弱");
  addDetail("通用电气矩阵：优势谋竞争，劣势比吸引");

  addLabels("有意愿", "无意愿", "有能力", "没能力");
  addDetail("情景管理模型：员工不相同，管理得变通");

  addLabels("于己有利", "于己无利", "于人有利", "于人无利");
  addDetail("互利矩阵：利己又利他，选它准不差");

  addLabels("占有率高", "占有率低", "增长率高", "增长率低");
  addDetail("波士顿矩阵：存量与增量，取舍不妄想");

  QString now = QDate::currentDate().toString("MM/dd");
  fourList = ui->listTime->timeListAdd(now + '-' + now);
  QString name = QString("新的四象限图%1").arg(fourList->fourItemCount + 1);
  itemList = fourList->fourListAdd(name);
  ui->listLabel->setCurrentRow(0);
  addToList(tr("新的条目"));
  ui->listTime->setCurrentRow(0);
}

void Widget::addLabels(const char *cxRight,
                       const char *cxLeft,
                       const char *cyUp,
                       const char *cyDown)
{
  QString xRight = tr(cxRight);
  QString xLeft = tr(cxLeft);
  QString yUp = tr(cyUp);
  QString yDown = tr(cyDown);
  QVector<QString> item;
  item.append(xRight);
  item.append(xLeft);
  item.append(yUp);
  item.append(yDown);
  labelsSet.append(item);
}

void Widget::addDetail(const char *cstr)
{
  QString str = tr(cstr);
  detailSet.append(str);
  ui->listLabel->addItem(str);
}

void Widget::connectAll()
{
  qDebug() << "[IN] connectAll";
  if(itemList != nullptr)
  {
    qDebug() << "Start Connect!";
    connect(ui->listFree, SIGNAL(itemFlow(QString, int, int)),
            ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    connect(ui->listD1, SIGNAL(itemFlow(QString, int, int)),
            ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    connect(ui->listD2, SIGNAL(itemFlow(QString, int, int)),
            ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    connect(ui->listD3, SIGNAL(itemFlow(QString, int, int)),
            ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    connect(ui->listD4, SIGNAL(itemFlow(QString, int, int)),
            ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));

    connect(ui->listFree, SIGNAL(itemPlaceChanged(int)),
            itemList, SLOT(on_itemPlaceChanged(int)));
    connect(ui->listD1, SIGNAL(itemPlaceChanged(int)),
            itemList, SLOT(on_itemPlaceChanged(int)));
    connect(ui->listD2, SIGNAL(itemPlaceChanged(int)),
            itemList, SLOT(on_itemPlaceChanged(int)));
    connect(ui->listD3, SIGNAL(itemPlaceChanged(int)),
            itemList, SLOT(on_itemPlaceChanged(int)));
    connect(ui->listD4, SIGNAL(itemPlaceChanged(int)),
            itemList, SLOT(on_itemPlaceChanged(int)));
    qDebug() <<  "Connect Complete!";
  }
  // qDebug () << ui->listFour->currentItem()->text();
  qDebug() << "[OUT] connectAll";
}

void Widget::disconnectAll()
{
  qDebug() << "[IN] disconnectAll";
  if(itemList != nullptr)
  {
    qDebug() << "Start Disconnect!!";
    disconnect(ui->listFree, SIGNAL(itemFlow(QString, int, int)),
               ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    disconnect(ui->listD1, SIGNAL(itemFlow(QString, int, int)),
               ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    disconnect(ui->listD2, SIGNAL(itemFlow(QString, int, int)),
               ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    disconnect(ui->listD3, SIGNAL(itemFlow(QString, int, int)),
               ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));
    disconnect(ui->listD4, SIGNAL(itemFlow(QString, int, int)),
               ui->listPlaced, SLOT(on_itemFlow(QString, int, int)));

    // qDebug() << "Ready to disconnect itemList: here's inside:" << itemList->itemCount;
    // itemList->showAll();

    qDebug() << "Part.2";
    // itemList->showAll();
    disconnect(ui->listFree, SIGNAL(itemPlaceChanged(int)), itemList, SLOT(on_itemPlaceChanged(int)));
    disconnect(ui->listD1, SIGNAL(itemPlaceChanged(int)), itemList, SLOT(on_itemPlaceChanged(int)));
    disconnect(ui->listD2, SIGNAL(itemPlaceChanged(int)), itemList, SLOT(on_itemPlaceChanged(int)));
    disconnect(ui->listD3, SIGNAL(itemPlaceChanged(int)), itemList, SLOT(on_itemPlaceChanged(int)));
    disconnect(ui->listD4, SIGNAL(itemPlaceChanged(int)), itemList, SLOT(on_itemPlaceChanged(int)));

    qDebug() <<  "Disconnect Complete!";
  }
  else
  {
    qDebug() << "nullptr, failed";
  }
  itemList = nullptr;
  qDebug() << "[OUT] disconnectAll";
}

void Widget::addToList(QString value)
{
  ui->listFree->addItem(value);
  int index = itemList->itemListAdd(value, 0);
  ui->listFree->indexList.append(index);
}


void Widget::on_btnAddItem_clicked()
{
  QString value = ui->txtAddItem->text();
  QString s_value = value.trimmed();
  if(!s_value.isEmpty())
  {
    addToList(s_value);
    ui->txtAddItem->clear();
  }
  else
    qDebug() << "Denied! Empty String is Received!";
}


void Widget::on_listFree_itemDoubleClicked(QListWidgetItem *item)
{
  item->setFlags(item->flags() | Qt::ItemIsEditable);
  ui->listFree->editItem(item);
}

void Widget::on_listD1_itemDoubleClicked(QListWidgetItem *item)
{
  item->setFlags(item->flags() | Qt::ItemIsEditable);
  ui->listD1->editItem(item);
}

void Widget::on_listD2_itemDoubleClicked(QListWidgetItem *item)
{
  item->setFlags(item->flags() | Qt::ItemIsEditable);
  ui->listD2->editItem(item);
}
void Widget::on_listD3_itemDoubleClicked(QListWidgetItem *item)
{
  item->setFlags(item->flags() | Qt::ItemIsEditable);
  ui->listD3->editItem(item);
}
void Widget::on_listD4_itemDoubleClicked(QListWidgetItem *item)
{
  item->setFlags(item->flags() | Qt::ItemIsEditable);
  ui->listD4->editItem(item);
}

void Widget::on_actListFreeDel_triggered()
{
  int row = ui->listFree->currentRow();
  QListWidgetItem *aItem = ui->listFree->takeItem(row);
  delete aItem;
  int indexKey = ui->listFree->indexList.at(row);
  ui->listFree->indexList.erase(ui->listFree->indexList.begin() + row);
  itemList->itemListDel(indexKey);
}

void Widget::on_actListD1Del_triggered()
{
  int row = ui->listD1->currentRow();
  QListWidgetItem *aItem = ui->listD1->takeItem(row);
  delete aItem;
  int indexKey = ui->listD1->indexList.at(row);
  // qDebug() << "Delete at D1, row: " << row << "key : " << indexKey;
  ui->listD1->indexList.erase(ui->listD1->indexList.begin() + row);
  itemList->itemListDel(indexKey);
  ui->listPlaced->on_itemDel(indexKey);
}

void Widget::on_actListD2Del_triggered()
{
  int row = ui->listD2->currentRow();
  QListWidgetItem *aItem = ui->listD2->takeItem(row);
  delete aItem;
  int indexKey = ui->listD2->indexList.at(row);
  ui->listD2->indexList.erase(ui->listD2->indexList.begin() + row);
  itemList->itemListDel(indexKey);
  ui->listPlaced->on_itemDel(indexKey);
}

void Widget::on_actListD3Del_triggered()
{
  int row = ui->listD3->currentRow();
  QListWidgetItem *aItem = ui->listD3->takeItem(row);
  delete aItem;
  int indexKey = ui->listD3->indexList.at(row);
  ui->listD3->indexList.erase(ui->listD3->indexList.begin() + row);
  itemList->itemListDel(indexKey);
  ui->listPlaced->on_itemDel(indexKey);
}

void Widget::on_actListD4Del_triggered()
{
  int row = ui->listD4->currentRow();
  QListWidgetItem *aItem = ui->listD4->takeItem(row);
  delete aItem;
  int indexKey = ui->listD4->indexList.at(row);
  ui->listD4->indexList.erase(ui->listD4->indexList.begin() + row);
  itemList->itemListDel(indexKey);
  ui->listPlaced->on_itemDel(indexKey);
}


void Widget::on_listFree_customContextMenuRequested(const QPoint &pos)
{
  // qDebug() << sender()->property("objectName");
  DraggableList *listCaller = qobject_cast<DraggableList *>(sender());
  Widget::callContextMenu(pos, listCaller);
}

void Widget::on_listD1_customContextMenuRequested(const QPoint &pos)
{
  // qDebug() << sender()->property("objectName");
  DraggableList *listCaller = qobject_cast<DraggableList *>(sender());
  Widget::callContextMenu(pos, listCaller);
}

void Widget::on_listD2_customContextMenuRequested(const QPoint &pos)
{
  // qDebug() << sender()->property("objectName");
  DraggableList *listCaller = qobject_cast<DraggableList *>(sender());
  Widget::callContextMenu(pos, listCaller);
}

void Widget::on_listD3_customContextMenuRequested(const QPoint &pos)
{
  // qDebug() << sender()->property("objectName");
  DraggableList *listCaller = qobject_cast<DraggableList *>(sender());
  Widget::callContextMenu(pos, listCaller);
}

void Widget::on_listD4_customContextMenuRequested(const QPoint &pos)
{
  // qDebug() << sender()->property("objectName");
  DraggableList *listCaller = qobject_cast<DraggableList *>(sender());
  Widget::callContextMenu(pos, listCaller);
}

void Widget::callContextMenu(const QPoint &pos, DraggableList* listCaller)
{
  Q_UNUSED(pos);
  // qDebug() << pos;
  // qDebug() << listCaller->property("objectName");
  QString targetName = listCaller->property("objectName").toString();
  QMenu *menuList = new QMenu(this);

  if(!targetName.compare("listFree"))
    menuList->addAction(ui->actListFreeDel);
  else if(!targetName.compare("listD1"))
    menuList->addAction(ui->actListD1Del);
  else if(!targetName.compare("listD2"))
    menuList->addAction(ui->actListD2Del);
  else if(!targetName.compare("listD3"))
    menuList->addAction(ui->actListD3Del);
  else if(!targetName.compare("listD4"))
    menuList->addAction(ui->actListD4Del);

  menuList->exec(QCursor::pos());
  delete menuList;
}

void Widget::on_listFree_itemChanged(QListWidgetItem *item)
{
  int indexRow = ui->listFree->currentRow();
  int indexKey = ui->listFree->indexList.at(indexRow);
  QString value = item->text();
  //qDebug() << "At Row" << indexRow;
  // qDebug() << ui->listFree->indexList;
  //qDebug() << "Change to " << value;
  //qDebug() << "At Key Index : " << indexKey;
  //qDebug() << "Before: " << itemList->itemList.value(indexKey)->getValue();
  itemList->itemListModValue(indexKey, value);
  // qDebug() << itemList->itemList[ui->listFree->currentRow()]->text();
  //itemList->showAll();
}

void Widget::on_listD1_itemChanged(QListWidgetItem *item)
{
  //qDebug() << "D1";
  int indexRow = ui->listD1->currentRow();
  int indexKey = ui->listD1->indexList.at(indexRow);
  QString value = item->text();
  itemList->itemListModValue(indexKey, value);
  // qDebug() << "Key is : " << indexKey;
  // qDebug() << ui->listPlaced->
  // qDebug() << ui->listPlaced->item(indexKey)->text();
  //itemList->showAll();
  ui->listPlaced->on_itemMod(value, indexKey);
}

void Widget::on_listD2_itemChanged(QListWidgetItem *item)
{
  //qDebug() << "D2";
  int indexRow = ui->listD2->currentRow();
  int indexKey = ui->listD2->indexList.at(indexRow);
  QString value = item->text();
  itemList->itemListModValue(indexKey, value);
  //itemList->showAll();
  ui->listPlaced->on_itemMod(value, indexKey);
}

void Widget::on_listD3_itemChanged(QListWidgetItem *item)
{
  //qDebug() << "D3";
  int indexRow = ui->listD3->currentRow();
  int indexKey = ui->listD3->indexList.at(indexRow);
  QString value = item->text();
  itemList->itemListModValue(indexKey, value);
  //itemList->showAll();
  ui->listPlaced->on_itemMod(value, indexKey);
}

void Widget::on_listD4_itemChanged(QListWidgetItem *item)
{
  //qDebug() << "D4";
  int indexRow = ui->listD4->currentRow();
  int indexKey = ui->listD4->indexList.at(indexRow);
  QString value = item->text();
  itemList->itemListModValue(indexKey, value);
  //itemList->showAll();
  ui->listPlaced->on_itemMod(value, indexKey);
}

void Widget::on_txtAddItem_returnPressed()
{
  on_btnAddItem_clicked();
}

void Widget::on_btnAddFour_clicked()
{
  //qDebug() << "At on_btnAddFour_clicked";
  //qDebug() << "Add Four List!";
  qDebug() << "#Disconnect# at [on_btnAddFour_clicked]";
  disconnectAll();
  QString name = QString("新的四象限图%1").arg(fourList->fourItemCount + 1);
  itemList = fourList->fourListAdd(name);
  QListWidgetItem *aItem = new QListWidgetItem(name);
  ui->listFour->addItem(aItem);
  // qDebug() << "Set current row : " << ui->listFour->getCurrentCount() - 1;
  ui->listFour->setCurrentRow(fourList->getCurrentCount() - 1);
  clearAllList();  //清空所有列表
  addToList(tr("新的条目"));
  //qDebug() << "Out At on_btnAddFour_clicked";
}

void Widget::deployContent()
{
  //qDebug() << "ReDeploy Start!";
  clearAllList();
  for(auto i = itemList->itemList.constBegin();
      i != itemList->itemList.constEnd(); ++i)
  {
    listMap[i.value()->getPlace()]->addItem(i.value()->getValue());
    listMap[i.value()->getPlace()]->indexList.append(i.key());
    if(i.value()->getPlace() != 0)
    {
      ui->listPlaced->addItem(i.value()->getValue());
      ui->listPlaced->indexList.append(i.key());
    }
  }
  deployLabels();
}

void Widget::clearAllList()
{
  ui->listFree->clear();
  ui->listFree->indexList.clear();
  ui->listPlaced->clear();
  ui->listPlaced->indexList.clear();
  ui->listD1->clear();
  ui->listD1->indexList.clear();
  ui->listD2->clear();
  ui->listD2->indexList.clear();
  ui->listD3->clear();
  ui->listD3->indexList.clear();
  ui->listD4->clear();
  ui->listD4->indexList.clear();
  //qDebug() << "All List and its Vector Clear!";
}

void Widget::on_listFour_currentRowChanged(int currentRow)
{
  qDebug() << "[IN] on_listFour_currentRowChanged, asking for " << currentRow;
  if(currentRow >= 0)
  {
    //qDebug() << "Current Time : " << ui->listTime->currentItem()->text();
    //qDebug() << "Current Row : " << currentRow;
    //qDebug() << "Name : " << fourList->nameList.at(currentRow);
    //qDebug() << "#Disconnect# at [on_listFour_currentRowChanged]";
    disconnectAll();
    //qDebug() << "Disconnected!";
    qDebug() << "ItemList Mod at [on_listFour_currentRowChanged]";
    itemList = fourList->listList.at(currentRow);
    connectAll();
    // itemList->showAll();
    deployContent();
  }
  else
  {
    //qDebug() << "No Item Should Be Handled. Disconnected All";
  }
  qDebug() << "[OUT] on_listFour_currentRowChanged";
}


void Widget::on_listFour_itemDoubleClicked(QListWidgetItem *item)
{
  item->setFlags(item->flags() | Qt::ItemIsEditable);
  ui->listFour->editItem(item);
}

void Widget::on_listFour_itemChanged(QListWidgetItem *item)
{
  int indexRow = ui->listFour->currentRow();
  //qDebug() << "At : " << indexRow << " : " << item->text();
  fourList->fourListMod(indexRow, item->text());
}

void Widget::on_btnDelFour_clicked()
{
  //qDebug() << "Asking for Delete a List Item!";
  // qDebug() << ui->listFour->currentRow();
  QString dlgTitle = "删除";
  QString strInfo = "删除操作无法撤回，是否继续？";
  QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
  QMessageBox::StandardButton result;
  result = QMessageBox::question(this, dlgTitle, strInfo,
                                 QMessageBox::Yes |
                                 QMessageBox::No |
                                 QMessageBox::Cancel, defaultBtn);
  if (result == QMessageBox::Yes)
  {
    //qDebug() << "Delete Process Start!";
    int row = ui->listFour->currentRow();
    qDebug() << "#Disconnect# at [on_btnDelFour_clicked]";
    disconnectAll();
    fourList->fourListDel(row);
    //qDebug() << "Del out";
    if(fourList->getCurrentCount() > 0)
    {
      //qDebug() << "Still Have Item(s)";
      // qDebug() << "Delete at Row " << row;
      if(row == 0)
      {
        //qDebug() << "Delete at Index 0";
        qDebug() << "ItemList Mod at [on_btnDelFour_clicked]";
        itemList = fourList->listList.at(0);
        ui->listFour->setCurrentItem(NULL);
        delete ui->listFour->item(0);
        ui->listFour->setCurrentRow(0);
      }
      else
      {
        //qDebug() << "Delete at Index " << row;
        //qDebug() << "Set at " << row - 1;
        qDebug() << "ItemList Mod at [on_btnDelFour_clicked]";
        itemList = fourList->listList.at(row - 1);
        ui->listFour->setCurrentRow(row - 1);
        //qDebug() << ui->listFour->nameList;
        //qDebug() << ui->listFour->listList;
        delete ui->listFour->item(row);
      }
    }
    else
    {
      qDebug() << "No More Item, Add New at Head";
      qDebug() << "Delete at Row " << row;
      QString name = QString("新的四象限图%1").arg(fourList->fourItemCount + 1);
      QListWidgetItem *aItem = new QListWidgetItem(name);
      ui->listFour->addItem(aItem);
      qDebug() << "ItemList Mod at [on_btnDelFour_clicked]";
      itemList = fourList->fourListAdd(name);
      ui->listFour->setCurrentItem(NULL);
      delete ui->listFour->item(0);
      ui->listFour->setCurrentRow(0);
      addToList(tr("新的条目"));
    }
    // qDebug() << "Delete Complete!";
  }
  else
    qDebug() << "Nope!";
}

void Widget::on_btnAddTime_clicked()
{
  /*
   * 1. 添加时间点条目
   * 2. 设置这个为当前被激活的条目
   * 3. 设置fourList无焦点
   * 4. 断开connect
   * 5. 根据选择的条目更新fourList
   * 6. 设置fourList的第一个条目为被激活的条目
   */
  qDebug() << "[IN] on_btnAddTime_clicked";
  fourList = ui->listTime->timeListAdd(getNewDate());
  ui->listFour->setCurrentItem(NULL);
  QString name = QString("新的四象限图%1").arg(fourList->fourItemCount + 1);
  qDebug() << "ItemList Mod at [on_btnAddTime_clicked]";
  disconnectAll();
  itemList = fourList->fourListAdd(name); //新建一个四象限图，这个四象限图对应一个ItemList
  QListWidgetItem *aItem = new QListWidgetItem(name);
  ui->listFour->addItem(aItem);
  ui->listFour->setCurrentRow(0);
  ui->listTime->setCurrentRow(ui->listTime->getCurrentCount() - 1);
  addToList(tr("新的条目"));
  qDebug() << "[OUT] on_btnAddTime_clicked";
  qDebug() << "Time List set to " << ui->listTime->getCurrentCount() - 1;
}

void Widget::deployFourList()
{
  qDebug() << "[IN] deployFourList";
  ui->listFour->setCurrentItem(NULL);
  ui->listFour->clear();
  // qDebug() << "ItemList Mod at [deployFourList]";
  for(int i = 0; i < fourList->getCurrentCount(); i++)
  {
    qDebug() << "Here's Inside The Deploy Process!";
    ui->listFour->addItem(fourList->nameList.at(i));
  }
  qDebug() << "[OUT] deployFourList";
}

void Widget::on_listTime_currentRowChanged(int currentRow)
{
  qDebug() << "[IN] on_listTime_currentRowChanged";
  qDebug() << "Time List Row Change to :" << currentRow;
  if(currentRow >=0)
  {
    /*
   * 发生了元素切换
   * 1. 挂载新的fourList
   * 2. 设置fourList无焦点
   * 3. 断开连接
   * 4. 更新fourList
   * 5. 设置fourList第一个被激活
   */
    //qDebug() << "#Disconnect# at [on_listTime_currentRowChanged]";
    //itemList->showAll();
    //qDebug() << "Selected Row: " << currentRow << " Name is : " << ui->listTime->nameList.at(currentRow);
    fourList = ui->listTime->listList.at(currentRow);
    //qDebug() << fourList->nameList;
    deployFourList();
    ui->listFour->setCurrentRow(0);
  }
  else
  {
  }
  qDebug() << "[OUT] on_listTime_currentRowChanged";
}

void Widget::on_listTime_itemDoubleClicked(QListWidgetItem *item)
{
  qDebug() << "Asking for Rename :" << item->text();
  int indexRow = ui->listTime->currentRow();
  QString newDate = getNewDate();
  ui->listTime->timeListMod(indexRow, newDate);
  item->setText(newDate);
}

void Widget::on_listTime_customContextMenuRequested(const QPoint &pos)
{
  qDebug() << "Right Menu Requested!";
  Q_UNUSED(pos);
  QMenu *menu = new QMenu(this);
  menu->addAction(ui->actListTimeDel);

  menu->exec(QCursor::pos());

  delete menu;
}

void Widget::on_actListTimeDel_triggered()
{
  qDebug() << "[IN] on_actListTimeDel_triggered";
  qDebug() << "Asking for Delete At: " << ui->listTime->currentRow();
  QString dlgTitle = "删除";
  QString strInfo = "删除操作无法撤回，是否继续？";
  QMessageBox::StandardButton defaultBtn = QMessageBox::No;
  QMessageBox::StandardButton result;
  result = QMessageBox::question(this, dlgTitle, strInfo,
                                 QMessageBox::Yes |
                                 QMessageBox::No |
                                 QMessageBox::Cancel, defaultBtn);
  if (result == QMessageBox::Yes)
  {
    qDebug() << "Delete Confirm!";
    /*
     * 1. 获得当前请求删除的行
     * 2. xxxxx断开连接xxxxx (NO!!NEVER!!)
     * 3. 删除底层元素
     */
    int row = ui->listTime->currentRow();
    if(ui->listTime->getCurrentCount() > 1) //删除之后还有剩余的
    {
      qDebug() << "Still Have Item(s)";
      if(row == 0)
      {
        qDebug() << "[Time] Delete At: 0";
        ui->listTime->setCurrentItem(NULL);
        disconnectAll();
        delete ui->listTime->item(0);
        itemList = nullptr;
        ui->listTime->timeListDel(0);
        ui->listTime->setCurrentRow(0);
      }
      else
      {
        qDebug() << "[Time] Delete At: " << row;
        ui->listTime->setCurrentRow(row - 1);
        ui->listTime->timeListDel(row);
        qDebug() << "New Row Set!";
        delete ui->listTime->item(row);
      }
    }
    else //删除之后不再有剩余的了
    {
      /*
       * 1. 新建一个item
       * 2. 把这个item加到显示列表
       * 3. 把这个item的数据加到底层
       * 4. 焦点置空
       * 5. 删除位于0的元素，也就是请求删除的元素
       * 6. 设置新的item为当前元素
       *
       */
      qDebug() << "[Time] No More Item, Add New at Head!";
      on_btnAddTime_clicked();

      qDebug() << "[Time] Delete At: 0";
      ui->listTime->setCurrentItem(NULL);
      delete ui->listTime->item(0);
      ui->listTime->timeListDel(0);
      ui->listTime->setCurrentRow(0);
    }
  }
  else
  {
    qDebug() << "Nope!";
  }
  qDebug() << "[OUT] on_actListTimeDel_triggered";
}


QString Widget::getNewDate()
{
  DateDialog *dlg = new DateDialog(this);
  Qt::WindowFlags flags = dlg->windowFlags();
  dlg->setWindowFlags(flags
                      | Qt::MSWindowsFixedSizeDialogHint
                      | Qt::FramelessWindowHint);
  dlg->setDate();
  dlg->exec();
  QString result = dlg->getDate();
  delete dlg;
  qDebug() << "Date::" << result;
  return result;
}

void Widget::on_btnXLeft_clicked()
{
  labelsMod();
}

void Widget::on_btnXRight_clicked()
{
  labelsMod();
}

void Widget::on_btnYUp_clicked()
{
  labelsMod();
}

void Widget::on_btnYDown_clicked()
{
  labelsMod();
}

void Widget::labelsMod()
{
  ui->listLabel->setCurrentItem(NULL);
  itemList->labelIndex = -1;
  LabelsDialog *dlg = new LabelsDialog(this);
  Qt::WindowFlags flags = dlg->windowFlags();
  dlg->setWindowFlags(flags
                      | Qt::MSWindowsFixedSizeDialogHint
                      | Qt::FramelessWindowHint);
  dlg->preSetLabels(itemList);
  dlg->exec();
  dlg->getModLabels(itemList);
  deployLabels();
  delete dlg;
  qDebug() << "labels dialog complete!";
}

void Widget::deployLabels()
{
  ui->btnXRight->setText(strMod(itemList->labelXRight));
  ui->btnXLeft->setText(strMod(itemList->labelXLeft));
  ui->btnYUp->setText(itemList->labelYUp);
  ui->btnYDown->setText(itemList->labelYDown);
  qDebug() << "This list is " << itemList->labelIndex;
  if(itemList->labelIndex >= 0)
  {
    ui->listLabel->setCurrentRow(itemList->labelIndex);
  }
  else
  {
    ui->listLabel->setCurrentItem(NULL);
  }
  // qDebug() << "Labels deploy complete!";
}

QString Widget::strMod(QString &str)
{
  // qDebug() << "Asking for " << str;
  QString res;
  res.clear();
  for(auto c: str)
  {
    res.append(c);
    res.append('\n');
  }
  res = res.left(res.length() - 1);
  //qDebug() << res;
  return res;
}

// 切换提供的标签
void Widget::on_listLabel_currentRowChanged(int currentRow)
{
  if(currentRow >= 0)
  {
    itemList->labelIndex = currentRow;
    //qDebug() << labelsSet.at(currentRow);
    //qDebug() << detailSet.at(currentRow);
    itemList->labelXRight = labelsSet.at(currentRow).at(0);
    itemList->labelXLeft = labelsSet.at(currentRow).at(1);
    itemList->labelYUp = labelsSet.at(currentRow).at(2);
    itemList->labelYDown = labelsSet.at(currentRow).at(3);
    deployLabels();
  }
}

bool Widget::saveDateAsStream(QString &fileName)
{
  QFile aFile(fileName);
  if(!(aFile.open(QIODevice::WriteOnly | QIODevice::Truncate)))
    return false;

  QDataStream aStream(&aFile);
  aStream.setVersion(QDataStream::Qt_5_9);

  /*
   *   c 时间点数量 qint16
   *     for 每一个时间点:
   *   c   时间点名称 QString
   *   c   四象限列表个数 qint
   *       for 时间点的每一个四象限列表:
   *   c     四象限列表名称 QString
   *           for 四象限列表的每一个条目列表:
   *   c         四个位置的标签
   *   c         条目个数 qint16
   *             for 条目列表的每一个条目:
   *   c           位置 qint16
   *   c           文字 QString
   */
  qint16 timeItemCount = ui->listTime->count();
  aStream << timeItemCount;

  for(int i = 0; i < timeItemCount; i++)
  {
    QString timePointName = ui->listTime->item(i)->text();
    aStream << timePointName;
    qDebug() << "[Date Duration] " << timePointName;
    qint16 fourListCount = ui->listTime->listList.at(i)->getCurrentCount();
    aStream << fourListCount;
    FourList *et = ui->listTime->listList.at(i);
    for(int j = 0; j < fourListCount; j++)
    {
      QString fourItemName = et->nameList.at(j);
      aStream << fourItemName;
      qDebug() << "\t[Four Item]" << fourItemName;
      ItemDataList *el = et->listList.at(j);
      aStream << el->labelXRight
              << el->labelXLeft
              << el->labelYUp
              << el->labelYDown;
      qDebug() << "\t\t [Canvas Labels] "
               << el->labelXRight
               << el->labelXLeft
               << el->labelYUp
               << el->labelYDown;
      qint16 labelIndex = el->labelIndex;
      aStream << labelIndex;
      qDebug() << "\t\t [Labels Index] " << labelIndex;
      qint16 itemListCount = el->itemList.count();
      aStream << itemListCount;
      qDebug() << "\t\t\t[Item]Place" << "\t"
               << "Value";
      for(auto k = el->itemList.constBegin(); k != el->itemList.constEnd(); ++k)
      {
        qint16 place = k.value()->getPlace();
        QString value = k.value()->getValue();
        aStream  << place
                 << value;

        qDebug() << "\t\t\t[Item]"
                 << place << "\t"
                 << value;
      }
    }
  }
  aFile.close();
  return true;
}

bool Widget::openDataAsStream(QString &fileName)
{
  qDebug() << "Asking for Open at: " << fileName;
  /*
   *   c 时间点数量 qint16
   *     for 每一个时间点:
   *   c   时间点名称 QString
   *   c   四象限列表个数 qint
   *       for 时间点的每一个四象限列表:
   *   c     四象限列表名称 QString
   *           for 四象限列表的每一个条目列表:
   *   c         四个位置的标签
   *   c         条目个数 qint16
   *             for 条目列表的每一个条目:
   *   c           主键 qint16
   *   c           位置 qint16
   *   c           文字 QString
   */
  QFile aFile(fileName);
  if(!(aFile.open(QIODevice::ReadOnly)))
    return false;

  clearAll();

  QDataStream aStream(&aFile);
  aStream.setVersion(QDataStream::Qt_5_9);
  qint16 timeItemCount;
  aStream >> timeItemCount;
  for(int i = 0; i < timeItemCount; i++)
  {
    QString timePointName;
    aStream >> timePointName;
    FourList *four = ui->listTime->timeListAdd(timePointName);
    qDebug() << "[Date Duration] " << timePointName;
    qint16 fourListCount;
    aStream >> fourListCount;
    for(int j = 0; j < fourListCount; j++)
    {
      QString fourItemName;
      aStream >> fourItemName;
      ItemDataList *ilist = four->fourListAdd(fourItemName);
      qDebug() << "\t[Four Item]" << fourItemName;
      QString xRight, xLeft, yUp, yDown;
      aStream >> xRight >> xLeft >> yUp >> yDown;
      ilist->labelXRight = xRight;
      ilist->labelXLeft = xLeft;
      ilist->labelYUp = yUp;
      ilist->labelYDown = yDown;
      qDebug() << "\t\t [Canvas Labels] "
               << xRight
               << xLeft
               << yUp
               << yDown;
      qint16 labelIndex;
      aStream >> labelIndex;
      ilist->labelIndex = labelIndex;
      qDebug() << "\t\t [Labels Index] " << labelIndex;
      qDebug() << "\t\t\t[Item]Place" << "\t"
               << "Value";
      qint16 itemListCount;
      aStream >> itemListCount;
      for(int k = 0; k < itemListCount; k++)
      {
        qint16 place;
        QString value;
        aStream >> place >> value;
        ilist->itemListAdd(value, place);
        qDebug() << "\t\t\t[Item]"
                 << place << "\t"
                 << value;
      }
    }
  }
  aFile.close();
  return true;
}

void Widget::clearAll()
{
  ui->listTime->setCurrentItem(NULL);
  ui->listTime->clear();
  ui->listFour->setCurrentItem(NULL);
  ui->listFour->clear();
  ui->listLabel->setCurrentItem(NULL);
  //ui->listLabel->clear();
  clearAllList();
  int cnt = ui->listTime->getCurrentCount();
  qDebug() << "There are: " << cnt;
  for(int i = cnt - 1; i >= 0; i--)
  {
    qDebug() << "###### delete at" << i;
    ui->listTime->timeListDel(i);
  }
  qDebug() << "###########Delete!!";
  itemList = nullptr;
}

void Widget::on_btnSave_clicked()
{
  QString curPath = QDir::currentPath();
  QString aFileName = QFileDialog::getSaveFileName(this, "选择保存文件",
                                                   curPath, "Qt预定义编码数据文件(*.stm)");
  // qDebug() << aFileName;
  if(aFileName.isEmpty())
    qDebug() << "[Abort] Empty Filename, Denied!";

  if(saveDateAsStream(aFileName))
    qDebug() << "[SAVE] 文件保存成功";
  else
    qDebug() << "[Error][SAVE] 文件保存失败";
}



void Widget::on_btnImport_clicked()
{
  qDebug() << "Load File";

  QString curPath = QDir::currentPath();
  QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件",
                                                   curPath, "Qt预定义编码数据文件(*.stm)");
  if(aFileName.isEmpty())
  {
    qDebug() << "[Error][Open] Empty File, Denied!";
    return;
  }

  if(openDataAsStream(aFileName))
  {
    qDebug() << "[OPEN] 文件打开成功";
    ui->listTime->setCurrentRow(0);
  }
  else
    qDebug() << "[Error][OPEN] 文件打开失败";
}

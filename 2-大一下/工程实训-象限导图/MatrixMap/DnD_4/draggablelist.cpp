#include "draggablelist.h"
#include <QApplication>
#include <QMimeData>
#include <QDebug>
#include "widget.h"

DraggableList::DraggableList(QWidget *parent) :
  QListWidget(parent)
{
  setAcceptDrops(true);
  indexList.empty();
}

DraggableList::~DraggableList()
{
  indexList.clear();
  qDebug() << "Drag List Destroyed!";
}

void DraggableList::mousePressEvent(QMouseEvent *event)
{
  QListWidgetItem *clickedItem = itemAt(event->pos());
  if(clickedItem)
  {
    // qDebug() << clickedItem->text();
    // qDebug() << this->property("objectName");
    if (event->button() == Qt::LeftButton)
    {
      startPos = event->pos();
      QListWidget::mousePressEvent(event);
    }
    else if (event->button() == Qt::RightButton)
    {
      QListWidget::mousePressEvent(event);
      /*传递参数必要性:
       * 1. 传递右键点击的位置，用于请求右键菜单显示
       * 2. 传递所属的QListWidget，用于指定操作作用于何处
       */
      emit customContextMenuRequested(event->pos());
    }
  }
}

void DraggableList::mouseMoveEvent(QMouseEvent *event)
{

  if(event->buttons() & Qt::LeftButton)
  {
    int distance = (event->pos() - startPos).manhattanLength();
    if(distance >= QApplication::startDragDistance())
      performDrag();
  }
  QListWidget::mouseMoveEvent(event);
}

void DraggableList::performDrag()
{
  QListWidgetItem *item = currentItem();
  QModelIndex index = currentIndex();
  if(item)
  {
    QMimeData *mimeData = new QMimeData;
    //QVector<int, QString> innerData(index.row(), item->text());
    //mimeData->setText(item->text());
    QByteArray encodeData;
    QDataStream stream(&encodeData, QIODevice::WriteOnly);
    stream << indexList.at(index.row()) << item->text();
    mimeData->setData("application", encodeData);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    if(drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {
      // qDebug() << "In" << this->property("objectName").toString() << ", Item Del at " << index.row();
      //qDebug() << "**********************";
      //qDebug() << "Before Erase: " << this->indexList;
      this->indexList.erase(this->indexList.begin() + index.row());
      //qDebug() << "After Erase: " << this->indexList;
      //qDebug() << "**********************";
      delete item;
    }
  }
}

void DraggableList::dragEnterEvent(QDragEnterEvent *event)
{
  DraggableList *source = qobject_cast<DraggableList *>(event->source());
  if(source && source != this)
  {
    // qDebug() << "Drag Enter!";
    event->setDropAction(Qt::MoveAction);
    event->accept();
  }
}

void DraggableList::dragMoveEvent(QDragMoveEvent *event)
{
  DraggableList *source = qobject_cast<DraggableList *>(event->source());
  if (source && source != this)
  {
    // qDebug() << "Drag Move!";
    event->setDropAction(Qt::MoveAction);
    event->accept();
  }
}

void DraggableList::dropEvent(QDropEvent *event)
{
  DraggableList *source = qobject_cast<DraggableList *>(event->source());
  if(source && source != this)
  {
    qDebug() << "Drop Event";
    QWidget *child = childAt(event->pos());
    DraggableList *target = qobject_cast<DraggableList *>(child->parentWidget());
    QString targetName = target->property("objectName").toString();
    QString sourceName = source->property("objectName").toString();

    // qDebug() << "In" << targetName << ", Item Add at " << target->count();
    QByteArray encodedData = event->mimeData()->data("application");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QString value;
    int index;
    stream >> index >> value;
    //qDebug() << "Get!" << index << value;
    this->addItem(value);
    //qDebug() << "**********************";
    //qDebug() << "Before Insert: " << target->indexList;
    this->indexList.append(index);
    //qDebug() << "After Insert: " << target->indexList;
    //qDebug() << target->indexList;
    //qDebug() << "**********************";
    event->setDropAction(Qt::MoveAction);
    event->accept();
    // qDebug() << "From:" << sourceName << " to: " << targetName;
    if(!sourceName.compare(QString("listFree")))
    {
      // qDebug() << "From Free to D";
      emit itemFlow(value, 1, index);
    }
    else if(!targetName.compare(QString("listFree")))
    {
      // qDebug() << "From D to Free";
      emit itemFlow(value, 0, index);
    }
    qDebug() << "[DropEvent] Drop of" << index;
    emit itemPlaceChanged(index); //使用sender来指明被放入的List，这样就可以得到place
  }
}

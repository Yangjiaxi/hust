#ifndef DRAGGABLELIST_H
#define DRAGGABLELIST_H

#include <QListWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "itemdatalist.h"

class DraggableList : public QListWidget
{
  Q_OBJECT
public:
  DraggableList(QWidget *parent = nullptr);
  ~DraggableList();
  QVector<int> indexList;

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void dragEnterEvent(QDragEnterEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dropEvent(QDropEvent *event);

private:
  void performDrag();
  QPoint startPos;

signals:
  void itemFlow(QString value, int dir, int index);
  void itemEdited(QString before, QString after);
  void itemPlaceChanged(int index);

};

#endif // DRAGGABLELIST_H

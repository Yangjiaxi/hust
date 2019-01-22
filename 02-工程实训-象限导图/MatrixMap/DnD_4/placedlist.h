#ifndef PLACEDLIST_H
#define PLACEDLIST_H

#include <QListWidget>

class PlacedList : public QListWidget
{
  Q_OBJECT
public:
  PlacedList(QWidget *parent = nullptr);
  QVector<int> indexList;
  void on_itemDel(int index);
  void on_itemMod(QString value, int index);

private slots:
  void on_itemFlow(QString value, int dir, int index);
};

#endif // PLACEDLIST_H

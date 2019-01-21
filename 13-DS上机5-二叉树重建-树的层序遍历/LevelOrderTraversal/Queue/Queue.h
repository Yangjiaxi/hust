#ifndef QUEUE_H
#define QUEUE_H

#include "../DoublyList/DoublyList.h"

typedef DoublyList Queue;

typedef DLElementType QElementType;

// 初始化
Queue InitQueue(Queue Q);
// 队列是否为空
Bool IsQueueEmpty(Queue Q);
// 队头入队
void InsertFirst(QElementType X, Queue Q);
// 队尾入队
void InsertLast(QElementType X, Queue Q);
// 队头出队
QElementType RemoveFirst(Queue Q);
// 队尾出队
QElementType RemoveLast(Queue Q);
// 返回队头
QElementType First(Queue Q);
// 返回队尾
QElementType Last(Queue Q);
// 打印队列
void PrintQueue(Queue Q);
// 清空数据但队列仍可使用
Queue RemoveAll(Queue Q);
// 彻底删除队列
Queue DeleteQueue(Queue Q);

#endif  // QUEUE_H
#include "Queue.h"

Queue InitQueue(Queue Q)
{
    return InitDoublyList(Q);
}

Bool IsQueueEmpty(Queue Q)
{
    return DLIsEmpty(Q);
}

void InsertFirst(QElementType X, Queue Q)
{
    DLInsertBefore(X, Q, DLHead(Q));
}

void InsertLast(QElementType X, Queue Q)
{
    DLInsertAfter(X, Q, DLTail(Q));
}

QElementType RemoveFirst(Queue Q)
{
    QElementType X = DLRetrieve(DLHead(Q));
    DLDeleteByPtr(DLHead(Q), Q);
    return X;
}

QElementType RemoveLast(Queue Q)
{
    QElementType X = DLRetrieve(DLTail(Q));
    DLDeleteByPtr(DLTail(Q), Q);
    return X;
}

QElementType First(Queue Q)
{
    return DLRetrieve(DLHead(Q));
}

QElementType Last(Queue Q)
{
    return DLRetrieve(DLTail(Q));
}

void PrintQueue(Queue Q)
{
    PrintDLList(Q, "Queue", "-");
}

Queue RemoveAll(Queue Q)
{
    return MakeDLEpmty(Q);
}

Queue DeleteQueue(Queue Q)
{
    return DeleteDoublyList(Q);
}
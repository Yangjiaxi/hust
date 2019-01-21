#include "DoublyList.h"
#include <stdio.h>
#include <stdlib.h>

DoublyList InitDoublyList(DoublyList L)
{
    if (L != NULL)
    {
        DeleteDoublyList(L);
        free(L);
        L = NULL;
    }
    L = malloc(sizeof(struct _DoublyList));
    if (L == NULL)
    {
        Fatal("[ERROR] Out of Space!\n");
    }
    else
    {
        L->Head = NULL;
        L->Tail = NULL;
    }
    return L;
}

DLPosition CreateDLNode(DLPosition Prev, DLElementType X, DLPosition Next)
{
    DLPosition tmp = malloc(sizeof(struct DLNode));
    tmp->Element = X;
    tmp->Prev = Prev;
    tmp->Next = Next;
    return tmp;
}

DoublyList DeleteDoublyList(DoublyList L)
{
    L = MakeDLEpmty(L);
    L = NULL;
    return L;
}

DoublyList MakeDLEpmty(DoublyList L)
{
    DLPosition p, tmp;
    p = L->Head;
    while (p != NULL)
    {
        // printf("Delete : %d\n", p->Element);
        tmp = p->Next;
        free(p);
        p = tmp;
    }
    L->Head = NULL;
    L->Tail = NULL;
    return L;
}

Bool DLIsEmpty(DoublyList L)
{
    return L->Head == NULL;
}

Bool DLIsFirst(DLPosition P, DoublyList L)
{
    return L->Head == P;
}

Bool DLIsLast(DLPosition P, DoublyList L)
{
    return P == L->Tail;
}

DLPosition DLFindByValue(DLElementType X, DoublyList L)
{
    DLPosition P;
    P = L->Head;
    while (P != NULL && P->Element != X)
    {
        P = P->Next;
    }
    return P;
}

void DLDeleteByValue(DLElementType X, DoublyList L)
{
    DLPosition P;
    P = DLFindByValue(X, L);
    DLDeleteByPtr(P, L);
}

void DLDeleteByPtr(DLPosition P, DoublyList L)
{
    // 1. 前面元素的连接权修正
    if (P->Prev != NULL)  // 不是头结点
    {
        P->Prev->Next = P->Next;
    }
    else  // 是头结点
    {
        L->Head = P->Next;
    }
    // 2. 后面元素的连接权修正
    if (P->Next != NULL)  // 不是尾节点
    {
        P->Next->Prev = P->Prev;
    }
    else
    {
        L->Tail = P->Prev;
    }
    free(P);
}

DLPosition DLInsertAfter(DLElementType X, DoublyList L, DLPosition P)
{
    DLPosition newbee = CreateDLNode(P, X, P == NULL ? NULL : P->Next);
    if (newbee == NULL)
    {
        Fatal("[ERROR] Out of space!\n");
    }
    else
    {
        if (P != NULL)
        {
            if (P->Next != NULL)  // P不是表尾
            {
                P->Next->Prev = newbee;
            }
            else  // 是表尾
            {
                L->Tail = newbee;
            }
            P->Next = newbee;
        }
        else  // 链表为空
        {
            L->Head = L->Tail = newbee;
        }
    }
    return newbee;
}

DLPosition DLInsertBefore(DLElementType X, DoublyList L, DLPosition P)
{
    DLPosition newbee = CreateDLNode(P == NULL ? NULL : P->Prev, X, P);
    if (newbee == NULL)
    {
        Fatal("[ERROR] Out of space!\n");
    }
    else
    {
        if (P != NULL)
        {
            if (P->Prev != NULL)  // P不是表头
            {
                P->Prev->Next = newbee;
            }
            else  // P是表头
            {
                L->Head = newbee;
            }
            P->Prev = newbee;
        }
        else  // 表为空
        {
            L->Head = L->Tail = newbee;
        }
    }
    return newbee;
}

DLPosition DLHead(DoublyList L)
{
    return L->Head;
}

DLPosition DLTail(DoublyList L)
{
    return L->Tail;
}

DLPosition DLForward(DLPosition P)
{
    return P->Next;
}

DLPosition DLForward_n(DLPosition P, int n)
{
    DLPosition target = P;
    for (int i = 1; i <= n; i++)
    {
        target = target->Next;
    }
    return target;
}

DLPosition DLBackward(DLPosition P)
{
    return P->Prev;
}

DLPosition DLBackward_n(DLPosition P, int n)
{
    DLPosition target = P;
    for (int i = 1; i <= n; i++)
    {
        target = target->Prev;
    }
    return target;
}

DLElementType DLRetrieve(DLPosition P)
{
    return P->Element;
}

int DLLength(DoublyList L)
{
    int count = 0;
    DLPosition tmp = DLHead(L);
    while (tmp != NULL)
    {
        ++count;
        tmp = tmp->Next;
    }
    return count;
}

void PrintDLList(DoublyList L, char* title, char* link)
{
    if (title == NULL)
        title = "Doubly Linked List";
    AlignPrint(GetConsoleWidth(), '-', title);
    DLPosition P;
    P = L->Head;
    while (P != NULL)
    {
        printf("%d", (int)P->Element);
        P = P->Next;
        if (P != NULL)
        {
            printf("%s", link);
        }
    }
    endl();
    AlignPrint(GetConsoleWidth(), '-', "End");
}

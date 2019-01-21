#ifndef DOUBLYLINKEDLIST_DOUBLY_LIST_H
#define DOUBLYLINKEDLIST_DOUBLY_LIST_H

#include "../Utils/Utils.h"

struct DLNode;
typedef struct DLNode* PtrToNode;
typedef PtrToNode DLPosition;
typedef struct _DoublyList* DoublyList;

typedef void* DLElementType;

// 初始化双向链表
DoublyList InitDoublyList(DoublyList L);
// 创建节点(对外隐藏)
DLPosition CreateDLNode(DLPosition Prev, DLElementType X, DLPosition Next);
// 彻底删除该双向链表L
DoublyList DeleteDoublyList(DoublyList L);
// 清空双向链表中的数据(但是还可继续使用)
DoublyList MakeDLEpmty(DoublyList L);
// 链表为空吗
Bool DLIsEmpty(DoublyList L);
// P所指是链表的首元素吗
Bool DLIsFirst(DLPosition P, DoublyList L);
// P所指是链表的尾元素吗
Bool DLIsLast(DLPosition P, DoublyList L);
// 通过值X寻找元素，返回指向元素的指针
DLPosition DLFindByValue(DLElementType X, DoublyList L);
// 通过值删除元素
void DLDeleteByValue(DLElementType X, DoublyList L);
// 通过指针删除元素
void DLDeleteByPtr(DLPosition P, DoublyList L);
// 在指针P之后插入元素X
DLPosition DLInsertAfter(DLElementType X, DoublyList L, DLPosition P);
// 在指针P之前插入元素X
DLPosition DLInsertBefore(DLElementType X, DoublyList L, DLPosition P);
// 返回表头
DLPosition DLHead(DoublyList L);
// 返回表尾
DLPosition DLTail(DoublyList L);
// 从P向后走1
DLPosition DLForward(DLPosition P);
// 从P向后走n
DLPosition DLForward_n(DLPosition P, int n);
// 从P向前走1
DLPosition DLBackward(DLPosition P);
// 从P向前走1
DLPosition DLBackward_n(DLPosition P, int n);
// 返回P节点存储的值
DLElementType DLRetrieve(DLPosition P);
// 返回链表的长度
int DLLength(DoublyList L);
// 打印双向链表
void PrintDLList(DoublyList L, char* title, char* link);
// 双向链表节点
struct DLNode
{
    DLElementType Element;
    DLPosition Next;
    DLPosition Prev;
};
// ADT::双向链表
struct _DoublyList
{
    DLPosition Head;
    DLPosition Tail;
};

#endif  // DOUBLYLINKEDLIST_DOUBLY_LIST_H

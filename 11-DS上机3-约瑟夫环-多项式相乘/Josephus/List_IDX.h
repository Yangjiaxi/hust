//
// Created by VanYang on 2018/12/3.
//

#ifndef LIST_IDX_LIST_IDX_H
#define LIST_IDX_LIST_IDX_H

#define SPACE_SIZE 100

typedef int ElementType;
typedef ElementType PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

void InitListIDX(void);

int NewList();

int IsEmpty(List L);

int IsLast(const Position P);

Position Find(ElementType X, const List L);

void Delete(ElementType X, List L);

Position FindPrevious(ElementType X, const List L);

Position Insert(ElementType X, List L, Position P);

void DeleteList(List L);

Position Header(const List L);

Position First(const List L);

Position Advance(const Position P);

Position RollAdv(const Position P, const List L);

ElementType Retrieve(const Position P);

void PrintList(const List L);

void ShowStoreSpace();

#endif  // LIST_IDX_LIST_IDX_H

struct Node
{
    ElementType ELement;
    Position Next;
};

struct Node CursorSpace[SPACE_SIZE];

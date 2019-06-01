#ifndef LIST_POINTER_LIST_H
#define LIST_POINTER_LIST_H

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List InitList(List L);

int IsEmpty(List L);

int IsLast(Position P, List L);

Position Find(int X, List L);

void DeleteByValue(int X, List L);

void DeleteByPtr(Position X, List L);

Position FindPreviousByValue(int X, List L);

Position FindPreviousByPtr(Position P, List L);

Position InsertAfter(int X, List L, Position P);

void DeleteList(List L);

Position Header(List L);

Position FirstElement(List L);

Position Advance(Position P);

Position Advance_n(Position P, int n);

int Retrieve(Position P);

int Length(List L);

void PrintList(List L, char* title);

#endif  // LIST_POINTER_LIST_H
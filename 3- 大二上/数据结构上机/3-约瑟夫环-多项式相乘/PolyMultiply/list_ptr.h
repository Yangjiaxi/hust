#ifndef LIST_POINTER_LIST_H
#define LIST_POINTER_LIST_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List InitList(List L);

int IsEmpty(List L);

int IsLast(Position P, List L);

Position FindByExp(int Exp, List L);

void DeleteByExp(int X, List L);

void DeleteByPtr(Position X, List L);

Position FindPreviousByExp(int Exp, List L);

Position FindPreviousByPtr(Position P, List L);

Position InsertAfter(int exp, int cof, List L, Position P);

void DeleteList(List L);

Position Header(List L);

Position FirstElement(List L);

Position Advance(Position P);

Position Advance_n(Position P, int n);

int Retrieve(Position P);

int Length(List L);

void PrintList(List L);

void InverseList(List L);

struct Node
{
    int exp;
    int coef;
    Position next;
};

#endif //LIST_POINTER_LIST_H
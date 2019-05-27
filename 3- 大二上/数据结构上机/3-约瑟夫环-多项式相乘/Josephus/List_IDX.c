//
// Created by VanYang on 2018/12/3.
//

#include "List_IDX.h"
#include <stdio.h>

static void FatalError(char* str)
{
    printf("[ERROR] %s\n", str);
}

void InitListIDX(void)
{
    for (int i = 0; i < SPACE_SIZE; i++)
    {
        CursorSpace[i].ELement = 0;
        CursorSpace[i].Next = i + 1;
    }
    CursorSpace[SPACE_SIZE - 1].Next = 0;
}

static Position CursorAlloc(void)
{
    Position P;
    P = CursorSpace[0].Next;
    CursorSpace[0].Next = CursorSpace[P].Next;
    return P;
}

int NewList()
{
    Position P = CursorAlloc();
    CursorSpace[P].Next = 0;
    CursorSpace[P].ELement = 0;
    return P;
}

static void CursorFree(Position P)
{
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}

int IsEmpty(List L)
{
    return CursorSpace[L].Next == 0;
}

int IsLast(Position P)
{
    return CursorSpace[P].Next == 0;
}

Position Find(ElementType X, List L)
{
    Position P;
    P = CursorSpace[L].Next;
    while (P && CursorSpace[P].ELement != X)
        P = CursorSpace[P].Next;
    return P;
}

Position FindPrevious(ElementType X, List L)
{
    Position P = 1;
    while (CursorSpace[P].Next && CursorSpace[CursorSpace[P].Next].ELement != X)
        P = CursorSpace[P].Next;
    return P;
}

void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if (!IsLast(P))
    {
        TmpCell = CursorSpace[P].Next;
        CursorSpace[TmpCell].ELement = 0;
        CursorSpace[P].Next = CursorSpace[TmpCell].Next;
        CursorFree(TmpCell);
    }
}

Position Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = CursorAlloc();
    if (TmpCell == 0)
        FatalError("Out of Space!");
    //    printf("Place %d at %d\n", X, P);
    CursorSpace[TmpCell].ELement = X;
    CursorSpace[TmpCell].Next = CursorSpace[P].Next;
    CursorSpace[P].Next = TmpCell;
    return TmpCell;
}

void DeleteList(List L)
{
    Position P, TemPos;
    P = CursorSpace[L].Next;
    CursorSpace[L].Next = 0;
    while (P)
    {
        TemPos = CursorSpace[P].Next;
        CursorFree(P);
        P = TemPos;
    }
}

Position Tail(const List L)
{
    return CursorSpace[0].Next;
}

void PrintList(const List L)
{
    Position P = CursorSpace[L].Next;
    if (IsEmpty(L))
    {
        printf("Empty List!\n");
    }
    while (P)
    {
        printf("%d\t", CursorSpace[P].ELement);
        P = CursorSpace[P].Next;
    }
    printf("\n");
}

Position Header(const List L)
{
    return L;
}

Position First(const List L)
{
    return CursorSpace[L].Next;
}

ElementType Retrieve(const Position P)
{
    return CursorSpace[P].ELement;
}

Position Advance(const Position P)
{
    return CursorSpace[P].Next;
}

Position RollAdv(const Position P, const List L)
{
    Position TmpCell = Advance(P);
    if (!TmpCell)
    {
        return First(L);
    }
    else
    {
        return TmpCell;
    }
}

void ShowStoreSpace()
{
    printf("\n\n------------------\n");
    printf("Global Storage:");
    printf("\nIDX\t\tELE\t\tNEXT\n");
    struct Node P;
    for (int i = 0; i < SPACE_SIZE; i++)
    {
        P = CursorSpace[i];
        printf("%d\t\t%d\t\t%d\n", i, P.ELement, P.Next);
    }
    printf("------------------\n");
}
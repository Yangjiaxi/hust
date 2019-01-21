#include <stdio.h>
#include <stdlib.h>

#include "UsefulFunc.h"
#include "list_ptr.h"

struct Node
{
    int element;
    Position next;
};

List InitList(List L)
{
    if (L != NULL)
    {
        DeleteList(L);
    }
    L = malloc(sizeof(struct Node));
    if (L == NULL)
    {
        printf("[ERROR] Out of space!!\n");
        exit(1);
    }
    L->next = NULL;
    L->element = -1;  // Header is not for restore data, the value of this Node
                      // is always -1
    return L;
}

int IsEmpty(List L)
{
    return L->next == NULL;
}

int IsLast(Position P, List L)
{
    return P->next == NULL;
}

Position Find(int X, List L)
{
    Position P;
    P = L->next;
    while (P != NULL && P->element != X)
    {
        P = P->next;
    }
    return P;
}

void DeleteByValue(int X, List L)
{
    Position P, target;
    P = FindPreviousByValue(X, L);
    if (!IsLast(P, L))
    {
        target = P->next;
        P->next = target->next;
        free(target);
    }
}

void DeleteByPtr(Position P, List L)
{
    Position prev;
    prev = FindPreviousByPtr(P, L);
    if (!IsLast(prev, L))
    {
        prev->next = P->next;
        free(P);
    }
}

Position FindPreviousByValue(int X, List L)
{
    Position P;
    P = L;
    while (P->next != NULL && P->next->element != X)
    {
        P = P->next;
    }
    return P;
}

Position FindPreviousByPtr(Position P, List L)
{
    Position tmp;
    tmp = L;
    while (tmp->next != NULL && tmp->next != P)
    {
        tmp = tmp->next;
    }
    return tmp;
}

// InsertAfter X after P in L
Position InsertAfter(int X, List L, Position P)
{
    Position target;
    target = malloc(sizeof(struct Node));
    if (target == NULL)
    {
        printf("[ERROR] Out of space!!\n");
        exit(1);
    }
    target->element = X;
    target->next = P->next;
    P->next = target;
    return target;
}

void DeleteList(List L)
{
    Position P, Tmp;
    P = L->next;
    L->next = NULL;
    while (P != NULL)
    {
        Tmp = P->next;
        free(P);
        P = Tmp;
    }
}

Position Header(List L)
{
    if (L == NULL)
    {
        printf("[ERROR] Request for a NULL, cannot get Header\n");
        exit(1);
    }
    return L;
}

Position FirstElement(List L)
{
    if (L == NULL)
    {
        printf("[ERROR] Request for a NULL, cannot get first\n");
        exit(1);
    }
    return L->next;
}

Position Advance(Position P)
{
    if (P == NULL)
    {
        printf("[ERROR] Request for a NULL, cannot perform Advance\n");
        exit(1);
    }
    return P->next;
}

Position Advance_n(Position P, int n)
{
    Position Tmp = P;
    for (int i = 0; i < n; i++)
    {
        if (Tmp != NULL)
        {
            Tmp = Tmp->next;
        }
        else
        {
            printf("[ERROR] Out of range, cannot perform Advance!\n");
            Tmp = NULL;
            break;
            // exit(1);
        }
    }
    return Tmp;
}

int Retrieve(Position P)
{
    if (P != NULL)
    {
        return P->element;
    }
    else
    {
        printf("[ERROR] Request for a NULL, cannot Retrieve!\n");
        return -1;
        // exit(1);
    }
}

void PrintList(List L, char* title)
{
    char* s = StrConcat("Print: ", title);
    AlignPrint(44, '-', s);
    free(s);
    Position P;
    P = L->next;
    while (P != NULL)
    {
        printf("%c", P->element);
        P = P->next;
        if (P != NULL)
        {
            printf(" ");
        }
    }
    AlignPrint(44, '-', "END");
}

int Length(List L)
{
    int count = 0;
    Position tmp = FirstElement(L);
    while (tmp != NULL)
    {
        ++count;
        tmp = tmp->next;
    }
    return count;
}

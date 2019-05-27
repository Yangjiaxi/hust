#include "stack.h"

Stack InitStack(Stack S)
{
    return InitList(S);
}

void Push(int X, Stack S)
{
    InsertAfter(X, S, S);
}

void PrintStack(Stack S)
{
    PrintList(S, "Stack");
}

int Top(Stack S)
{
    return Retrieve(FirstElement(S));
}

int Pop(Stack S)
{
    Position P = FirstElement(S);
    int X = Retrieve(P);
    DeleteByPtr(P, S);
    return X;
}

void DeleteStack(Stack S)
{
    DeleteList(S);
}
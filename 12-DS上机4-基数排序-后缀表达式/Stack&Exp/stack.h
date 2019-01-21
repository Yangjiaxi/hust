#ifndef STACK_POINTER_STACK_H
#define STACK_POINTER_STACK_H

#include "list_ptr.h"

typedef List Stack;

Stack InitStack(Stack S);

void Push(int X, Stack S);

int Top(Stack S);

int Pop(Stack S);

void DeleteStack(Stack S);

void PrintStack(Stack S);

#endif
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>

int Max(int a, int b)
{
    return a > b ? a : b;
}

int Height(Position P)
{
    if (P == NULL)
    {
        return -1;
    }
    else
    {
        return P->Height;
    }
}
//递归释放所有节点，相当于构造一个空树
Tree MakeEmpty(Tree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return T;
}
//在树T中寻找元素X的位置，并返回指向节点的指针，未找到返回NULL
Position Find(int X, Tree T)
{
    if (T == NULL)  //树T为空，代表寻找到叶子仍未找到目标元素；或树T本来就为空
    {
        return NULL;
    }
    else
    {
        if (X < T->Element)  //比根节点大，进入左子树搜索
        {
            return Find(X, T->Left);
        }
        else  //比根节点小，进入右字数搜索
        {
            return Find(X, T->Right);
        }
    }
}
//寻找树中最小元素
Position FindMin(Tree T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else
    {
        if (T->Left == NULL)  //当前节点的左子树为空，说明该节点保存着最小值
        {
            return T;
        }
        else  //左子树存在，必然保存着比当前节点小的值，进入左子树搜索
        {
            return FindMin(T->Left);
        }
    }
}

Position FindMax(Tree T)  //寻找树中最大元素（不使用递归）
{
    if (T != NULL)
    {
        while (T->Right != NULL)
        {
            T = T->Right;
        }
    }
    return T;
}

void InorderTreeWalk(Tree T)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        if (T->Left)
        {
            InorderTreeWalk(T->Left);
        }
        printf("%c ", T->Element);
        if (T->Right)
        {
            InorderTreeWalk(T->Right);
        }
    }
}

void PreTreeWalk(Tree T)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        printf("%c ", T->Element);
        if (T->Left)
        {
            PreTreeWalk(T->Left);
        }
        if (T->Right)
        {
            PreTreeWalk(T->Right);
        }
    }
}

void PostTreeWalk(Tree T)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        if (T->Left)
        {
            PostTreeWalk(T->Left);
        }
        if (T->Right)
        {
            PostTreeWalk(T->Right);
        }
        printf("%c ", T->Element);
    }
}
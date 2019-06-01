#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

SearchTree Insert(int X, SearchTree T)  //插入值为X的节点
{
    //这里T==null处理两种情况，1.找到了应该放置的节点 2.树T本身为空
    if (T == NULL)
    {
        T = malloc(sizeof(TreeNode));
        if (T == NULL)
        {
            printf("\nFatal Error: Out of space!\n");
            exit(-1);
        }
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else
    {
        if (X < T->Element)  //要插入的元素小于根节点进入左子树搜索
        {
            T->Left = Insert(X, T->Left);
        }
        else
        {
            T->Right = Insert(X, T->Right);
        }
        //否则，X == T->Element，元素已经存在，什么都不做
    }
    return T;
}

SearchTree Delete(int X, SearchTree T)  //删除树中值为X的节点
{
    Position TmpCell;  //相当于中间变量
    if (T == NULL)     //始终未找到
    {
        printf("Element [%d] Not Found", X);
    }
    else if (X < T->Element)  //值比节点元素小，去左子树
    {
        T->Left = Delete(X, T->Left);  //进入左子树删除元素X，并将左子树替换为删除后的树
    }
    else if (X > T->Element)  //大，去右子树
    {
        T->Right = Delete(X, T->Right);
    }
    else if (T->Left && T->Right)  //此时X == Element开始删除
    {
        //这里左右子树均存在，删除一个有两个儿子的节点比较复杂，故进行转换：
        TmpCell = FindMin(T->Right);  //将节点的值替换为右子树中最小的值，然后删除右子树中该最小的值
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else
    {
        //这里左右子树不全存在或全不存在，用存在的子树或NULL替换当前节点，然后释放当前节点（中间变量）
        TmpCell = T;
        if (T->Left == NULL)  //左子树为空
        {
            T = T->Right;
        }
        else if (T->Right == NULL)  //右子树为空
        {
            T = T->Left;
        }
        free(TmpCell);
    }
    return T;
}
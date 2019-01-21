#ifndef TREE_H
#define TREE_H

struct TreeNode;
typedef struct TreeNode* Position;
typedef struct TreeNode* Tree;

Tree MakeEmpty(Tree T);        //清空一棵树
Position Find(int X, Tree T);  //寻找值为X的节点并返回指向该节点的指针
Position FindMax(Tree T);      //寻找最大的元素
Position FindMin(Tree T);      //寻找最小的元素
int Height(Position P);        //返回节点P的高度
int Max(int a, int b);         //比大小
void InorderTreeWalk(Tree T);  //中序遍历输出
void PreTreeWalk(Tree T);      //先序遍历输出
void PostTreeWalk(Tree T);     //后序遍历输出

typedef struct TreeNode
{
    int Element;
    Tree Left;
    Tree Right;
    int Height;
} TreeNode;

#endif  // TREE_H
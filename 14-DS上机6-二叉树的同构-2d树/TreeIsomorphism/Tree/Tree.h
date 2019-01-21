#ifndef TREE_H
#define TREE_H

struct TreeNode;
typedef struct TreeNode* TPosition;
typedef struct TreeNode* Tree;

typedef char TElementType;

// 清空一棵树
Tree MakeEmpty(Tree T);
// 寻找值为X的节点并返回指向该节点的指针
TPosition Find(TElementType X, Tree T);
// 寻找最大的元素
TPosition FindMax(Tree T);
// 寻找最小的元素
TPosition FindMin(Tree T);
// 创建节点
TPosition CreateNode(TPosition L, TElementType X, TPosition R);
// 返回节点P的高度
int Height(TPosition P);
// 中序遍历输出
void InorderTreeWalk(Tree T);
// 先序遍历输出
void PreTreeWalk(Tree T);
// 后序遍历输出
void PostTreeWalk(Tree T);
// 层序遍历输出
void LevelTreeWalk(Tree T);
// 通过中序遍历和先序遍历恢复树
Tree InPreBuild(const char* InOrder, const char* PreOrder);
// 通过中序遍历和后序遍历恢复树
Tree InPostBuild(const char* InOrder, const char* PostOrder);
/*  ---- 请自行实现----
// 通过中序遍历和层序遍历恢复树
// Tree InLevelBuild(const char* InOrder, const char* LevelOrder);
    ----------------- */

// 在控制台打印树
// T : 要打印的树
// format : 元素的打印格式
// width : 元素的打印宽度
void TreePlot(Tree T, char* format, int width);
// 树节点
typedef struct TreeNode
{
    TElementType Element;
    Tree Left;
    Tree Right;
    int Height;
} TreeNode;

#endif  // TREE_H
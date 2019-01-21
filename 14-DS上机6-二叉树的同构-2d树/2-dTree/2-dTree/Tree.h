#ifndef TREE_H
#define TREE_H

struct KDNode;
typedef struct KDNode* KDPosition;
typedef struct KDNode* KDTree;

typedef int TElementType;
typedef TElementType ItemType[2];

typedef int (*Comparator)(TElementType RHS, TElementType LHS);

// 清空一棵树
KDTree MakeEmpty(KDTree T);
// 寻找值为X的节点并返回指向该节点的指针
KDTree TreeInsert(ItemType Item, KDTree T, Comparator cmp);
//在树T中寻找所有满足Low<=X<=High的元素X的位置，并打印节点数据
void FindAndPrint(ItemType Low, ItemType High, KDTree T, Comparator cmp);

// 创建数据
TElementType* CreateData(TElementType A, TElementType B);
// 创建节点
KDPosition CreateNode(KDPosition L, ItemType Item, KDPosition R);
// 返回节点P的高度
int Height(KDPosition P);
// // 打印节点的值
// void PrintNode(KDPosition Point);

// 在控制台打印树
// T : 要打印的树
// format : 元素的打印格式
// width : 元素的打印宽度
void TreePlot(KDTree T, char* format, int width);

// 树节点
struct KDNode
{
    ItemType Data;
    KDTree Left;
    KDTree Right;
};

#endif  // TREE_H
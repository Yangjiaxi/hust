#include <stdio.h>
#include <stdlib.h>
#include "../Tree/Tree.h"

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

typedef Tree AvlTree;
typedef TreeNode AvlNode;

typedef TPosition AvlPosition;
typedef TElementType AvlElementType;

AvlTree AvlInsert(AvlElementType X, AvlTree T);            //插入元素X
AvlTree AvlDelete(AvlElementType X, AvlTree T);            //删除元素X
static AvlPosition SingleRotateWithLeft(AvlPosition K2);   // insert LC->L，返回新的根
static AvlPosition SingleRotateWithRight(AvlPosition K2);  // insert RC->R，返回新的根
static AvlPosition DoubleRotateWithLeft(AvlPosition K3);   // insert LC->R，返回新的根
static AvlPosition DoubleRotateWithRight(AvlPosition K3);  // insert RC->L，返回新的根

#endif  // AVLTREE_AVLTREE_H
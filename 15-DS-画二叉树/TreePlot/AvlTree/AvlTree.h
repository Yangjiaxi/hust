#include <stdio.h>
#include <stdlib.h>
#include "../Tree/Tree.h"

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

typedef Tree AvlTree;
typedef TreeNode AvlNode;

AvlTree Insert(int X, AvlTree T);                    //插入元素X
AvlTree Delete(int X, AvlTree T);                    //删除元素X
static Position SingleRotateWithLeft(Position K2);   // insert LC->L，返回新的根
static Position SingleRotateWithRight(Position K2);  // insert RC->R，返回新的根
static Position DoubleRotateWithLeft(Position K3);   // insert LC->R，返回新的根
static Position DoubleRotateWithRight(Position K3);  // insert RC->L，返回新的根

#endif  // AVLTREE_AVLTREE_H
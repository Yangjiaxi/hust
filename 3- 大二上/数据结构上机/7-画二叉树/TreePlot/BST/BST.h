#ifndef BINARYSEARCHTREE_TREE_H
#define BINARYSEARCHTREE_TREE_H

#include "../Tree/Tree.h"

typedef Tree SearchTree;

SearchTree Insert(int X, SearchTree T);  //插入值为X的节点
SearchTree Delete(int X, SearchTree T);  //删除树中值为X的节点

#endif  // BINARYSEARCHTREE_TREE_H
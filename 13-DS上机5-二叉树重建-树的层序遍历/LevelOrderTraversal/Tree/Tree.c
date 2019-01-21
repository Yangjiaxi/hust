#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Queue/Queue.h"
#include "../Utils/Utils.h"

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
// 获取节点的高度
int Height(TPosition P)
{
    if (!P)
    {
        return 0;
    }
    return Max(Height(P->Left), Height(P->Right)) + 1;
}
// 创建节点
TPosition CreateNode(TPosition L, TElementType X, TPosition R)
{
    TPosition node = malloc(sizeof(TreeNode));
    if (node == NULL)
    {
        printf("[FATAL ERROR] Out of memory!\n");
        exit(-1);
    }
    node->Element = X;
    node->Left = L;
    node->Right = R;
    return node;
}

//在树T中寻找元素X的位置，并返回指向节点的指针，未找到返回NULL
TPosition Find(TElementType X, Tree T)
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
TPosition FindMin(Tree T)
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

TPosition FindMax(Tree T)  //寻找树中最大元素（不使用递归）
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

TPosition CastPtrToTreeNode(void* ptr)
{
    return (Tree)ptr;
}

// void LevelTreeWalk(Tree T)
// {
//     Queue Q = InitQueue(NULL);
//     InsertLast(T, Q);
//     Tree Tmp = NULL;
//     while (!IsQueueEmpty(Q))
//     {
//         Tmp = CastPtrToTreeNode(RemoveFirst(Q));
//         printf("%c ", Tmp->Element);
//         if (Tmp->Left != NULL)
//             InsertLast(Tmp->Left, Q);
//         if (Tmp->Right != NULL)
//             InsertLast(Tmp->Right, Q);
//     }
//     DeleteQueue(Q);
// }

Tree InPreBuild(const char* InOrder, const char* PreOrder)
{
    char Root = PreOrder[0];
    int RootIdx = FindChar(InOrder, Root);
    int Left_n = RootIdx;
    int Right_n = strlen(InOrder) - RootIdx - 1;
    Tree LeftTree = NULL;
    Tree RightTree = NULL;
    if (Left_n > 0)
    {
        char* Left_In = StrCopy(InOrder, Left_n);
        char* Left_Pre = StrCopy(&PreOrder[1], Left_n);
        if (strlen(Left_In) > 1)
            LeftTree = InPreBuild(Left_In, Left_Pre);
        else
            LeftTree = CreateNode(NULL, Left_Pre[0], NULL);
        free(Left_In);
        free(Left_Pre);
    }
    if (Right_n > 0)
    {
        char* Right_In = StrCopy(&InOrder[RootIdx + 1], Right_n);
        char* Right_Pre = StrCopy(&PreOrder[RootIdx + 1], Right_n);
        if (strlen(Right_In) > 1)
            RightTree = InPreBuild(Right_In, Right_Pre);
        else
            RightTree = CreateNode(NULL, Right_Pre[0], NULL);
        free(Right_In);
        free(Right_Pre);
    }
    return CreateNode(LeftTree, Root, RightTree);
}

Tree InPostBuild(const char* InOrder, const char* PostOrder)
{
    char Root = PostOrder[strlen(PostOrder) - 1];
    int RootIdx = FindChar(InOrder, Root);
    int Left_n = RootIdx;
    int Right_n = strlen(InOrder) - RootIdx - 1;
    Tree LeftTree = NULL;
    Tree RightTree = NULL;
    if (Left_n > 0)
    {
        char* Left_In = StrCopy(InOrder, Left_n);
        char* Left_Post = StrCopy(PostOrder, Left_n);
        if (strlen(Left_In) > 1)
            LeftTree = InPostBuild(Left_In, Left_Post);
        else
            LeftTree = CreateNode(NULL, Left_Post[0], NULL);
        free(Left_In);
        free(Left_Post);
    }
    if (Right_n > 0)
    {
        char* Right_In = StrCopy(&InOrder[RootIdx + 1], Right_n);
        char* Right_Post = StrCopy(&PostOrder[RootIdx], Right_n);
        if (strlen(Right_In) > 1)
            RightTree = InPostBuild(Right_In, Right_Post);
        else
            RightTree = CreateNode(NULL, Right_Post[0], NULL);
        free(Right_In);
        free(Right_Post);
    }
    return CreateNode(LeftTree, Root, RightTree);
}

// 根据InOrder提取LevelOrder
char* FixLevel(const char* LevelOrder, const char* InOrder)
{
    int size = strlen(InOrder);
    char* res = malloc(sizeof(char) * (size + 1));
    int cnt = 0;
    int LO_len = strlen(LevelOrder);
    for (int i = 0; i < LO_len; i++)
    {
        if (FindChar(InOrder, LevelOrder[i]) != -1)
        {
            res[cnt++] = LevelOrder[i];
        }
    }
    res[cnt] = '\0';
    return res;
}

Tree InLevelBuild(const char* InOrder, const char* LevelOrder)
{
    char Root = LevelOrder[0];
    int RootIdx = FindChar(InOrder, Root);
    int Left_n = RootIdx;
    int Right_n = strlen(InOrder) - RootIdx - 1;
    Tree LeftTree = NULL;
    Tree RightTree = NULL;
    if (Left_n > 0)
    {
        char* Left_In = StrCopy(InOrder, Left_n);
        char* Left_Level = FixLevel(LevelOrder, Left_In);
        if (strlen(Left_In) > 1)
        {
            LeftTree = InLevelBuild(Left_In, Left_Level);
        }
        else
            LeftTree = CreateNode(NULL, Left_Level[0], NULL);
        free(Left_In);
        free(Left_Level);
    }

    if (Right_n > 0)
    {
        char* Right_In = StrCopy(&InOrder[RootIdx + 1], Right_n);
        char* Right_Level = FixLevel(LevelOrder, Right_In);
        if (strlen(Right_In) > 1)
        {
            RightTree = InLevelBuild(Right_In, Right_Level);
        }
        else
            RightTree = CreateNode(NULL, Right_Level[0], NULL);
        free(Right_In);
        free(Right_Level);
    }
    return CreateNode(LeftTree, Root, RightTree);
}

// T : 树T
// is_left : 是否是左子树
// offset : 在偏移量offset处打印，对于
// depth : 当前深度depth
// buffer :  保存结果的二维数组
int PrintElement(Tree T, int is_left, int offset, int depth, char* format, int width, char** buffer)
{
    char b[20];
    memset(b, 0, sizeof(b));
    if (!T)
        return 0;

    sprintf(b, format, T->Element);

    // 得到左子树的总宽度
    int left = PrintElement(T->Left, 1, offset, depth + 1, format, width, buffer);
    // 右子树的总宽度
    int right = PrintElement(T->Right, 0, offset + left + width, depth + 1, format, width, buffer);

    // 当左右子树都处理完成时
    // 开始处理根节点 与 节点之间的连接线

    // 1. 根节点上的元素
    // 元素在buffer数组中的偶数行
    // 纵坐标从左子树最右边+1开始写(因为数组内下标从0开始)
    for (int i = 0; i < width; i++)
        buffer[2 * depth][offset + left + i] = b[i];

    if (depth)  // 不是根节点
    {
        // 在当前元素中心位置的上一行画'+'
        buffer[2 * depth - 1][offset + left + width / 2] = '+';
        if (is_left)  // 是左子树
        {
            for (int i = 1; i < width + right; i++)
                buffer[2 * depth - 1][offset + left + width / 2 + i] = '-';
            // 从左子树根的中心位置推测其父节点的中心位置
            buffer[2 * depth - 1][offset + left + width + right + width / 2] = '+';
        }
        else  // 是右子树
        {
            for (int i = 0; i < left + width - 1; i++)
                buffer[2 * depth - 1][offset - width / 2 + i] = '-';
            // 从右子树根的中心位置推测其父节点的中心位置
            buffer[2 * depth - 1][offset - width / 2 - 1] = '+';
        }
    }

    return left + width + right;
}

static int max(int a, int b)
{
    return a > b ? a : b;
}

void TreePlot(Tree T, char* format, int width)
{
    int ConsoleWidth = GetConsoleWidth();
    int TreeHeight = 2 * Height(T) - 1;
    AlignPrint(ConsoleWidth, '-', "Print : Tree Plot");
    printf("Print Lines : %d, Console Width : %d", TreeHeight, ConsoleWidth);
    endl();

    char** s = malloc(sizeof(char*) * TreeHeight);
    for (int i = 0; i < TreeHeight; i++)
    {
        s[i] = malloc(sizeof(char) * ConsoleWidth);
        memset(s[i], ' ', sizeof(char) * ConsoleWidth);
        s[i][ConsoleWidth - 1] = '\0';
    }

    int FinalWidth = PrintElement(T, 0, 0, 0, format, width, s);
    printf("final width: %d\n", FinalWidth);
    if (FinalWidth > ConsoleWidth)
    {
        AlignPrint(ConsoleWidth, '-',
                   "WARNING : Current console CANNOT show enough characters, tree may looks "
                   "werid, scale console and try again");
    }

    for (int i = 0; i < TreeHeight; i++)
        printf("%s\n", s[i]);
    for (int i = 0; i < TreeHeight; i++)
        free(s[i]);
    free(s);
    endl();
    AlignPrint(ConsoleWidth, '-', "End");
}
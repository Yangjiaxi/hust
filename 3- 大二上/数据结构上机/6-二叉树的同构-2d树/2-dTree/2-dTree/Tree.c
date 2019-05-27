#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utils/Utils.h"

void PrintData(ItemType Data)
{
    printf("<%03d, %03d>", Data[0], Data[1]);
}

KDTree MakeEmpty(KDTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return T;
}

int Height(KDPosition P)
{
    if (!P)
    {
        return 0;
    }
    return Max(Height(P->Left), Height(P->Right)) + 1;
}

TElementType* CreateData(TElementType A, TElementType B)
{
    TElementType* aT = malloc(sizeof(ItemType));
    aT[0] = A;
    aT[1] = B;
    return aT;
}

KDPosition CreateNode(KDPosition L, ItemType Item, KDPosition R)
{
    KDPosition node = malloc(sizeof(struct KDNode));
    if (node == NULL)
    {
        Fatal("[FATAL ERROR] Out of memory!\n");
    }
    node->Data[0] = Item[0];
    node->Data[1] = Item[1];
    node->Left = L;
    node->Right = R;
    free(Item);
    return node;
}

KDTree InsertRec(ItemType Item, KDTree T, int Level, Comparator cmp)
{
    if (T == NULL)
    {
        T = CreateNode(NULL, Item, NULL);
    }
    else if (cmp(Item[Level], T->Data[Level]) <= 0)
        T->Left = InsertRec(Item, T->Left, !Level, cmp);
    else
        T->Right = InsertRec(Item, T->Right, !Level, cmp);
    return T;
}

KDTree TreeInsert(ItemType Item, KDTree T, Comparator cmp)
{
    return InsertRec(Item, T, 0, cmp);
}

static void FindRec(ItemType Low, ItemType High, KDTree T, int Level, Comparator cmp)
{
    if (T != NULL)
    {
        if (cmp(Low[0], T->Data[0]) <= 0 && cmp(T->Data[0], High[0]) <= 0 &&
            cmp(Low[1], T->Data[1]) <= 0 && cmp(T->Data[1], High[1]) <= 0)
        {
            PrintData(T->Data);
            endl();
        }

        if (cmp(Low[Level], T->Data[Level]) <= 0)
            FindRec(Low, High, T->Left, !Level, cmp);
        if (cmp(High[Level], T->Data[Level]) >= 0)
            FindRec(Low, High, T->Right, !Level, cmp);
    }
}

void FindAndPrint(ItemType Low, ItemType High, KDTree T, Comparator cmp)
{
    printf("Query X where \t");
    PrintData(Low);
    printf("   <= X <=   ");
    PrintData(High);
    printf(" : \n");
    FindRec(Low, High, T, 0, cmp);
}

// T : 树T
// is_left : 是否是左子树
// offset : 在偏移量offset处打印，对于
// depth : 当前深度depth
// buffer :  保存结果的二维数组
int PrintElement(KDTree T,
                 int is_left,
                 int offset,
                 int depth,
                 char* format,
                 int width,
                 char** buffer)
{
    char b[20];
    memset(b, 0, sizeof(b));
    if (!T)
        return 0;

    sprintf(b, format, T->Data[0], T->Data[1]);
    unsigned len_b = strlen(b);

    // 得到左子树的总宽度
    int left = PrintElement(T->Left, 1, offset, depth + 1, format, width, buffer);
    // 右子树的总宽度
    int right = PrintElement(T->Right, 0, offset + left + width, depth + 1, format, width, buffer);

    // 当左右子树都处理完成时
    // 开始处理根节点 与 节点之间的连接线

    // 1. 根节点上的元素
    // 元素在buffer数组中的偶数行
    // 纵坐标从左子树最右边+1开始写(因为数组内下标从0开始)
    int pad_left = (width - (len_b)) / 2;
    for (int i = 0; i < len_b; i++)
        buffer[2 * depth][offset + left + i + pad_left] = b[i];

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

void TreePlot(KDTree T, char* format, int width)
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
                   "WARNING : Current console CANNOT show enough characters, "
                   "tree may looks "
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
#include "TreePlot.h"
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "UsefulFunc.h"
#include "stdio.h"

// T : 树T
// is_left : 是否是左子树
// offset : 在偏移量offset处打印，对于
// depth : 当前深度depth
// buffer :  保存结果的二维数组
int PrintElement(Tree T, int is_left, int offset, int depth, char** buffer)
{
    char b[20];
    memset(b, 0, sizeof(b));
    int width = 3;
    if (!T)
        return 0;

    sprintf(b, "[%c]", T->Element);

    // 得到左子树的总宽度
    int left = PrintElement(T->Left, 1, offset, depth + 1, buffer);
    // 右子树的总宽度
    int right = PrintElement(T->Right, 0, offset + left + width, depth + 1, buffer);

    // 当左右子树都处理完成时
    // 开始处理根节点(准确的说，子树的根)与节点之间的连接线

    // 1. 根节点上的元素
    // 元素在buffer数组中的偶数行
    // 纵坐标从左子树最右边+1开始写
    for (int i = 0; i < width; i++)
        buffer[2 * depth][offset + left + i] = b[i];

    // 2. 连接线，简单的模拟算法
    if (depth)  // 不是根节点
    {
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

int TreeHeight(Tree T)
{
    if (!T)
    {
        return 0;
    }
    return Max(TreeHeight(T->Left), TreeHeight(T->Right)) + 1;
}

void TreePlot(Tree T)
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int ConsoleWidth = w.ws_col;
    int Height = 2 * TreeHeight(T) - 1;
    AlignPrint(ConsoleWidth, '-', "Print : Tree Plot");
    printf("Print Lines : %d\nConsole Width : %d", Height, ConsoleWidth);
    endl();

    char** s = malloc(sizeof(char*) * Height);
    for (int i = 0; i < Height; i++)
    {
        s[i] = malloc(sizeof(char) * ConsoleWidth);
        memset(s[i], ' ', sizeof(char) * ConsoleWidth);
        s[i][ConsoleWidth - 1] = '\0';
    }

    int FinalWidth = PrintElement(T, 0, 0, 0, s);
    printf("Final Width : %d\n", FinalWidth);
    if (FinalWidth > ConsoleWidth)
    {
        AlignPrint(ConsoleWidth, '-',
                   "WARNING : Current console CANNOT show enough characters, tree may looks "
                   "werid, scale console and try again");
    }

    for (int i = 0; i < Height; i++)
        printf("%s\n", s[i]);
    for (int i = 0; i < Height; i++)
        free(s[i]);
    free(s);
    endl();
    AlignPrint(ConsoleWidth, '-', "End");
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RadixSort.h"
#include "timer.h"

/*
    测试方法：
        1. 基数与数组长度测试
            base    in  [2, 50]
            size    in  [10, 100, 1000, 10000, 100000]
            max     =   10000
            绘制len(size)条曲线
            期望：类似反函数的曲线
            理由:
                T(N) = O(Log_base{P}*(Size+Base))
                在size较大时base+size~size
                T(N) = O(Log_base{P}*Size)
                T(N) = O(Ln{P} * size/Ln{base})
                    1.  当size固定时，T(N) ~ 1 / Ln{Base}
                        由数学知识可知，f(x)=1/ln(x)的图像
                        与反比例函数图像相似
                    2. 当base固定时, T(N) ~ size，为直线
        2. 最大元素测试
            base    =   10
            size    in  [10, 100, 1000, ..., 100000]
            max     in  [10, 100, 1000, ..., 100000]
            绘制len(size)条曲线
            期望：趋势log_10{max}，也就是几个不同的平台，而且平台越来越高
            理由：
                设最大元素为P，P的位数在base进制下为Log_base{P}
                位数即为排序总趟数，在其他条件不变的情况下，
                执行时间与位数成正比关系,
                T = K * d
                d = Log_base{P}
                T = K * Log_base{P} = K * Ln{P}
                故执行时间与最大元素呈对数关系
        3. 数组有序性测试
            先将一个数组排序
            对有序数组重复1000次，记录时间
            使用相同参数，不预先排序，记录时间
            绘制 次-时间(预排序) 曲线
            绘制 次-时间(无预排序) 曲线
            期望：两曲线重合
            base    =   10
            size    in  [10, 100, 1000, ..., 1000000]
            max     =   100000

        ## 1.   所有实验在程序内重复1000次，使时间撑开
        ## 2.   所有实验在使用Python调用时也重复1000次，
        ##      并计算平均时间，以减小偶然误差
*/

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        printf(
            "[ERROR] Argument length : %d"
            "\nExpect :\n"
            "\tSORTED=0/1 BASE LENGTH MAX \n"
            "\te.g.\t ... 0 16 1000 100\n",
            argc);
        return 0;
    }
    int mth = atoi(argv[1]);  // 是否对已排序数组进行排序测试，0-否，1-是
    int base = atoi(argv[2]);  // 基数
    int size = atoi(argv[3]);  // 数组规模
    int max = atoi(argv[4]);   // 数组最大值
    int min = 1;
    int* Ori = ArrRandInit(size, min, max);
    // int* A = MakeEmptyArray(size);
    // CopyArray(A, Ori, size);
    // PrintArray(A, size);
    int* A = MakeEmptyArray(size);
    int* B = MakeEmptyArray(size);
    // int* B;
    unsigned long timer = 0;  // 计时器
    _TIME_INIT
    switch (mth)
    {
        case 0:
        {
            for (int i = 0; i < 1000; i++)
            {
                CopyArray(A, Ori, size);  // 原始数据复制进A
                // PrintArray(Ori, size);
                _TIME_START
                // 算法开始
                // int* B = RadixSort(A, B, size, base);
                RadixSort(A, B, size, base);
                // PrintArray(B, size);
                timer += _TIME_END;
            }
            break;
        }
        case 1:
        {
            // PrintArray(Ori, size);
            CopyArray(Ori, RadixSort(Ori, B, size, base), size);
            // PrintArray(Ori, size);
            for (int i = 0; i < 1000; i++)
            {
                _TIME_START
                CopyArray(A, Ori, size);  // 原始数据复制进A
                // PrintArray(Ori, size);
                _TIME_START
                // 算法开始
                // int* B = RadixSort(A, B, size, base);
                RadixSort(A, B, size, base);
                // PrintArray(B, size);
                timer += _TIME_END;
            }
            break;
        }
        default:
        {
            printf("[ERROR] paramater error, please refer to source code!\n");
            break;
        }
    }
    printf("%ld\n", timer);
    // int* B = RadixSort(A, size, base);
    // PrintArray(B, size);
    return 0;
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.c"

long double power_2_rec(long double x, int n)
{
    if (0 == n)
        return 1;
    if (1 == n)
        return x;
    if (n & 1)
        return power_2_rec(x * x, n >> 1) * x;
    else
        return power_2_rec(x * x, n >> 1);
}

long double power_3_rec(long double x, int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (n == 2)
        return x * x;
    if (n % 3 == 0)
        return power_3_rec(x * x * x, n / 3);
    if (n % 3 == 1)
        return power_3_rec(x * x * x, n / 3) * x;
    else
        return power_3_rec(x * x * x, n / 3) * x * x;
}

long double power_2(int x, int n)
{
    long double res = 1;
    long double base = x;
    while (n)
    {
        if (n & 1)
        {
            res *= base;
        }
        n >>= 1;
        base *= base;
    }
    return res;
}

long double power_3(int x, int n)
{
    long double res = 1;
    long double base = x;
    while (n)
    {
        if (n % 3 == 1)
        {
            res *= base;
        }
        if (n % 3 == 2)
        {
            res *= base * base;
        }
        n /= 3;
        base *= base * base;
    }
    return res;
}

int main(int argc, char **argv)
{
    _TIME_INIT
    int a = 2;
    int b = atoi(argv[1]);
    char mtd = argv[2][0];
    _TIME_START
    for (int i = 0; i < 100000; i++)
    {
        switch (mtd)
        {
        case '1':
            power_2(a, b);
            break;
        case '2':
            power_3(a, b);
            break;
        case '3':
            power_2_rec(a, b);
            break;
        case '4':
            power_3_rec(a, b);
            break;
        }
    }
    _TIME_END
    return 0;
}
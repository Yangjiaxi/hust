#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.c"

long long sum(int n)
{
    // if (n < 0)
    // {
    //     exit(1);
    // }
    // else if (n <= 1)
    // {
    //     return n;
    // }
    // return n + sum(n - 1);
    long long res = 0;
    for (int i = 1; i <= n; i++)
    {
        res += i;
    }
    return res;
}
int main(int argc, char **argv)
{
    _TIME_INIT
    int size = atoi(argv[1]);
    char mtd = argv[2][0];
    _TIME_START
    sum(size);
    _TIME_END
    return 0;
}
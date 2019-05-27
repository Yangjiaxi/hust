#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.c"

long double pizza(int n)
{
    if (n == 1)
    {
        return 2;
    }
    return n + pizza(n - 1);
}

int main(int argc, char **argv)
{
    _TIME_INIT
    int size = atoi(argv[1]);
    char mtd = argv[2][0];
    _TIME_START
    // printf("%.0Lf\n", pizza(80000));
    pizza(size);
    _TIME_END
    return 0;
}
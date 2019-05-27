#include "UsefulFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void endl()
{
    printf("\n");
}

char* StrConcat(const char* s1, char* s2)
{
    const size_t len1 = strlen(s1);
    if (!s2)
        s2 = "No Name";
    const size_t len2 = strlen(s2);
    char* result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

void AlignPrint(int width, char pad, const char* text)
{
    // printf("\n");
    int t_len = strlen(text) + 4;
    int l = (width - t_len + 1) / 2;
    for (int i = 1; i <= l; i++)
        printf("%c", pad);
    width -= l;
    printf("[ %s ]", text);
    width -= t_len;
    for (int i = 1; i <= width; i++)
        printf("%c", pad);
    printf("\n");
}
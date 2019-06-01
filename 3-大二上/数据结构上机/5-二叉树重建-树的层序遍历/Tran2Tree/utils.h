/*
    Some useful functions
*/

#ifndef USEFUL_FUNC_H
#define USEFUL_FUNC_H

// 连接字符串，使用后需要free
char* StrConcat(const char* s1, char* s2);
// 输出"[ $text ]"，并用pad在两侧填充至宽度为width
void AlignPrint(int width, char pad, const char* text);
// 换行
void endl();
// 在str中寻找字母ch首次出现的下标，没找到则返回-1
int FindChar(const char* str, char ch);
// 从str开始拷贝size个元素，返回指针，需要使用后free
char* StrCopy(const char* str, int size);
// 获取控制台宽度
int GetConsoleWidth();
// 比大小
int Max(int a, int b);

#endif  // USEFUL_FUNC_H

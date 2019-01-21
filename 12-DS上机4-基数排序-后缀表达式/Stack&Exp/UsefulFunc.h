#ifndef USEFUL_FUNC_H
#define USEFUL_FUNC_H

// 连接字符串，使用后需要free
char* StrConcat(const char* s1, char* s2);
// 输出"[$text]"，并用pad在两侧填充至宽度为width
void AlignPrint(int width, char pad, const char* text);

#endif  // USEFUL_FUNC_H
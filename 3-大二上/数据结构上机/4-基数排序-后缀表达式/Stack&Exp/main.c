#include <stdio.h>
#include "UsefulFunc.h"
#include "expression.h"

int main()
{
    // char* expr = "a + (b + [c * d) + e]";
    // char* expr = "a + b * c + (d * e + f) * g";
    char* expr = "{(a + b) / [c + d * (e - f)]} - g * (h + i * j)";

    // 输出信息
    AlignPrint(44, '-', "Input String:");
    printf("%s", expr);
    AlignPrint(44, '-', "END");

    // 预处理
    Expression LNR = ExprFix(expr);
    PrintList(LNR, "After Fix and Parse as List");

    // 检查合法性并转换为后缀表达式
    if (ExprPairCheck(LNR))
    {
        Expression LRN = LNRToLRN(LNR);
        PrintList(LRN, "Convert to Postfix Expression");
    }
    else
        printf("[ERROR] input error, bracket not match!\n");
    return 0;
}
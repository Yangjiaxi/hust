#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "list_ptr.h"

typedef List Expression;
typedef PtrToNode Unit;

typedef char Bool;
#define false 0
#define true 1

#define LEVEL_NUMBER 0
#define LEVEL_ONES 1      // 加减
#define LEVEL_MULTS 2     // 乘除
#define LEVEL_BRACKET 10  // 括号

#define BRACKET_BORDER 10  // 括号的分割级，小于10都是左括号，大于10都是右括号

/*
    do :
        1. ExprFix
        2. ExprPairCheck
        3. LNRToLRN
*/

// 修复字符串，删除空格，并转换为链表形式
Expression ExprFix(char* C);

// 中缀表达式转后缀表达式
Expression LNRToLRN(Expression LNR);

// 检查括号合法性
Bool ExprPairCheck(Expression expr);

//检查符号是否是括号并返回括号的属性数字
int BracketLevel(char c);

// 返回元素的优先级
int UnitLevel(char c);

#endif  // EXPRESSION_H
#include "expression.h"
#include <stdio.h>
#include <string.h>
#include "stack.h"

Expression ExprFix(char* C)
{
    int length = strlen(C);
    Expression LNR = InitList(NULL);
    Unit cursor = Header(LNR);
    for (int i = 0; i < length; i++)
    {
        if (C[i] != ' ')
        {
            cursor = InsertAfter(C[i], LNR, cursor);
        }
    }
    return LNR;
}

int BracketLevel(char c)
{
    switch (c)
    {
        case '{':
            return 1;
        case '[':
            return 2;
        case '(':
            return 3;
        case '}':
            return 1 + BRACKET_BORDER;
        case ']':
            return 2 + BRACKET_BORDER;
        case ')':
            return 3 + BRACKET_BORDER;
    }
    return 0;
}

Bool ExprPairCheck(Expression expr)
{
    Bool status = true;
    Stack check = InitStack(NULL);
    Unit cursor = FirstElement(expr);
    char current;
    char compare;
    int level;
    while (cursor)
    {
        current = Retrieve(cursor);
        level = BracketLevel(current);
        if (level)  // 是括号
        {
            if (level < BRACKET_BORDER)  // 左括号
                Push(current, check);
            else  // 右括号
            {
                if (IsEmpty(check))
                    return false;
                else
                {
                    compare = Pop(check);
                    if (level - BracketLevel(compare) != BRACKET_BORDER)
                        return false;
                }
            }
        }
        cursor = Advance(cursor);
    }

    return IsEmpty(check) ? true : false;
}

Expression LNRToLRN(Expression LNR)
{
    Expression LRN = InitList(NULL);
    Unit Pori = FirstElement(LNR);
    Unit Pres = Header(LRN);
    Stack stack = InitStack(NULL);
    char data;
    int level;
    while (Pori)
    {
        // PrintStack(stack);
        data = Retrieve(Pori);
        level = UnitLevel(data);
        if (level == LEVEL_NUMBER)  // 是数字，直接送进结果
            Pres = InsertAfter(data, LRN, Pres);
        else  // 不是数字
        {
            if (level != LEVEL_BRACKET)  // 不是括号
            {
                // 符号栈为空 或 栈顶为括号(相当于压入左括号后开辟了一个子栈)，
                // 直接入栈
                if (IsEmpty(stack) || UnitLevel(Top(stack)) == LEVEL_BRACKET)
                {
                    Push(data, stack);
                }
                // 当前元素优先级高于栈顶元素，直接入栈
                // 相当于当前表达式还未完成
                else if (level > UnitLevel(Top(stack)))
                {
                    Push(data, stack);
                }
                // 当前元素优先级小于或等于栈顶元素
                else
                {
                    while (1)
                    {
                        // 遇到左括号，说明之前的子表达式完成
                        if (IsEmpty(stack) || BracketLevel(Top(stack)))
                        {
                            Push(data, stack);
                            break;
                        }
                        // 优先级较大(相当于完成了一个子表达式)
                        else if (level > UnitLevel(Top(stack)))
                        {
                            Push(data, stack);
                            break;
                        }
                        // 优先级小于栈顶元素，栈顶元素出栈并进入结果
                        // 说明栈顶符号与其连接的两个元素为子表达式
                        else
                        {
                            Pres = InsertAfter(Pop(stack), LRN, Pres);
                        }
                    }
                }
            }
            else  // 为括号
            {
                // 是左括号，直接入栈
                if (BracketLevel(data) < BRACKET_BORDER)
                {
                    Push(data, stack);
                }
                // 是右括号，pop直到栈顶为左括号
                else
                {
                    while (1)
                    {
                        // 遇到左括号，停止pop
                        if (UnitLevel(Top(stack)) == LEVEL_BRACKET &&
                            BracketLevel(Top(stack)) < BRACKET_BORDER)
                        {
                            Pop(stack);
                            break;
                        }
                        // pop并直接进入结果
                        else
                        {
                            Pres = InsertAfter(Pop(stack), LRN, Pres);
                        }
                    }
                }
            }
        }
        Pori = Advance(Pori);
    }
    // 将剩余操作符全部pop进结果
    while (!IsEmpty(stack))
    {
        Pres = InsertAfter(Pop(stack), LRN, Pres);
    }
    return LRN;
}

int UnitLevel(char c)
{
    switch (c)
    {
        case '+':
        case '-':
            return LEVEL_ONES;
        case '*':
        case '/':
            return LEVEL_MULTS;
    }
    if (BracketLevel(c))
        return LEVEL_BRACKET;

    return LEVEL_NUMBER;
}

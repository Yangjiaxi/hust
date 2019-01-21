#include <stdio.h>
#include "list_ptr.h"
#include "Polynomial.h"

int main()
{
    List Poly1 = NULL;
    List Poly2 = NULL;
    List Poly3 = NULL;
    List Poly4 = NULL;
    Poly1 = InitList(Poly1);
    Poly2 = InitList(Poly2);
    Poly3 = InitList(Poly3);
    Poly4 = InitList(Poly4);
    Position tmp;

    tmp = Poly1;
    tmp = InsertAfter(2, 5, Poly1, tmp);
    tmp = InsertAfter(1, 3, Poly1, tmp);
    tmp = InsertAfter(0, 6, Poly1, tmp);

    tmp = Poly3;
    tmp = InsertAfter(0, 6, Poly3, tmp);
    tmp = InsertAfter(2, 5, Poly3, tmp);
    tmp = InsertAfter(1, 3, Poly3, tmp);

    tmp = Poly2;
    tmp = InsertAfter(3, 3, Poly2, tmp);
    tmp = InsertAfter(2, 5, Poly2, tmp);
    tmp = InsertAfter(0, 7, Poly2, tmp);

    tmp = Poly4;
    tmp = InsertAfter(2, 5, Poly4, tmp);
    tmp = InsertAfter(0, 7, Poly4, tmp);
    tmp = InsertAfter(3, 3, Poly4, tmp);

// ----------------------------------------------
    printf("1. Mutiply of Exp-Sorted Polynomial:\n");
    printf("Multiply of \n");
    PrintPolynomial(Poly1);
    printf("and\n");
    PrintPolynomial(Poly2);
    printf("is:\n");
    List result_1 = NULL;
    result_1 = InitList(result_1);
    MultPolynomial_Sorted(Poly1, Poly2, result_1);
    PrintPolynomial(result_1);

// ----------------------------------------------
    printf("----------------------------------------------\n");
    printf("2. Mutiply of Non-Sorted Polynomial:\n");
    printf("Multiply of \n");
    PrintPolynomial(Poly3);
    printf("and\n");
    PrintPolynomial(Poly4);
    printf("is:\n");
    List result_2 = NULL;
    result_2 = InitList(result_2);
    MultPolynomial(Poly3, Poly4, result_2);
    PrintPolynomial(result_2);

    return 0;
}
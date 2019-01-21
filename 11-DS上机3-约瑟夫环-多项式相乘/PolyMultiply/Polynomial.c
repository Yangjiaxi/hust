//
// Created by VanYang on 2018/12/3.
//

#include "Polynomial.h"

void PrintUnit(Item P)
{
    printf("(%d) * x^[%d]", P->coef, P->exp);
}

void PrintPolynomial(const Polynomial Poly)
{
    Item P;
    P = Poly->next;
    printf("\t");
    while (P != NULL)
    {
        PrintUnit(P);
        P = P->next;
        if (P != NULL)
        {
            printf(" + ");
        }
    }
    printf("\n");
}

void MultPolynomial(Polynomial Poly1, Polynomial Poly2, Polynomial Res)
{
    Item p1 = FirstElement(Poly1);      // Pointer to Poly1
    Item p2 = NULL;                     // Pointer to Poly2
    Item tmp = NULL;                    // Tmp pointer, for Insert() to Res
    int Coef = 0;                       // Multiply of two items' coef
    int Exp;                            // Sum of two items' exp
    while (p1)                          // for each Item in Poly1
    {
        p2 = FirstElement(Poly2);       // Reset pointer p2, which point to Poly2
        while (p2)                      // for each item in Poly2, do p1 * item
        {
            Coef = p1->coef * p2->coef;
            Exp = p1->exp + p2->exp;
            p2 = Advance(p2);
            tmp = FindByExp(Exp, Res);  // Does this Exp already exist?
            if (tmp)                    // -> yes, add to its coef
            {
                tmp->coef += Coef;
            }
            else                        // -> no, create one
            {
                InsertAfter(Exp, Coef, Res, Res);
            }
        }
        p1 = Advance(p1);
    }
}

void MultPolynomial_Sorted(const Polynomial Poly1, const Polynomial Poly2, Polynomial Res)
{
    // both Poly1 and Poly2 is sorted, the very first elements' exp is the highest
    int MaxExp = FirstElement(Poly1)->exp + FirstElement(Poly2)->exp;
    InverseList(Poly2);     // inverse Poly2, will explain later
    Item p1 = NULL;
    Item p2 = NULL;
    Item pres = Header(Res);
    int CoefSum = 0;
    /*
     * ALGORITHM -- Multiply of two exponential-sorted polynomials
     *     0. !!!IMPORTANT!!!   two polynomials are DESCENDING order
     *     1. get the highest exp of result,
     *          -> this can be done by sum up two first elements
     *     2. reverse Poly2
     *          -> Poly1 : DESCENDING order
     *          -> Poly2 : ASCENDING order
     *     3. from MaxExp down to 0, do:
     *         a. find all pairs whose exp1+exp2 is i
     *             I. when exp1+exp2 == i
     *                 -> move both pointer one step
     *             II. when exp1+exp2 < i
     *                 -> move p2(point to Poly2, ascending order) one step
     *                 -> only this way can enlarge exp1+exp2
     *             III. when exp1+exp2 > i
     *                 -> move p1(point to Poly1, descending order) one step
     *                 -> only this way can shrink exp1+exp2
     *         b. add to result
     *             -> exist, just add up
     *             -> otherwise, create
     */
    for (int i = MaxExp; i >= 0; i--)
    {
        p1 = FirstElement(Poly1);
        p2 = FirstElement(Poly2);
        while (p1 && p1->exp > i)
            p1 = Advance(p1);
        while (p1 && p2 && p1->exp + p2->exp < i)
            p2 = Advance(p2);
        while (p1 && p2)
        {
            if (p1->exp + p2->exp == i)
            {
                CoefSum += p1->coef * p2->coef;
                p1 = Advance(p1);
                p2 = Advance(p2);
            }
            else
            {
                if (p1->exp + p2->exp < i)
                    p2 = Advance(p2);
                else
                    p1 = Advance(p1);
            }
        }
        if (CoefSum != 0)
        {
            pres = InsertAfter(i, CoefSum, Res, pres);
            CoefSum = 0;
        }
    }
    InverseList(Poly2);
}



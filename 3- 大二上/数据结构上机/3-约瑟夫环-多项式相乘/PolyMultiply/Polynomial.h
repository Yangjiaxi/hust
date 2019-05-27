//
// Created by VanYang on 2018/12/3.
//

#ifndef POLYMULTIPLY_POLYNOMIAL_H
#define POLYMULTIPLY_POLYNOMIAL_H

#include <stdio.h>
#include "list_ptr.h"

typedef List Polynomial;
typedef PtrToNode Item;

void PrintUnit(Item P);

void MultPolynomial(Polynomial Poly1, Polynomial Poly2, Polynomial Res);

void MultPolynomial_Sorted(Polynomial Poly1, Polynomial Poly2, Polynomial Res);

void PrintPolynomial(Polynomial Poly);


#endif //POLYMULTIPLY_POLYNOMIAL_H

// K1_0809-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

const double Epsilon = 1e-3;

int main() {
	double cur = 1, prev = 0, tmpPrev, t, a, c1, c2, first = 1;
	// Postavlja se na 1, da ne bi u prvom koraku bio gotov
	//
	printf("unesite korak simulacije ");
	scanf_s("%lf", &t);
	printf("unesite ubrznje tela ");
	scanf_s("%lf", &a);
	printf("unesite koeficijente otpora C1 C2 ");
	scanf_s("%lf%lf", &c1, &c2);

	while (((cur - prev) > Epsilon) || ((prev - cur) >  Epsilon)) {
		tmpPrev = cur;
		cur = prev + a * t - c1 * prev - c2 * prev * prev;
		if (first) {
			first = 0;
			prev = 0;
		}
		else prev = tmpPrev;
	}
	printf("Maksimalna brzina je %lf", cur);
}


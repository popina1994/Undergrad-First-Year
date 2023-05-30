// K1_0607-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

const int nMax = 12, numQuart = 4;

double quart[numQuart];

int main() {
	int i, sale, j = 0;
	memset(quart, 0, sizeof(quart));
	for (i = 0; i < nMax; i++) {
		scanf_s("%d", &sale);
		j = i / 3;
		quart[j] += sale;
	}
	double maxSale = 0;
	int indMax = -1;
	for (i = 0; i < numQuart; i ++)
		if (quart[i] / 3> maxSale) {
			indMax = i;
			maxSale = quart[i] / 3;
		}
	printf("Maksimalna prodja je %.0lf u %d kvartalu", maxSale, indMax + 1);
	return 0;
}


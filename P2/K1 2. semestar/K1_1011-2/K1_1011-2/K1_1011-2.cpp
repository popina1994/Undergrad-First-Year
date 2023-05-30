// K1_1011-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
const int NumOfMonth = 12, NumOfQuart = 4, LenOfQuart = NumOfMonth / NumOfQuart;

int main() {
	int temp[NumOfMonth], i, kraj = 1, indMin, indMax;
	double quart[NumOfQuart], min, max;

	for (i = 0; i < NumOfMonth; i++)
		scanf_s("%d", &temp[i]);
	for (i = 0; i < NumOfMonth; i++) if (temp[i] != 0) kraj = 0;

	while (!kraj) {
		memset(quart, 0, sizeof(quart));

		for (i = 0; i < NumOfMonth; i++) {
			quart[i / LenOfQuart] += temp[i];
			if ((i + 1) % LenOfQuart == 0)
				quart[i / LenOfQuart] /= LenOfQuart;
		}
		
		min = INT_MAX; max = INT_MIN; indMin = -1; indMax = -1;
		for (i = 0; i < NumOfQuart; i++) {
			if (quart[i] <= min) {	min = quart[i]; indMin = i; }
			if (quart[i] >= max) {	max = quart[i];	indMax = i;	}
		}

		printf("Najveca prosecna je u kvartalu %d a ona je %.3lf\n", indMax, max);
		printf("Najmanja prosecna je u kvartalu %d a ona je %.3lf\n", indMin, min);
		for (i = 0; i < NumOfMonth; i++)
			scanf_s("%d", &temp[i]);
		kraj = 1;
		for (i = 0; i < NumOfMonth; i++) if (temp[i] != 0) kraj = 0;
	}
		
}


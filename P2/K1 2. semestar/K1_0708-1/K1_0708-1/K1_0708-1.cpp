// K1_0708-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

const int naMax = 20, nbMax = 10;

double a[naMax], b[nbMax];

int main() {
	int i, j, na, nb;
	printf("unesite broj elemenata niza a");
	scanf_s("%d", &na);

	for (i = 0; i < na; i++)
		scanf_s("%lf", &a[i]);
	scanf_s("%d", &nb);
	
	bool increase = true;
	for (i = 0; i < nb; i++)
		scanf_s("%lf", &b[i]);
	for (i = 1; i < nb; i++)
		if (b[i] <= b[i - 1]) {
			increase = false;
			break;
		}

	if (!increase)
		("Nije rastuci");
	else 
		for (i = 0; i < na; i++) {
			if (a[i] < b[0])
				printf("-1");
				else if (a[i] > b[nb - 1])
					printf("%d", nb - 1);
				else for (j = 0; j < nb - 1; j++)
						if ((a[i] >= b[j]) && (a[i] < b[j + 1]))
							printf("%d", j);
		}
}


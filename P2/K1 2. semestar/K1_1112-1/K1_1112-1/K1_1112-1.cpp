// K1_1112-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int tc, tu, i;
	double x, y;
	
	srand((unsigned )time(NULL));

	scanf_s("%d", &tu);
	while (tu >= 0) {
		tc = 0;
		for (i = 0; i < tu; i++) {
			x = (double)rand() / RAND_MAX;
			y = (double)rand() / RAND_MAX;
			if ((x * x + y * y) < 1) tc++;
		}
		printf("pi je %.10lf", 4 * (double)tc / tu);
		scanf_s("%d", &tu);
	}
	return 0;
}


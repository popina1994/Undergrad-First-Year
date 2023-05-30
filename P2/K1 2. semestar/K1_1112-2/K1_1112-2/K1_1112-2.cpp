// K1_1112-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS 0
const int MaxNumStudent = 100, MinMark = 5, NumOfMarks = 6;

int main() {
	double x[MaxNumStudent], avg = 0, devitation = 0, mark[NumOfMarks];
	int n, i;
	
	printf("unesite broj studentata");
	scanf("%d", &n);
	
	for (i = 0; i < n; i++) {
		scanf("%lf", &x[i]);
		avg += x[i];
	}
	avg /= n;

	for (i = 0; i < n; i++)
		devitation += (x[i] - avg) * (x[i] - avg);
	devitation /= n;
	devitation = sqrt(devitation);

	memset(mark, 0, sizeof(mark));
	for (i = 0; i < n; i++) {
		if (x[i] <= 50)
			mark[5 - MinMark] ++;
		else if (x[i] <= 60)
			mark[6 - MinMark] ++;
		else if (x[i] <= 70)
			mark[7 - MinMark] ++;
		else if (x[i] <= 80)
			mark[8 - MinMark] ++;
		else if (x[i] <= 90)
			mark[9 - MinMark] ++;
		else mark[10 - MinMark] ++;
	}
	for (i = 0; i < NumOfMarks; i++)
		printf("ocenu %d ima %.3lf procenat ucenika\n", i + MinMark, (double)mark[i] * 100 / n);
	printf("prosecan broj poena je %.3lf odstupanje je %.3lf\n", avg, devitation);
	return 0;
}

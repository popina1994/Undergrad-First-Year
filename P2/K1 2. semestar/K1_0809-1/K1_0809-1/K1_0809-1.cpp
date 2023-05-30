// K1_0809-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

const int NumDay = 7, LenMax = 13, NumMonth = 12, DaysInYear = 365, BeginYear = 2009; 
const char day[NumDay][LenMax] = { "Cetvrtak", "Petak", "Subota", "Nedelja", "Ponedeljak", "Utorak", "Sreda" };
const int month[NumMonth] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main() {
	int d, m, g, fromFirst = 0;
	
	printf("unesite datum");
	scanf_s("%d%d%d", &d, &m, &g);
	
	while (g >= 2009) {
		for (int i = 0; i < g - BeginYear; i++) fromFirst += DaysInYear;
		for (int i = 0; i < m - 1; i++) fromFirst += month[i];
		fromFirst += d - 1;
		printf("%s", day[fromFirst % NumDay]);
		scanf_s("%d%d%d", &d, &m, &g);
	}
}


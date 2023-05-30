// K1_0708-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

const int numMonth = 12;

int main() {
	int d1, m1, d2, m2, fromFirst1 = 0, fromFirst2 = 0, i,
		month[numMonth] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	printf("unesite prvi datum");
	scanf_s("%d%d", &d1, &m1);
	printf("unesite drugi datum");
	scanf_s("%d", &d2, &m2);
	
	for (i = 0; i < m1 - 1; i++) fromFirst1 += month[i];
	fromFirst1 += d1;
	for (i = 0; i < m2 - 1; i++) fromFirst2 += month[i];
	fromFirst2 += d2;
	if ((fromFirst1 - fromFirst2 == 10) || (fromFirst2 - fromFirst1 == 10))
		printf("Razlikuju se za 10");
	else printf("Ne razlikuju se za 10");

}


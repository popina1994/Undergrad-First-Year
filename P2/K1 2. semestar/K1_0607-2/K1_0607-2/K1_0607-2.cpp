// K1_0607-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <limits.h>

const int shortLen = 16;

int main() {
	unsigned short x;
	int binPalindrom = 1, i;
	scanf_s("%hu", &x);
	for (i = 0; i < shortLen / 2; i++) {
		if ((x & (1 << i)) != (x & (1 << (16 - i + 1))))
			binPalindrom = 0;
	}
	if (binPalindrom)
		printf("DA");
	else printf("NE");
}


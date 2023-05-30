// K1_0910-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

int main() {
	int a, b, tmpA, tmpB, c;
	scanf_s("%d%d", &a, &b);

	if ((a <= 0) || (b <= 0))
		printf("Kuku Lele, pa sta uradi crni Djordje");
	else {
		tmpA = a; tmpB = b; c = a % b;

		while (c != 0) {
			tmpA = tmpB;
			tmpB = c;
			c = tmpA % tmpB;
		}
		printf("%d %d", a / tmpB, b / tmpB);
	}
}
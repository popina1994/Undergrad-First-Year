// K1_1011-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

const int randBegin = 10, randEnd = 10000;

int main() {
	int randomNum, a = 1, b = 1, c, isFib = 0;
	
	srand((unsigned)time(NULL));
	randomNum = (double)rand() / RAND_MAX * (randEnd - randBegin) + randBegin;
	c = a + b;

	while (c < randomNum) {
		a = b;
		b = c;
		c = a + b;
	}
	
	if ((randomNum == 1) || (randomNum == c))
		printf("Fibonacijev");
	else printf("Nije Fibonacijev");
}

// K1_0910-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int nMax = 100, MaxNumGuess = 10;

int rand100() {
	srand((unsigned)time(NULL));
	return (double) rand() / RAND_MAX * (nMax - 1) + 1;
}

int main() {
	int numGuess = 0, trie, randomNum, guess = 0;
	randomNum = rand100();

	while (numGuess < MaxNumGuess) {
		printf("unesite broj");
		scanf_s("%d", &trie);
		numGuess++;

		if (trie > randomNum)
			printf("broj je manji");
		else if (trie < randomNum)
			printf("broj je veci");
		else { guess = 1; break;}
		if (!guess)
			printf(" ostalo vam je %d ", MaxNumGuess - numGuess);
	}

	if (!guess)
		printf("BUUUDALA");
	else printf("Pogodili ste nakon %d pokusaja", numGuess);
}


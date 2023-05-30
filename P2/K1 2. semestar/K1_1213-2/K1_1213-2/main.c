
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define NumMax 100

int main() {
	int x[NumMax], i, rastuci, opadajuci, n, bitSek;
	printf("unesite broj elemenata niza");
	scanf("%d", &n);
	while (n > 0 && n <= NumMax) {
		
		for (i = 0; i < n; i++) {
			printf("unesite vrednost");
			scanf("%d", &x[i]);
			
			while (x[i] < 0 && x[i] > 50){
				printf("unesite ponovo element\n");
				scanf("%d", &x[i]);
			}
		}
		
		bitSek = 0; rastuci = 0; opadajuci = 0;
		for (i = 0; i < n - 1; i++)	if (x[i] >= x[i + 1]) break;
		if (i < n - 1 && i > 0) rastuci = 1;
		
		for (; i < n - 1; i++) if (x[i] < x[i + 1]) break;
		if (i == n - 1)	opadajuci = 1;
		
		if (rastuci && opadajuci) bitSek = 1;

		rastuci = 0; opadajuci = 0;
		for (i = 0; i < n - 1; i++)	if (x[i] <= x[i + 1]) break;
		if (i < n - 1 && i > 0) opadajuci = 1;

		for (; i < n - 1; i++) if (x[i] >= x[i + 1]) break;
		if (i == n - 1)	rastuci = 1;

		if (rastuci && opadajuci) bitSek = 1;
		if (bitSek)
			printf("Bitonicka sekvenca");
		else printf("Nije Bitonicka sekvenca");
		
		printf("unesite broj elemenata niza");
		scanf("%d", &n);
		
	}
}
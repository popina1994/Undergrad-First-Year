#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXDUZ 100

int main() {
	int x[MAXDUZ], pow[MAXDUZ], i, n, j, k;
	
	printf("unesite duzinu niza");
	scanf("%d", &n);

	while (n > 0 && n <= MAXDUZ){

		for (i = 0; i < n; i++) {
			printf("unesite elemenet");
			scanf("%d", &x[i]);

			while (x[i] <= 0) {
				printf("unesite ponovo");
				scanf("%d", &x[i]);
			}
		}
		
		for (i = 0; i < n; i++) {
			printf("%d = ", x[i]);

			for (j = 0; j < MAXDUZ; j++)
				pow[j] = 0;

			for (j = 0; x[i] > 0; x[i] /= 2)
				pow[j++] = x[i] % 2;
			for (k = j - 1; k >= 0; k--)
				if (pow[k]) printf("2^%d + ", k);
			printf("\n");
		}

		printf("unesite duzinu niza\n");
		scanf("%d", &n);
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define DUZMAX 100

int main() {
	int n, i, j, k, a[DUZMAX], b[DUZMAX];


	printf("unesite duzine nizova");
	scanf("%d", &n);
	while 	(n > 0 && n <= DUZMAX) {

		printf("unesite niz a\n");
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		printf("unesite niz b\n");
		for (i = 0; i < n; i++)
			scanf("%d", &b[i]);

		for (i = 0; i < n; i++) {
			int rotacija = 1;

			for (j = i; j < i + n; j++)
				if (b[j % n] != a[j - i]) {
					rotacija = 0;
					break;
				}

			if (rotacija) {
				printf("Niz A:");
				for (k = 0; k < n; k++) printf("%d ", a[k]);
				printf("\n");

				printf("Niz B");
				for (k = 0; k < n; k++) printf("%d ", b[k]);
				printf("\n");

				printf("Niz A se dobija rotacijom niza B za %d mesta udesno", n - i);
			}
		}
		printf("unesite duzine nizova");
		scanf("%d", &n);
	}

	return 0;
}
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int binToInt(int* arr, int n) {
	int dec = 0, cnt, pow = 1;
	for (cnt = n - 1; cnt >= 0; cnt--) {
		dec += arr[cnt] * pow;
		pow *= 2;
	}
	return dec;
}

int main() {
	int *arr, n, cnt;

	printf("unesite duzinu niza");
	scanf("%d", &n);

	while (n > 0) {
		printf("unesite brojeve");
		arr = (int*) calloc(n, sizeof(int));
		
		if (arr == NULL) {
			printf("Neuspela alokacija");
			break;
		}
		else for (cnt = 0; cnt < n; cnt++)
			scanf("%d", &arr[cnt]);
		printf("Decimalni broj je %d", binToInt(arr, n));

		printf("unesite duzinu niza");
		scanf("%d", &n);
	}


}
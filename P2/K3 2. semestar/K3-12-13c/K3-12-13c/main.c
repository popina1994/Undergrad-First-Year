#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tacka {
	double x, y;
} Tacka;

double Distance(Tacka *x, Tacka *y) {
	return sqrt(pow((y->x - x->x), 2) + pow((x->y - y->y), 2));
}

double DistanceMax(Tacka *x, int n, int *i, int *j) {
	double max = -1;
	int cnt1, cnt2, iCur = -1, jCur = -1;

	for (cnt1 = 0; cnt1 < n - 1; cnt1++)
		for (cnt2 = cnt1 + 1; cnt2 < n; cnt2++)
			if (Distance(x + cnt1, x + cnt2) > max) {
				max = Distance(x + cnt1, x + cnt2);
				iCur = cnt1;
				jCur = cnt2;
			}
	*i = iCur; *j = jCur;
	return max;
}

int main() {
	int n, cnt, i, j;
	Tacka *x;

	printf("Unesite broj tacaka\n");
	scanf("%d", &n);
	x = (Tacka*)malloc(n * sizeof(Tacka));
	for (cnt = 0; cnt < n; cnt++)
		scanf("%lf %lf", &x[cnt].x, &x[cnt].y);
	printf("Maksimalno rastojanje je %lf izmedju tacaka sa rednim brojem ", DistanceMax(x, n, &i, &j));
	printf("%d %d", i, j);
	free(x);
	system("pause");
	return 0;
}
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double GeomSrVr(int **x, int row, int col) {
	int cnt;
	double sr = 1;
	for (cnt = 0; cnt < col; cnt++) {
		sr *= pow(x[row][cnt], 1.0 / col);
	}
	return sr;
}



int main() {
	int **x, numRow, numCol, cnt, maxIndex, cntRow, cntCol;
	double maxGsr;

	printf("unesite dimenzije matrice\n");
	scanf("%d %d", &numRow, &numCol);

	// alokacija
	x = (int**)calloc(numRow, sizeof(int*));
	if (x == NULL) {
		printf("Neuspela alokacija");
		exit(1);
	}
	for (cnt = 0; cnt < numRow; cnt++) {
		x[cnt] = (int*)calloc(numCol, sizeof(int));
		if (x[cnt] == NULL) {
			printf("Neuspela alokacija");
			exit(1);
		}
	}
	
	//ucitavanje matrice
	printf("unesite matricu'\n");
	for (cntRow = 0; cntRow < numRow; cntRow++)
		for (cntCol = 0; cntCol < numCol; cntCol++)
			scanf("%d", &x[cntRow][cntCol]);

	// nalazenje vrste sa najvecom geometrijskom sredinom
	maxGsr = 0;
	for (cnt = 0; cnt < numRow; cnt++)
		if (GeomSrVr(x, cnt, numCol) > maxGsr) {
			maxGsr = GeomSrVr(x, cnt, numCol);
			maxIndex = cnt;
		}

	//zamena vrsta
	for (cnt = 0; cnt < numCol; cnt++) {
		int tmp;
		tmp = x[0][cnt];
		x[0][cnt] = x[maxIndex][cnt];
		x[maxIndex][cnt] = tmp;
	}

	//ispis matrice
	for (cntRow = 0; cntRow < numRow; cntRow++){
		for (cntCol = 0; cntCol < numCol; cntCol++)
			printf("%d ", x[cntRow][cntCol]);
		printf("\n");
	}

	//dealokacija
	for (cnt = 0; cnt < numRow; cnt++)
		free(x[cnt]);
	free(x);
	return 0;
}
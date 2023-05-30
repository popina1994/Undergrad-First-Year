#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int numRow, numCol, cntRow, cntCol, **x, **y;
	double matrArSr = 0;

	printf("unesite dimenzije matrice");
	scanf("%d%d", &numRow, &numCol);
	
	//alokacija memorije
	x = (int*)calloc(numRow, sizeof(int*));
	if (x == NULL) {
		printf("neuspela alokacija");
		exit(1);
	}
	for (cntRow = 0; cntRow < numRow; cntRow++) {
		x[cntRow] = calloc(numCol, sizeof(int));
		if (x[cntRow] == NULL) {
			printf("FUCKING ERROR");
			exit(1);
		}
	}

	// unos matrice i racunanje aritmeticke sredine
	for (cntRow = 0; cntRow < numRow; cntRow++)
		for (cntCol = 0; cntCol < numCol; cntCol++) {
			scanf("%d", &x[cntRow][cntCol]);
			matrArSr += x[cntRow][cntCol];
		}
	matrArSr /= numRow * numCol;

	for (cntRow = 0; cntRow < numRow; cntRow++) {
		int arSr = 0;
		for (cntCol = 0; cntCol < numCol; cntCol++)
			arSr += x[cntRow][cntCol];
	}

	for (cntRow = 0; cntRow < numRow; cntRow++)
		free(x[cntRow]);
	free(x);
	


	return 0;
}
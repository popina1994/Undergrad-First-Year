// DZ1P2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MaxVektor = 100000;

typedef struct matrix {
	int numRow, numCol, defaultValue, x[MaxVektor];
} Matrix;

int AddresFunction(int row, int column) {
	if (((column - 1) * (column - 2) / 2 - row + 1) < MaxVektor) 
		return ((column - 1) * (column - 2) / 2 + row - 1);
	return -1;
}

int IsRegularIndex(Matrix *ptM, int row, int column) {
	if ((row > ptM->numRow) || (row < 1) || (column > ptM->numCol) || (column < 1)) return 0;

	return 1;
}

void MakeMatrix(Matrix *ptM) {
	int i, j;

	printf("unesite broj Kolona");
	scanf_s("%d", &ptM->numCol);
	ptM->numRow = ptM->numCol;

	if (AddresFunction(ptM->numRow - 1, ptM->numCol) == -1)
		printf("Greska u pravljenju, prevelike dimenzije trougaone matrice");
	else {
		printf("unesite podrazumevanu vrednost");
		scanf_s("%d", &ptM->defaultValue);
		for (i = 1; i <= ptM->numRow; i++)
			for (j = i + 1; j <= ptM->numCol; j++)
				scanf_s("%d", &ptM->x[AddresFunction(i, j)]);
		//Odredi adresnu funkciju u nizu, ucita novi element na to mesto u memoriji
	}
}

int GetElement(Matrix *ptM, int row, int column) {
	if (row >= column) return ptM->defaultValue;
	return ptM->x[AddresFunction(row, column)];
		
} 

int ChangeElement(Matrix *ptM, int row, int column) {
	int val;

	if (!IsRegularIndex(ptM, row, column) || column <= row)
	return 0;

	printf("unesite vrednost koju hocete\n");
	scanf_s("%d", &val);
	ptM->x[AddresFunction(row, column)] = val;
	return 1;
}

int main() {
	int choice, row, column;
	Matrix m;

	printf("Unesite 0 da izadjete iz programa\n1 Napravite matricu datih dimenzija\n");
	printf("2 Ako hocete da menjate vrednost\n");
	printf("3 Ako hocete da vidite vrednost\n");
	printf("4 Broj nepodrazumevanih elemenata\n");

	scanf_s("%d", &choice);

	while (choice != 0) {
		switch (choice) {
		case 1: MakeMatrix(&m);
			break;

		case 2: printf("unesite vrednosti vrste i kolone koje zelite da menjate\n");
			scanf_s("%d%d", &row, &column);
			if (ChangeElement(&m, row, column))
				printf("Uspela promena\n");
			else printf("Nije uspela promena\n");
			break;

		case 3: printf("unesite vrednosti vrste i kolone koje zelite da vidite\n");
			scanf_s("%d%d", &row, &column);
			if (IsRegularIndex(&m, row, column))
				printf("Vrednost je %d\n", GetElement(&m, row, column));
			else printf("Nepostojeci element\n");
			break;

		case 4: printf("Broj nepodrazumevanih elemenata je%d", m.numCol * (m.numCol - 1) / 2);
			break;

			default: printf("unesite ispravno");
				break;
		}
		printf("Unesite 0 da izadjete iz programa\n1 Napravite matricu datih dimenzija\n");
		printf("2 Ako hocete da menjate vrednost\n");
		printf("3 Ako hocete da vidite vrednost\n");
		printf("4 Broj nepodrazumevanih elemenata\n");
		scanf_s("%d", &choice);
	}
	return 0;
}
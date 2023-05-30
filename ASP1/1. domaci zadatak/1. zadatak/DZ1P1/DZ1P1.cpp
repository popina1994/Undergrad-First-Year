// DZ1P1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MaxNumberElement = 2;

typedef struct Node*PtNode;
typedef struct Stack *PtStack;

struct  Node {
	int info;
	PtNode next;
};

struct Stack {
	int numberElement;
	int maxNumberElement;
	PtNode begin;
};

int IsEmpty(PtStack ptStack) {
	if (ptStack->begin == NULL) return 1;
	return 0;
}

int Push(PtStack ptStack, int element) {
	PtNode tmpPtNode;

	if (ptStack->numberElement == ptStack->maxNumberElement)
		return 0;

	tmpPtNode = (PtNode)malloc(sizeof(Node));
	tmpPtNode->info = element;
	
	tmpPtNode->next = ptStack->begin;
	ptStack->begin = tmpPtNode;	
	ptStack->numberElement++;
	return 1;
}

int Pop(PtStack ptStack) {
	PtNode tmpPtNode;
	int tmp;

	tmpPtNode = ptStack->begin;
	ptStack->begin = ptStack->begin->next;
	tmp = tmpPtNode->info;
	free(tmpPtNode);
	ptStack->numberElement--;
	return tmp;
}

int Top(PtStack ptStack) {
	return ptStack->begin->info;
}

int NumberOfElements(PtStack ptStack) {
	return ptStack->numberElement;
}

void Empty(PtStack ptStack) {
	while (ptStack->begin)
		Pop(ptStack);
}

int MaxCapacity(PtStack ptStack) {
	return ptStack->maxNumberElement;
}

int main() {
	PtStack ptStack;
	int out = 0, tmp, choice;

	ptStack = (PtStack)malloc(sizeof(Stack));
	ptStack->begin = NULL; 
	ptStack->numberElement = 0;
	ptStack->maxNumberElement = MaxNumberElement;

	printf("Unesite 0 ako cete da izadjete\n 1 ako cete da stavite na stek\n 2 ako cete da vidite element na vrhu steka\n");
	printf(" 3 ako cete da skinete element i da ga uklonite\n 4 ako cete trenutni broj elementa na steku\n");
	printf(" 5 ako hocete maksimalni kapacitet steka\n");

	scanf_s("%d", &choice);

	while (choice != 0) {
		switch (choice) {
			case 0: out = 1; break;

			case 1: printf("unesite element"); scanf_s("%d", &tmp); 
				if (Push(ptStack, tmp))
					printf("Uspesno Dodavanje\n");
				else printf("Pun stek\n"); break;

			case 2: if (IsEmpty(ptStack))
						printf("Stek je prazan\n");
					else printf("Element na vrhue je %d\n", Top(ptStack)); break;

			case 3: if (IsEmpty(ptStack))
						printf("stek je prazan nema nista na vrhu\n");
					else printf("Element na vrhu je %d i uklonjen je \n", Pop(ptStack)); break;

			case 4: printf("Broj elemenata na steku je %d\n", NumberOfElements(ptStack)); break;

			case 5: printf("Maksimalni kapacitet steka je %d\n", MaxCapacity(ptStack)); break;

			default: printf("Unesite ponovo broj\n"); break;
		}

		printf("Unesite 0 ako cete da izadjete\n 1 ako cete da stavite na stek\n 2 ako cete da vidite element na vrhu steka\n");
		printf(" 3 ako cete da skinete element i da ga uklonite\n 4 ako cete trenutni broj elemensta na steku\n");
		printf(" 5 ako hocete maksimalni kapacitet steka\n");
		scanf_s("%d", &choice);
	}
	Empty(ptStack);
}

// U slucaju underflow program vraca -1 (problem je ako se ubaci element -1, ali to ostavljamo na ruke programeru)
// V2 Izbaceno

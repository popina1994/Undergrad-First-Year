#include "dz5.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int numArg, char *argS[]) {
	char *inputName1, *inputName2, *outputName;
	clock_t  tBegin, tEnd;
	NodePt list1 = NULL, list2 = NULL, list3 = NULL, newNode;

	newNode = (NodePt)malloc(sizeof(Node));

	if (numArg != 4) BadArgumentNum();
	
	inputName1 = argS[1]; inputName2 = argS[2];
	outputName = argS[3];

	printf("Pocetno vreme je "); PrintCurrentTime();
	tBegin = clock();
	
	ReadM3U(inputName1, &list1);
	ReadM3U(inputName2, &list2);

	Procc(list1, list2, &list3);

	WriteASX(outputName, list3);

	printf("Broj elemenata u listi Ulazna1 %d Ulazna2 %d Izlazna %d\n", NumNumber(list1), NumNumber(list2), NumNumber(list3));

	printf("Duzina nove liste %d\n", LengthPlaylist(list3));

	printf("Ime sa najvise naslova %s\n", NameMostNumera(list3));
	
	DeleteM3U(&list1); DeleteM3U(&list2);
	DeleteASX(&list3);

	tEnd = clock();
	printf("Krajnje vreme je "); PrintCurrentTime();

	printf("Vreme koje je utrosio procesor %lf", (double)(tEnd - tBegin) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}
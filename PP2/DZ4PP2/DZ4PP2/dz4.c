#include "dz4.h"
#include <stdio.h>

void OutputMenu(int *choice) {
	printf("Unesite sledece brojeve:\n");
	printf("0) Kraj rada\n");
	printf("1) Ucitavanje liste\n");
	printf("2) Dodavanje na kraj liste\n");
	printf("3) Dodavanje na pocetak liste\n");
	printf("4) Brisanje proizvoljnog elementa iz liste (ime se unosi)\n");
	printf("5) Ispis liste\n");
	printf("6) Brisanje liste\n");
	printf("7) Obrada liste\n");
	scanf("%d", choice);
	getchar();
}

int main() {
	int choice, n;
	NodePt list = NULL;
	char name[30];
	int start, finish, mass;

	OutputMenu(&choice);
	while (choice != 0) {
		switch (choice) {
		case 1: 
			printf("Unesite broj elemenata liste\n");
			scanf("%d", &n);
			DeleteList(&list); // brisi staru
			if (!InputList(&list, n)) printf("Greska u unosu liste\n"); // dodaj novu
			break;

		case 2: 
			printf("Unesite ime koje hocete da dodate na kraj\n");
			scanf("%s", &name);
			printf("Unesite masu\n");
			scanf("%d", &mass);
			printf("Pocetni sprat\n");
			scanf("%d", &start);
			printf("Krajnji sprat\n");
			scanf("%d", &finish);
			if (!PushBack(&list, name, mass, start, finish)) printf("Greska u dodavanju u listu\n");
			break;
		case 3:
			printf("Unesite ime koje hocete da dodate na pocetak\n");
			scanf("%s", &name);
			getchar();
			printf("Unesite masu\n");
			scanf("%d", &mass);
			printf("Pocetni sprat\n");
			scanf("%d", &start);
			printf("Krajnji sprat\n");
			scanf("%d", &finish);
			if (!PushFront(&list, name, mass, start, finish)) printf("Greska u dodavanju u listu\n");
			break;
		case 4: 
			printf("Unesite ime osobe koju cete da obrisete iz liste\n");
			scanf("%s", &name);
			Delete(&list, name);
			break;
		case 5:
			OutputList(list); break;
		case 6:
			DeleteList(&list); break;
		case 7: 
			printf("Unesite maksimalnu dozvoljenu masu\n");
			scanf("%d", &mass);
			printf("Unesite pocetni sprat\n");
			scanf("%d", &start);
			printf("Unesite krajnji sprat\n");
			scanf("%d", &finish);
			ListLoading(list, mass, start, finish);
			printf("Unesite 0 ako cete da prekinete simulaciju\n");
			scanf("%d", &choice);
			while (choice != 0) {
				ListLoading(list, mass, start, finish);
				printf("Unesite 0 ako cete da prekinete simulaciju\n");
				scanf("%d", &choice);
			}
			break;
			
		default:printf("Unesite ponovo izbor\n"); OutputMenu(&choice);
			break;
		}
		OutputMenu(&choice);
	}
	return 0;
}
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// proverava da li je karakter heksa
int HexChar(char c) {
	if ((c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'))
		return 1;
	return 0;
}

int ReadHex(char hexNum[], int *len) {
	char c;
	
	*len = 0;
	memset(hexNum, 0, sizeof(hexNum));
	c = getchar();

	while (c != ' ' && c != '\n')  {
		if (*len > 8) return 0;
		hexNum[(*len)++] = c;
		c = getchar();
	}
	return 1;
}

int IsGood(char hexNum[], int len) {
	while (len > 0) {
		if (!HexChar(hexNum[len - 1])) return 0;
		len--;
	}

	return 1;
}



void Prvi() {
	char hexNum[8];
	int len, cnt, dec = 0;

	if (!ReadHex(hexNum, &len)) {	printf("Neispravan\n"); return; }
	if (!IsGood(hexNum, len)) { printf("Neispravan\n"); return; }

	for (cnt = 0; cnt < len; cnt++)
		if (hexNum[cnt] <= '9')
			dec += dec * 16 + hexNum[cnt] - '0';
		else dec += dec * 16 + hexNum[cnt] - 'A' + 10;
		printf("Decimalna vrednost broja je: %d", dec);
}

typedef struct Node Node;

struct Node {
	char broj[20];
	int ponuda;
	Node *next;
};

void InitializeList(Node **list) {
	*list = NULL;
}

void Push(Node **list, const char broj[], const ponuda) {
	Node *newNode;

	if ((newNode = malloc(sizeof(Node))) == NULL) { fprintf(stderr, "Nema memorije\n"); exit(1); }
	
	strcpy(newNode->broj, broj);
	newNode->ponuda = ponuda;
	newNode->next = *list;
	*list = newNode;
}

void DeleteList(Node **list) {
	Node *tmpNode;

	while (*list != NULL) {
		tmpNode = *list;
		*list = (*list)->next;
		free(tmpNode);
	}
}

// vraca 1 ako postoji ista ponuda u listi
int Exist(Node *list, int ponuda) {
	int cnt = 0;

	while (list != NULL) {
		if (list->ponuda == ponuda)
			cnt++;
		list = list->next;
	}

	if (cnt >= 2)
		return 1;
	return 0;
}


void Drugi(){
	FILE *filePonude, *fileUcesnici;
	int minOffer = INT_MAX, curOffer, noOffer = 1, cnt = 0;
	char minNum[20], curNum[20], ime[20], prezime[20], broj[20];
	Node *list, *iterator;

	InitializeList(&list);

	// citanje iz datoteke
	if ((filePonude = fopen("ponude.txt", "r")) == NULL) { fprintf(stderr, "Greska pri otvaranju datoteke\n"); exit(1); };
	while (fscanf(filePonude, "%s%d", curNum, &curOffer) == 2) 
		Push(&list, curNum, curOffer);

	fclose(filePonude);

	for (iterator = list; iterator != NULL; iterator = iterator->next) {
		if (!Exist(list, iterator->ponuda) && iterator->ponuda < minOffer) {
			minOffer = iterator->ponuda;
			strcpy(minNum, iterator->broj);
			noOffer = 0;
		}
	}

	if ((fileUcesnici = fopen("ucesnici.txt", "r")) == NULL) { fprintf(stderr, "Greska pri otvaranju datoteke\n"); exit(1); }

	if (!noOffer)
		while ((fscanf(fileUcesnici, "%s%s%s", ime, prezime, broj)) == 3) {
			if (strcmp(broj, minNum) == 0) {
				printf("%s %s", ime, prezime);
				break;
			}
		}
	else printf("Nema pobednika\n");
	fclose(fileUcesnici);

	DeleteList(&list);
}



int main() {
	void(*func[2])() = { Prvi, Drugi };
	int choice;

	printf("Birajte koju cete funkciju\n");
	scanf("%d", &choice);

	if (choice != 1 && choice != 2) { fprintf(stderr, "SISAJ MAJMUNE\n"); exit(1); }

	func[choice - 1]();
	system("pause");

	return 0;
}
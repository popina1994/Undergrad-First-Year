#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Zapis{
	char ime[31], prezime[31];
	int godinaProizvodnje;
	char pogonsko;
	int godina;
	int regBroj;
} Zapis;

typedef struct Node Node;

typedef struct Node *NodePt;

struct Node {
	Zapis* info;
	NodePt next;
};

void InitializeList(NodePt *list) {
	*list = NULL;
}

void Push(NodePt *list, Zapis *ptZap) {
	NodePt newNode;
	
	if ((newNode = (NodePt)malloc(sizeof(Node))) == NULL) { fprintf(stderr, "HEAP te rastura\n"); exit(2); }
	newNode->info = ptZap;
	newNode->next = *list;
	*list = newNode;
}

void ReadNode(FILE *f, Zapis **ptPtZap) {
	if ((*ptPtZap = malloc(sizeof(Zapis))) == NULL) { fprintf(stderr, "HEAP ce te ubiti\n"); exit(2); }
	
	if (fread(*ptPtZap, sizeof(Zapis), 1, f) != 1) { fprintf(stderr, "KONJU JEDAN NAPRAVI DATOTEKU KAKO TREBA!\n"); exit(3); }
}

void DeleteList(NodePt *list) {
	NodePt tmp;
	while ((*list) != NULL) {
		tmp = *list;
		(*list) = (*list)->next;
		free(tmp);
	}
}

Zapis* TraziRegTabl(int regTabl, NodePt list) {
	while (list != NULL) 
		if (list->info->regBroj == regTabl)
			return list->info;
	return NULL;
}

int main() {
	FILE *in;
	Zapis *ptZap;
	NodePt list;

	in = fopen("vozila.dat", "r");
	if (in == NULL) { fprintf(stderr, "Greska u citanju\n"); exit(1); }
	
	InitializeList(&list);

	while (!feof(in)) {
		int godina, regTabl;
		ReadNode(in, &ptZap);
		if (ptZap->pogonsko == 'G') // pogonsko
			Push(&list, ptZap);
		else free(ptZap);

		printf("Unesite godinu dan i mesec\n");
		scanf("%d", &godina);
		printf("Unesite Broj registarskih tablica\n");
		scanf("%d", &regTabl);
		
		while (regTabl != 0) {
			ptZap = TraziRegTabl(regTabl, list);
			if ((ptZap != NULL) && (ptZap->godina / 100 % 100 > 24))
				printf("%s %s", ptZap->ime, ptZap->prezime);
		}
	}
	
	DeleteList(&list);

	fclose(in);
	
	return 0;
}
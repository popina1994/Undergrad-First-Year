#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_LENGTH 30
#define TENNIS_PLAYERS "teniseri.txt"
#define TOURNAMENT_INFO "wimbledon.txt"
#define NEW_ATP_LIST "atplista.txt"

typedef struct Teniser {
	int code, points;
	char name[NAME_LENGTH], surName[NAME_LENGTH];
} Teniser;


void PushList(FILE *f, Teniser **list) {
	Teniser *newNode;
	if ((newNode = (Teniser*)malloc(sizeof(Teniser))) == NULL) { fprintf(stderr, "Nedovoljno memorije"); exit(1); }
	if (fscanf(f, "%d", newNode->code);
	if 

}

void Prvi() {
	Teniser *list = NULL;
}

void Drugi() {

}

int main() {
	void(*ptFunction[2])() = { Prvi, Drugi };
	int choice;
	
	scanf("%d", &choice);
	getchar();
	ptFunction[choice]();
	system("pause");
	return 0;
}
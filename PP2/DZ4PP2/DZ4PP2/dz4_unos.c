#include "dz4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int InputList(NodePt* ptList, int numPersons) {
	int cnt;
	NodePt newNode ;

	*ptList = NULL;

	for (cnt = 0; cnt < numPersons; cnt++) {
		newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return 0;
		}
		// ucitavanje cvora liste
		printf("Unesite ime koje hocete da dodate\n");
		scanf("%s", &(newNode->name));
		printf("Unesite masu\n");
		scanf("%d", &(newNode->mass));
		printf("Pocetni sprat\n");
		scanf("%d", &(newNode->start));
		printf("Krajnji sprat\n");
		scanf("%d", &(newNode->finish));
		newNode->inElevator = 0; // nije u liftu
		newNode->reach = 0;
		newNode->next = NULL;
		
		newNode->next = *ptList; // novi cvor postaje prvi
		*ptList = newNode; 
	}
	return 1;
}

int PushBack(NodePt *ptList, char name[], int mass, int start, int finish) {
	NodePt newNode, end;
	// ucitavanje cvora liste
	newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		return 0;
	}
	strcpy(newNode->name, name);
	newNode->mass = mass;
	newNode->start = start;
	newNode->finish = finish;
	newNode->inElevator = 0; 
	newNode->reach = 0;
	newNode->next = NULL;

	if (*ptList == NULL) {
		newNode->next = *ptList; // novi cvor postaje prvi
		*ptList = newNode;
	}
	else  {
		end = *ptList;
		while (end->next != NULL) 
			end = end->next;
		end->next = newNode; // doda se na kraj
	}
	return 1;
}

int PushFront(NodePt *ptList, char name[], int mass, int start, int finish) {
	NodePt newNode;

	newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		return 0;
	}
	// ucitavanje cvora liste
	strcpy(newNode->name, name);
	newNode->mass = mass;
	newNode->start = start;
	newNode->finish = finish;
	newNode->inElevator = 0; // nije u liftu
	newNode->reach = 0;
	newNode->next = NULL;

	newNode->next = *ptList; // novi cvor postaje prvi
	*ptList = newNode;
	return 1;
}
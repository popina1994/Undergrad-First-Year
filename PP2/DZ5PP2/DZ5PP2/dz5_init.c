#include "dz5.h"
#include <time.h>

void BadArgumentNum(){
	printf("Los broj argumenata\n");
	exit(1);
}

void NotEnoughMemory() {
	printf("Nedovoljno memorije\n");
	exit(2);
}

void BadRead() {
	printf("Lose citanje datoteke\n");
	exit(3);
}

void BadWrite() {
	printf("Lose pisanje datoteke\n");
	exit(4);
}


void PrintCurrentTime() {
	time_t beginTime = time(NULL);
	struct tm* currentLocalTime = localtime(&beginTime);
	char* dateTimeString = calloc(100 + 1, sizeof(char));

	if (currentLocalTime && dateTimeString) {
		strftime(dateTimeString, 100, "%a%H:%M:%S", currentLocalTime);
		printf("%s\n", dateTimeString);
	}
	else NotEnoughMemory(); 
	free(dateTimeString);
}


void AddNode(NodePt *list, NodeSongPt songPt) {
	NodePt newNode;

	newNode = (NodePt)malloc(sizeof(Node));
	if (newNode == NULL) NotEnoughMemory();

	newNode->prev = NULL;
	newNode->song = songPt;
	newNode->next = *list;

	if (*list != NULL) 	// ako lista ima bar jedan element
		(*list)->prev = newNode;

	*list = newNode;
}


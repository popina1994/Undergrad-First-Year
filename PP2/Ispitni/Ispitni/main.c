#include "spisci.h"
#include <stdio.h>
#include <string.h>
#include <time.h>



void ErrorMemory() {
	fprintf(stderr, "Nedovoljno memorije\n"); exit(3);
}

void ErrorWriteFile() {
	fprintf(stderr, "Greska pri otvaranju\n"); exit(2);
}

void ErrorReadFile() {
	fprintf(stderr, "Greska pri citanju\n"); exit(1);
}

void PrintCurrentTime1() {
	time_t beginTime = time(NULL);
	struct tm* currentLocalTime = localtime(&beginTime);
	char* dateTimeString = calloc(100 + 1, sizeof(char));

	if (currentLocalTime && dateTimeString) {
		strftime(dateTimeString, 100, "%a%H:%M:%S", currentLocalTime);
		printf("%s\n", dateTimeString);
	}
	free(dateTimeString);
}


void PrintCurrentTime() {
	time_t beginTime = time(NULL);
	struct tm*  curTime= localtime(&beginTime);
	char *dateTimeString = calloc(101, sizeof(char));
	if (dateTimeString && curTime) {
		strftime(dateTimeString, 100, "%H:%M:%S", curTime);
		printf("%s\n", dateTimeString);
	}
	free(dateTimeString);
}

int main(int numArg, char *ArrStr[]) {
	NodePt list = NULL;
	clock_t clockBegin = clock();
	PrintCurrentTime();

	if (numArg != 3) { fprintf(stderr, "Pogresan broj argumenata\n"); }

	ReadFile(ArrStr[1], &list);
	WriteSTD(list);
	MakeTerm(ArrStr[2], list);
	DeleteList(&list);
	clock_t clockEnd = clock();
	PrintCurrentTime();
	printf("Proteklo vreme je %lf sekundi", (double)(clockEnd - clockBegin) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}
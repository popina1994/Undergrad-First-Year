#include "spisci.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// cita string iz datog fajla od date pozicije do prvog blanko znaka
char *ReadStr(FILE *f) {
	char *newStr, c;
	int len = 0;

	newStr = (char*)malloc(sizeof(char) * STEP);
	while ((c = fgetc(f)) != ' ') {
		if ((len + 1) % 10 == 0) {
			newStr = (char*)realloc(newStr, sizeof(char) * (len + 11));
			if (newStr == NULL) ErrorMemory();
		}
		newStr[len++] = c;
		newStr[len] = '\0';
	}
	return newStr;
}

Student *ReadStudent(FILE *f) {
	Student *newStudent;
	int lenName = 0, lenSurName = 0;

	newStudent = (Student*)malloc(sizeof(Student));
	if (newStudent == NULL) ErrorMemory();

	if (fscanf(f, "%s ", &newStudent->index) != 1) {
		free(newStudent);
		return NULL; // doslo do kraja datoteke
	}
	newStudent->name = ReadStr(f);
	newStudent->surName = ReadStr(f);

	fscanf(f, "%s\n", newStudent->division);

	return newStudent;
}

// pravi listu kao stek
void ReadFile(char *inFileName, NodePt *list) {
	NodePt newNode;
	Student *studentPt;
	FILE *in;

	if ((in = fopen(inFileName, "r")) == NULL) ErrorReadFile();
	
	while ((studentPt = ReadStudent(in)) != NULL) {
		if ((newNode = (NodePt)malloc(sizeof(Node))) == NULL) ErrorMemory();
		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->info = studentPt;

		newNode->next = *list;
		if (*list != NULL) 
			(*list)->prev = newNode;
		*list = newNode;
	}
	fclose(in);
}

char *ReadTerm(FILE *f) {
	char *s;
	if ((s = (char*)malloc((SHIT_MAX + 1) * sizeof(char))) == NULL) ErrorMemory();
	
	if (fscanf(f, "%s\n", s) != 1) return NULL; // nije dobro procitano

	return s;
}
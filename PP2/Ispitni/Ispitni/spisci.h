#ifndef _spisci_h_
#define _spisci_h_
#define _CRT_SECURE_NO_DEPRECATE

#define STEP 10 // za koliko se realocira memorija pri svakom koraku
#define T_MAX 100 // maksimalno vreme
#define SHIT_MAX 23
#define STUDENT_MAX 20
#define TERMIN_IME "term_"
#define TERMIN_EXT ".txt"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student {
	char *name, *surName, division[3], index[7];
} Student;


typedef struct Node Node;
typedef struct Node *NodePt;

struct Node {
	NodePt next, prev;
	Student *info;
};

void ErrorReadFile();

void ErrorWriteFile();

void ErrorMemory();

void ReadFile(char *inFileName, NodePt *list);

NodePt End(NodePt list);

void WriteSTD(NodePt list);

char *ReadTerm(FILE *f);

void WriteStudent(FILE *f, NodePt nodePt, int cnt);

void MakeTerm(char *raspTerm, NodePt list);

void DeleteList(NodePt *list);

#endif
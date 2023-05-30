#include "spisci.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

NodePt End(NodePt list) {
	if (list == NULL)
		return NULL;

	while (list->next != NULL)
		list = list->next;
	return list;
}

// pravi ime izlazne datoteke
char *OutName(int cnt) {
	int log10 = 0, tmpCnt = cnt;
	char *s;
	int maxLen;
	
	while (tmpCnt > 0) {
		tmpCnt /= 10;
		log10++;
	}
	if (cnt == 0) log10 = 1;
	tmpCnt = cnt;

	maxLen = strlen(TERMIN_EXT) + strlen(TERMIN_IME) + log10;

	if ((s = (char*)malloc(sizeof(char) * (maxLen + 1))) == NULL) ErrorMemory();
	s[0] = '\0';
	s = strcat(s, TERMIN_IME);

	for (cnt = log10 - 1; cnt >= 0; cnt--) {
		s[cnt + strlen(TERMIN_IME)] = tmpCnt % 10 + '0';
		tmpCnt /= 10;
	}

	for (cnt = strlen(TERMIN_IME) + log10; cnt < maxLen; cnt++)
		s[cnt] = TERMIN_EXT[cnt - strlen(TERMIN_IME) - log10];

	s[maxLen] = '\0';
	return s;
}

// rasporedjuje studente po terminima
void MakeTerm(char *raspTerm, NodePt list) {
	FILE *in, *out, *outCnt;
	char *s, *outName;
	int cnt = 0, // broji broj termina
		cntStudent;
	NodePt end = End(list);

	if ((in = fopen(raspTerm, "r")) == NULL) ErrorReadFile();
	if ((out = fopen("termini.txt", "w")) == NULL) ErrorWriteFile();

	for (cnt = 0; (s = ReadTerm(in)) != NULL; cnt++) {
		outName = OutName(cnt);
		if (((outCnt = fopen(outName, "w"))) == NULL) ErrorWriteFile();
		if (end == NULL)
			fprintf(outCnt, "%s", outName); // ne pises termin
		else {
			fprintf(out, "%s\n", s); 
			fprintf(outCnt, "%s\n", s);
			for (cntStudent = 0; cntStudent < STUDENT_MAX && end != NULL; cntStudent++) {
				WriteStudent(outCnt, end, cntStudent);
				end = end->prev;
			}
		}
		fclose(outCnt);
		free(outName);
	}
	fclose(in);
	fclose(out);
}

void DeleteList(NodePt *list) {
	NodePt tmpNode;
	while (*list != NULL)  {
		tmpNode = *list;
		*list = (*list)->next;
		free(tmpNode->info->name); 
		free(tmpNode->info->surName);
		free(tmpNode);
	}
}


#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define STEP 10
#define REG_LEN 6
#define EMPTY_STR ""

// vraca ime iz fajla
char *ReadStrFile(FILE *f) {
	char *str = NULL, c;
	int len = 0;

	str = (char*)malloc(sizeof(char) * STEP);
	str[len] = '\0';

	while ((c = getc(f)) != '\n') {
		if ((len + 1) % STEP == 0)
			str = realloc(str, sizeof(char) * (len + STEP + 1));
		str[len++] = c;
		str[len] = '\0';
	}

	return str;
}

// vraca koliko je presao automobil sa datim registarskim tablicama
int RoadPassed(char RegTabSearch[]) {
	FILE *in;
	char RegTab[REG_LEN + 1];
	int i, len;

	if ((in = fopen("putovanja.txt", "r")) == NULL) { fprintf(stderr, "Greska u citanju\n"); exit(1); }
	
	while (in, fscanf(in, "%d-%d-%d %s %d\n", &i, &i, &i, &RegTab, &len) == 5) 
		if (strcmp(RegTabSearch, RegTab) == 0) {
			fclose(in);
			return len;
		}

	fclose(in);
	return -1; // nije naslo registarsku tablicu
}

void Prvi() {
	FILE *in;
	char regTabl[REG_LEN + 1], *name, *nameMax = NULL, *nameMin = NULL; // maksimalna i minimalna duzina koju su automobili presli
	int maxLen = INT_MIN, minLen = INT_MAX, len, change; // duzine koje su automobili presli

	if ((in = fopen("automobili.txt", "r")) == NULL) { fprintf(stderr, "Greska pri otvaranju datoteke\n"); exit(1); }
	
	while (fscanf(in, "%s ", regTabl) == 1) {
		name = ReadStrFile(in);
		if ((len = RoadPassed(regTabl)) != -1) { // duzina automobila koji se obradjuje
			change = 0;
			if (len > maxLen) {
				change = 1;
				maxLen = len;
				if (nameMax != NULL && nameMin != NULL && strcmp(nameMax, nameMin) != 0) free(nameMax); 
				nameMax = name;
			}
			if (len < minLen) {
				change = 1;
				minLen = len;
				if (nameMax != NULL && nameMin != NULL && strcmp(nameMin, nameMax) != 0) free(nameMin);
				nameMin = name;
			}
			if (!change) free(name); // mrzelo me ozbiljnije da razmisljam	
		}
	}

	fclose(in);

	printf("Najmanji %s %d\n", nameMin, minLen);
	printf("Najveci %s %d\n", nameMax, maxLen);
	free(nameMin);
	free(nameMax);
}

void LoadStr(char *s) {
	unsigned int len = strlen(s), cnt;
	char last = ' ';

	for (cnt = 0; cnt < len; cnt++) {
		if (s[cnt] != ' ' && last == ' ') {
			cnt++;
			if (cnt < len && s[cnt] >= 'A' && s[cnt] <= 'Z')
				s[cnt] = s[cnt] - 'A' + 'a'; // veliko u 
		}
		last = s[cnt];
	}
}


void Drugi() {
	char *s;
	
	s = ReadStrFile(stdin);
	while (strcmp(s, EMPTY_STR) != 0) {
		LoadStr(s);
		printf("%s", s);
		s = ReadStrFile(stdin);
	}
}

	
int main() {
	void(*ptF[2])() = { Prvi, Drugi};
	int choice;

	printf("Koji zadatak hocete\n");
	scanf("%d", &choice);
	getchar();
	ptF[choice - 1]();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123465789 .", END[] = "dosta Brus Li";

//cita sa ulaza string dok ne dodje do /n
char *ReadStr() {
	char *s = NULL, c;
	int len = 0;
	len = 0;

	s = realloc(s, (len + 1) * sizeof(char));
	if (s == NULL) {
		printf("Neuspesna alokacija");
		exit(1);
	}
	s[len] = '\0';

	while ((c = getchar()) != '\n') { // ciklus koji cita string
		len++;
		s = realloc(s, (len + 1) * sizeof(char));
		if (s == NULL) {
			printf("Neuspesna alokacija");
			exit(1);
		}

		s[len - 1] = c;
		s[len] = '\0';
	}
	return s;
}

//vraca simbol iz alfabeta
int Symbol(char c) {
	int cnt ;
	for (cnt = 0; cnt < strlen(ALPHABET); cnt++)
		if (ALPHABET[cnt] == c)
			return cnt;
}

int main() {
	char *s = NULL, *sKey = NULL, *sCopy = NULL, c;
	int len, lenKey, cnt;
	
	while (1) { // ciklus koji ide dok ne dodje do dosta Brus Li

		printf("Unesite kljuc\n");
		sKey = ReadStr();

		printf("unesite string koji cete da sifrujete\n");
		s = ReadStr();

		if (strcmp(s, END) == 0) // kraj
			break;

		len = strlen(s);
		lenKey = strlen(sKey);

		sCopy = malloc(sizeof(char)* (strlen(s) + 1));
		if (sCopy == NULL) {
			printf("Neuspesna alokacija");
			exit(1);
		}

		for (cnt = 0; cnt < len; cnt++)  {
			int val = s[cnt], valKey = sKey[cnt % lenKey], valMod, symVal, symKey;

			symVal = Symbol(val); symKey = Symbol(valKey);
			valMod = (symVal + symKey) % 64;

			printf("%2d    %c %2d ", cnt, s[cnt], symVal); // prve 3 kolone
			printf("%c %2d ", sKey[cnt % lenKey], symKey); // druge dve kolone
			printf("%2d %c\n", valMod, ALPHABET[valMod]); // poslednje dve kolone
			sCopy[cnt] = ALPHABET[valMod];
		}
		sCopy[cnt] = '\0';
		printf("Original je:%s\n", s);
		printf("Kopija je: %s\n", sCopy);

		free(sCopy);
		free(s);
		free(sKey);
	}	
	free(s);
	free(sKey);
	return 0;
}
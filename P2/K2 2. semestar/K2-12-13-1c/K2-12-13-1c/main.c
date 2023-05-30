#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// proverava da li se drugi nalazi u prvom
// vraca 1 ako se nalazi, 0 inace
int strPartialCmp(const char* s1, const char* s2) {
	for (; (*s1) != NULL && (*s2) != NULL; s1++, s2++) {
		if (*s1 < *s2)
			return 0;
		if (*s1 > *s2)
			return 0;
	}
	if (*s2 != NULL)
		return 0;
	return 1;
}

//vraca duzinu stringa
int strLen(char *s) {
	int cnt;
	for (cnt = 0; *s != NULL; s++, cnt++);
	return cnt;
}

// brise sva pojavljivanje drugog stringa u prvom
// vraca broj izbrisanih pojavljivanja
int removeAll(char* str, const char* matchStr) {
	int matchStrLen = strLen(matchStr), lenStr = strLen(str),
		cnt, cntCopy, numOfReplaces = 0, match;

	for (cnt = 0; str[cnt] != NULL && str[cnt + matchStrLen - 1] != NULL;) {
		int equal = 1;
		match = strPartialCmp(str + cnt, matchStr);
		numOfReplaces += match;
		if (match)
			for (cntCopy = 0; cntCopy <= strLen(str + cnt); cntCopy++)
				str[cnt + cntCopy] = str[cnt + matchStrLen + cntCopy];
		else cnt++;
	}
	return numOfReplaces;
}

char *readStr() {
	char c, *s = NULL;
	int cnt = 0;

	s = realloc(s, 1);
	*s = '\0';

	while ((c = getchar()) != '\n') {
		++cnt;
		if ((s = realloc(s, (cnt + 1) * sizeof(char))) == NULL) {
			printf("chchu MotherFucker");
			return NULL;
		}
		s[cnt - 1] = c;
		s[cnt] = '\0';
	}
	return s;
}

// glavna funkcija :D
int main() {
	char *s1, *s2;

	s1 = readStr();
	s2 = readStr();
	printf("Shit works");
	printf("%s", s1);
	printf("%s", s2);
	if (s1 != NULL && s2 != NULL) {
		printf("Broj izvrsenih zamena je %d", removeAll(s1, s2));
		printf("Novodobijeni string je%s", s1);
		free(s1);
		free(s2);
		// Ova memorija nije dealocirana jer se digla neka stvar Visual C++ i nije radilo
		// Naravno, ovo radi u Code Blocks, ali izvan Debuger rezima, tako da ne postoji mogucnost da se vidi sta je problem
		// 
	}
	
	getchar();
	return 0;
}
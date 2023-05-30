#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DUZ 100

typedef char string[MAX_DUZ];
typedef string* ptStr;

void upgradeScanS(char *s) {
	char c;
	int cnt = 0;

	while ((c = getchar()) != '\n') {
		s[cnt++] = c;
	}
	s[cnt] = '\0';
}

void ChangeToUpper(char *s) {
	int len = strlen(s), i, j;

	for (i = 0, j = 0; j <= len; i++, j++) 
		if (s[j] == '_') 
			s[i] = s[++j] - 'a' + 'A';
		else s[i] = s[j];
}

int main() {
	char (*arrStr)[MAX_DUZ] = NULL, buffer[MAX_DUZ];
	int numStr = 0, uspesna;

	upgradeScanS(buffer);


	while (strlen(buffer) > 0) {
		++numStr;
		if ((arrStr = realloc(arrStr, sizeof(buffer) * numStr)) == NULL) {
			printf("Neuspesna alokacija");
			break;
		}
		ChangeToUpper(buffer);
		strcpy(arrStr[numStr - 1], buffer);
		printf("%s", arrStr[numStr - 1]);
		printf("%s", arrStr[numStr - 2]);
		upgradeScanS(buffer);
	}

	free(arrStr);
	return 0;
}
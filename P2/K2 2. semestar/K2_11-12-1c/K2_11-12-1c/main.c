#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DUZ 80

int uporedi(const char* str1, const char* str2) {
	int cnt1, cnt2;
	
	for (cnt1 = 0, cnt2 = 0; str1[cnt1] != NULL && str2[cnt2] != NULL; cnt1++, cnt2++) {
		if (str1[cnt1] < str2[cnt2])
			return -1;
		if (str1[cnt1] > str2[cnt2])
			return 1;
	}

	if (str1[cnt1] == str2[cnt2])
		return 0;
	if (str1[cnt1] < str2[cnt2])
		return -1;
	return 1;
}

int main() {
	char pog[MAX_DUZ], unos[MAX_DUZ];
	int rez;

	printf("unesite string koji hocete da pogadjete\n");
	scanf("%s", pog);

	printf("unesite pokusaj\n");
	scanf("%s", unos);

	while ((rez = uporedi(unos, pog)) != 0) {
		printf("%d", rez);
		printf("unesite pokusaj\n");
		scanf("%s", unos);
	}

	return 0;
}
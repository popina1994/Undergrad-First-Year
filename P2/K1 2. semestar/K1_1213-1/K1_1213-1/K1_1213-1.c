#include <string.h>
#include <stdlib.h>
#include <time.h>

const int RandBegin = 1, RandEnd = 255;

int main() {
	char c;
	unsigned randNum, tmpNum, numOnes = 0, cnt;

	srand((unsigned)time(NULL));
	randNum = (double)rand() / RAND_MAX * (RandEnd - RandBegin) + RandEnd;


	while (randNum > 0) {
		if (1 & randNum) numOnes++;
		randNum >>=  1; 
	}
	
	scanf_s("%c", &c, 1);
	while (c != '\n') {
		tmpNum = (unsigned)c ^ randNum;
		for (cnt = numOnes; cnt > 0; cnt--) 
			if (((1u << sizeof(tmpNum) * 8) & tmpNum)) {
				tmpNum <<= 1;
				tmpNum |= 1;
			}
			else tmpNum <<= 1;
		
		printf("%0X", tmpNum);
		scanf_s("%c", &c, 1);
	}
}


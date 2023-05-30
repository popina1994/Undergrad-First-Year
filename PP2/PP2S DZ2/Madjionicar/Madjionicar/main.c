#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int *meme, *weigth, *memeWeigth, *memeOld, *cntPath,
		cntWeigth, cntMeme, cntMemeWeigth, cnt, numCard, magWeigth, cnt1, cnt2;

	//freopen("ulaz.in", "r", stdin);
	//freopen("izlaz.out", "w", stdout);

	scanf("%d%d", &magWeigth, &numCard);

	weigth = (int*)calloc(numCard, sizeof(int)); // weigth oznacava tezine karata
	for (cnt = 0; cnt < numCard; cnt++)
		scanf("%d", &weigth[cnt]);

	meme = (int*)calloc(magWeigth + 1, sizeof(int)); // meme oznacava mase koje mogu se dobiti
	memeWeigth = (int*)calloc(magWeigth + 1, sizeof(int)); // memeWeigth oznacava dobijene mase 
	memeOld = (int*)calloc(magWeigth + 1, sizeof(int));
	cntPath = (int*)calloc(magWeigth + 1, sizeof(int)); // koji indeksi, ovo je najgluplja stvar koju sam napisao u zivotu

	memeWeigth[0] = 0; cntMemeWeigth = 1;
	meme[0] = 1;

	for (cnt = 0; cnt <= magWeigth; cnt++)
		cntPath[cnt] = -1;

	for (cntWeigth = 0; cntWeigth < numCard; cntWeigth++) { // ide po svim masama
		int beforeFor = cntMemeWeigth;
		for (cnt = 0; cnt < beforeFor; cnt++) 
			memeOld[memeWeigth[cnt]] = meme[memeWeigth[cnt]];
		for (cnt = 0; cnt < beforeFor; cnt++) // ide po svim predjenim do sad
			if (memeWeigth[cnt] + weigth[cntWeigth] <= magWeigth) { 
				if (memeOld[memeWeigth[cnt] + weigth[cntWeigth]] == 0) { // prvo pojavljivanje
					memeWeigth[cntMemeWeigth++] = memeWeigth[cnt] + weigth[cntWeigth];
					cntPath[memeWeigth[cnt] + weigth[cntWeigth]] = cntWeigth; 
				}
				meme[memeWeigth[cnt] + weigth[cntWeigth]] += memeOld[memeWeigth[cnt]];
				
			}
	}

 	if (meme[magWeigth] == 0)
		printf("0");
	else if (meme[magWeigth] == 1) {
		int sum = magWeigth;
		for (cnt = cntPath[sum], cntWeigth = 0; sum > 0; cnt = cntPath[sum]){
			sum -= weigth[cnt];
			memeOld[cntWeigth++] = cnt;
	}
		for (cnt1 = 0; cnt1 < numCard; cnt1++) { // Moglo bi da se sortira O(n log n), pa da prodje se u O(n), ali quicksort
			int cond = 1;
			for (cnt2 = 0; cnt2 < cntWeigth; cnt2++)
				if (cnt1 == memeOld[cnt2]) {
					cond = 0;
					break;
				}
			if (cond)
				printf("%d ", cnt1 + 1);

		}
	}
	else printf("-1");

	free(weigth);
	free(meme);
	free(memeWeigth);
	free(memeOld);
	free(cntPath);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILENAMEMAX 100
#define LETTERNUM 26
#define MESSAGEMAX 10000

struct Tree;

typedef struct Tree* PtTree;

struct Tree{
	PtTree left, right;
	int cntProb;
	char letter;
};

struct Node;

typedef struct Node* PtNode;

struct Node {
	PtTree infoTree;
	PtNode next;
};

struct PriorityQueue {
	PtNode begin;
};

struct StackCode;

typedef struct StackCode* PtStackCode;

struct StackCode {
	char code[LETTERNUM + 1];
	int back;

};

struct Stack;

typedef struct Stack* PtStack;

struct Stack {
	PtNode begin;
};

void InsertPQ(struct PriorityQueue* priorityQueue, PtTree ptTree) {
	PtNode ptNewNode, ptTour;

	ptNewNode = (PtNode)malloc(sizeof(struct Node));
	ptNewNode->infoTree = ptTree;
	ptNewNode->next = NULL;

	ptTour = priorityQueue->begin;

	if (ptTour == NULL|| ptTour->infoTree->cntProb > ptNewNode->infoTree->cntProb)
	{
		ptNewNode->next = ptTour;
		priorityQueue->begin = ptNewNode;
	}
	else
	{
		while ((ptTour->next != NULL) && (ptTour->next->infoTree->cntProb <= ptNewNode->infoTree->cntProb))
			ptTour = ptTour->next;
		ptNewNode->next = ptTour->next;
		ptTour->next = ptNewNode;
	}

}

PtTree DeletePQ(struct PriorityQueue* priorityQueue) {
	PtNode tmpNode;
	PtTree element;
	if (priorityQueue->begin == NULL)
		return NULL;

	tmpNode = priorityQueue->begin;
	element = tmpNode->infoTree;
	priorityQueue->begin = priorityQueue->begin->next;
	free(tmpNode);
	return element;
}

void InitializeStackCode(PtStackCode ptStackCode) {
	memset(ptStackCode->code, 0, sizeof(ptStackCode->code));
	ptStackCode->back = 0;
	ptStackCode->code[ptStackCode->back] = '\0';
}

void PushCode(PtStackCode ptStackCode, int element){
	ptStackCode->code[ptStackCode->back] = '0' + element;
	ptStackCode->back++;
	ptStackCode->code[ptStackCode->back] = '\0';

}

// smanji duzinu stringa za jedan karakter
void PopCode(PtStackCode ptStackCode) {
	if (ptStackCode->back == 0){
		printf("Asta La Vista");
		return;
	}
	ptStackCode->back--;
	ptStackCode->code[ptStackCode->back] = '\0';
}

void Push(PtStack ptStack, PtTree ptTree) {
	PtNode tmpPtNode;
	tmpPtNode = (PtNode)malloc(sizeof(struct Node));
	tmpPtNode->infoTree = ptTree;
	tmpPtNode->next = ptStack->begin;
	ptStack->begin = tmpPtNode;
}

PtTree Pop(PtStack ptStack) {
	PtNode tmpPtNode;
	PtTree tmpPtTree;

	tmpPtNode = ptStack->begin;
	ptStack->begin = ptStack->begin->next;
	tmpPtTree = tmpPtNode->infoTree;
	free(tmpPtNode);
	return tmpPtTree;
}

int Empty(PtStack ptStack) {
	if (ptStack->begin == NULL)
		return 1;
	return 0;
}

PtTree Top(PtStack ptStack) {
	return ptStack->begin->infoTree;
}


void Dealocate(PtTree ptTree) {
	PtTree next;
	PtStack ptStack;
	
	if (ptTree->left == NULL && ptTree->right == NULL) {
		free(ptTree);
		return;
	}
		
	ptStack = (PtStack)malloc(sizeof(struct Stack));
	ptStack->begin = NULL;
	
	next = ptTree;
	while (next != NULL) {
		Push(ptStack, next);
		next = next->left;
	}

	while (!Empty(ptStack)) {
		next = Pop(ptStack);
		if (next->cntProb > 0) {
			next->cntProb = -next->cntProb;
			Push(ptStack, next);
			next = next->right;

			while (next != NULL) {
				Push(ptStack, next);
				next = next->left;
			}
		}
		else {
			next->cntProb = -next->cntProb;
			free(next);
		}
	}
	free(ptStack);
}
PtTree HuffmanTree(int letterCnt[], struct PriorityQueue* ptPq, int* numLetter) {
	int cnt;
	PtTree ptTmpTree, ptTmpLeft, ptTmpRight, ptHuffmanTree;

	//inicijalizovanje prioritetnog
	*numLetter = 0;
	for (cnt = 0; cnt < LETTERNUM; cnt++)
		if (letterCnt[cnt] > 0) {
			(*numLetter)++;
			ptTmpTree = (PtTree)malloc(sizeof(struct Tree));
			ptTmpTree->left = NULL; ptTmpTree->right = NULL;
			ptTmpTree->cntProb = letterCnt[cnt];
			ptTmpTree->letter = cnt + 'A';
			InsertPQ(ptPq, ptTmpTree);
		}

	//Huffman's code
	for (cnt = 0; cnt < *numLetter - 1; cnt++) {
		ptTmpTree = (PtTree)malloc(sizeof(struct Tree));

		ptTmpLeft = DeletePQ(ptPq); ptTmpRight = DeletePQ(ptPq);
		ptTmpTree->letter = 0;

		ptTmpTree->left = ptTmpLeft; ptTmpTree->right = ptTmpRight;

		ptTmpTree->cntProb = ptTmpRight->cntProb + ptTmpLeft->cntProb;

		InsertPQ(ptPq, ptTmpTree);
	}

	ptHuffmanTree = DeletePQ(ptPq);
	ptHuffmanTree->cntProb = 0;
	return ptHuffmanTree;
}

// naklepana verzija postorder, kojom se ponosim :)
void HuffmanCodeRead(PtTree ptHuffmanTree, char huffmanCodes[][LETTERNUM + 1]) {
	PtTree  ptTmpTree, ptTmpRight;
	PtStackCode ptStackCode;
	PtStack ptStack;

	ptStackCode = (PtStackCode)malloc(sizeof(struct StackCode));
	ptStack = (PtStack)malloc(sizeof(struct Stack));

	InitializeStackCode(ptStackCode);
	ptStack->begin = NULL;

	Push(ptStack, ptHuffmanTree);

	while (!Empty(ptStack)) {
		//tera dok ne nadje list
		ptTmpTree = Top(ptStack);
		while (ptTmpTree->letter == 0 || ptTmpTree->letter == 1){
			if (ptTmpTree->left != NULL && ptTmpTree->letter != 1) {
				ptTmpTree->letter = 1;
				Push(ptStack, ptTmpTree->left);
				ptTmpTree = ptTmpTree->left;
				PushCode(ptStackCode, 0);
			}
			else if (ptTmpTree->right != NULL){
				ptTmpTree->letter = 2;
				Push(ptStack, ptTmpTree->right);
				ptTmpTree = ptTmpTree->right;
				PushCode(ptStackCode, 1);
			}
		}
		strcpy(huffmanCodes[ptTmpTree->letter - 'A'], ptStackCode->code);

		//zaglavi se, dok ne nadje prvo desno koje nije poseceno
		ptTmpRight = Top(ptStack)->right;
		while (!Empty(ptStack) && (ptTmpRight == NULL || (Top(ptStack)->letter == 2))) {
			Pop(ptStack);

			if (Empty(ptStack))
				break;
			// underflow stackCode

			PopCode(ptStackCode);
			ptTmpRight = Top(ptStack)->right;
			if (ptTmpRight->letter >= 'A' && Top(ptStack)->letter != 2) {
				Top(ptStack)->letter = 2;
				Push(ptStack, ptTmpRight);
				PushCode(ptStackCode, 1);
				break;
				/* ako imas desno pa samo levo otici ce prvo desno umesto levo
				jeste napisano u uslovu, ali neka stoji
				Bog i ja smo znali zasto je ovaj komentar napisan
				Sad samo Bog zna
				Zakljucak : Ne znam sta je bilo sa mnom, moze 1000 puta cistiji kod, ali ne znam sta je bilo sa mnom
				*/
			}
		}
		//Ovo djubre kad ti je proslo :D
	}
	free(ptStack);
}

int main() {
	FILE *input, *output;
	char inputFileName[FILENAMEMAX], c, inputStr[MESSAGEMAX], outputFileName[FILENAMEMAX],
		huffmanCodes[LETTERNUM][LETTERNUM + 1];
	int letterCnt[LETTERNUM], cnt, numLetter;
	struct PriorityQueue* ptPq;

	PtTree ptTmpTree, ptTmpLeft, ptTmpRight, ptHuffmanTree;
	

	// alokacije
	ptPq = (struct PriorityQueue*) malloc(sizeof(struct PriorityQueue));
	

	// inicijalizacije
	
	ptPq->begin = NULL;
	

	printf("unesite ime datoteke koju hocete da citate\n");
	gets(inputFileName);

	printf("unesite ime datoteke u koju hocete da pisete\n");
	gets(outputFileName);

	while (strlen(inputFileName) > 0 && strlen(outputFileName))  {

		if ((input = fopen(inputFileName, "r")) == NULL || (output = fopen(outputFileName, "w")) == NULL)
			printf("Lose citanje\n");
		else {
			// verovatnoca
			memset(letterCnt, 0, sizeof(letterCnt));
			fgets(inputStr, MESSAGEMAX, input);
			for (cnt = 0; cnt < strlen(inputStr); cnt++)
				letterCnt[inputStr[cnt] - 'A']++;
			fclose(input);

			ptHuffmanTree = HuffmanTree(letterCnt, ptPq, &numLetter);

			if (ptHuffmanTree->left == NULL && ptHuffmanTree->right == NULL) {
				huffmanCodes[ptHuffmanTree->letter - 'A'][0] = '0';
				huffmanCodes[ptHuffmanTree->letter - 'A'][1] = '\0';
			}
			else HuffmanCodeRead(ptHuffmanTree,  huffmanCodes);
			
			//ispis
			for (cnt = 0; cnt < LETTERNUM; cnt++)
				if (letterCnt[cnt])
					fprintf(output, "%c %s\n", cnt + 'A', huffmanCodes[cnt]);

			for (cnt = 0; cnt < strlen(inputStr); cnt++)
				fputs(huffmanCodes[inputStr[cnt] - 'A'], output);
			
			fclose(output);
			Dealocate(ptHuffmanTree);
		}
		
		printf("unesite ime datoteke koju hocete da citate\n");
		gets(inputFileName);

		printf("unesite ime datoteke u koju hocete da pisete\n");
		gets(outputFileName);
	}

	free(ptPq);
	


	return 0;
}
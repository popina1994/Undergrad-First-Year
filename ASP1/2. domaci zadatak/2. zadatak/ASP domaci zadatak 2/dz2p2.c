#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUMJMPPOS 8

const int IndexRow[NUMJMPPOS] = { -2, -2, -1, -1, 1, 1, 2, 2 },
		  IndexCol[NUMJMPPOS] = { -1, 1, -2, 2, -2, 2, -1, 1 };

struct Node;

typedef struct Node* PtNode;

struct Node {
	int info;
	PtNode next;
};

struct Tree;

typedef struct Tree *PtTree;

struct Tree {
	PtTree arrPt[NUMJMPPOS];
	int end;
};

struct NodeTree;

typedef struct NodeTree* PtNodeTree;

struct NodeTree {
	PtTree infoTree;
	PtNodeTree next;
};

struct Stack;

typedef struct Stack* PtStack;

struct Stack {
	PtNode begin;
};

struct StackTree{
	PtNodeTree begin;
};

typedef struct StackTree *PtStackTree;

void InitializeStack(PtStack ptStack) {
	ptStack->begin = NULL;
}

int Empty(PtStack ptStack) {
	return (ptStack->begin == NULL);
}

void Push(PtStack ptStack, int val) {
	PtNode ptTmpNode;

	ptTmpNode = (PtNode)malloc(sizeof(struct Node));
	ptTmpNode->info = val;
	ptTmpNode->next = NULL;

	ptTmpNode->next = ptStack->begin;
	ptStack->begin = ptTmpNode;
	return;
}

int Pop(PtStack ptStack) {
	PtNode ptTmpNode;
	int tmpVal;
	
	if (Empty(ptStack)) {
		printf("ERROR");
		return -1;
	}
	
	ptTmpNode = ptStack->begin;
	tmpVal = ptStack->begin->info;
	ptStack->begin = ptTmpNode->next;
	free(ptTmpNode);

	return tmpVal;
}

int Top(PtStack ptStack) {
	if (ptStack->begin == NULL)
		return -1;
	return ptStack->begin->info;
}

void Clear(PtStack ptStack) {
	while (!Empty(ptStack)) Pop(ptStack);
}


int EmptyTree(PtStackTree ptStackTree) {
	if (ptStackTree->begin == NULL)
		return 1;
	return 0;
}

void PushTree(PtStackTree ptStackTree, PtTree ptTree) {
	PtNodeTree tmpPtNodeTree;
	int cnt;
	
	tmpPtNodeTree = (PtNodeTree)malloc(sizeof(struct NodeTree));
	tmpPtNodeTree->infoTree = ptTree;
	tmpPtNodeTree->next = ptStackTree->begin;
	ptStackTree->begin = tmpPtNodeTree;
}

PtTree PopTree(PtStackTree ptStackTree) {
	PtNodeTree tmpPtNodeTree;
	PtTree ptTree;

	if (ptStackTree->begin == NULL) {
		printf("prazan stek");
		return NULL;
	}

	tmpPtNodeTree = ptStackTree->begin;
	ptTree = tmpPtNodeTree->infoTree;
	ptStackTree->begin = ptStackTree->begin->next;	
	free(tmpPtNodeTree);
	return ptTree;
}

PtTree TopTree(PtStackTree ptStackTree) {
	if (ptStackTree->begin == NULL) {
		printf("prazan stek");
		return NULL;
	}

	return ptStackTree->begin->infoTree;
}

int AllocateMatrix(int ***matrix, int row, int col) {
	int cnt;
	*matrix = (int**)calloc(row, sizeof(int*));
	if (*matrix == NULL)
		return 0;

	for (cnt = 0; cnt < row; cnt++) {
		(*matrix)[cnt] = (int*)calloc(col, sizeof(int));
		if ((*matrix)[cnt] == NULL)
			return 0;
	}

	return 1;
}

void DealocateMatrix(int ***matrix, int row, int col) {
	int cnt;

	for (cnt = 0; cnt < row; cnt++)
		free((*matrix)[cnt]);
	free(*matrix);
}

int CanJump(int row, int col, int numRow, int numCol) {
	return (row < numRow && row >= 0 && col < numCol && col >= 0);
}

PtTree NewTree() {
	PtTree tmpPtTree;
	int cnt;

	tmpPtTree = (PtTree)malloc(sizeof(struct Tree));
	for (cnt = 0; cnt < NUMJMPPOS; cnt++)
		tmpPtTree->arrPt[cnt] = NULL;
	tmpPtTree->end = 0;
	return tmpPtTree;
}

void PrintMatrix(int **matrix, int numRow, int numCol) {
	int cntRow, cntCol;
	for (cntRow = 0; cntRow < numRow; cntRow++) {
		for (cntCol = 0; cntCol < numCol; cntCol++)
			printf("%2d ", matrix[cntRow][cntCol]);
		printf("\n");
	}
	printf("\n");
}


void WalkTree(int ***matrix, int numRow, int numCol, int startRow, int startCol, PtTree root) {
	int cntRow, cntCol, cnt, cnt1;
	
	for (cntRow = 0; cntRow < numRow; cntRow++)
		for (cntCol = 0; cntCol < numCol; cntCol++)
			(*matrix)[cntRow][cntCol] = 0;

	for (cnt = 0; cnt < numRow * numCol; cnt++) {
		(*matrix)[startRow][startCol] = cnt;
		PrintMatrix(*matrix, numRow, numCol);

		for (cnt1 = 0; cnt1 < NUMJMPPOS; cnt1++)
			if (root->arrPt[cnt1] != NULL) {
				startRow += IndexRow[cnt1];
				startCol += IndexCol[cnt1];
				root = root->arrPt[cnt1];
				break;
			}
	}
}

void DealocateTree(PtStackTree ptStackTree, PtTree root) {
	PtTree next;
	int cnt;

	if (root == NULL)
		return;
	for (cnt = 0; cnt < NUMJMPPOS; cnt++) 
		DealocateTree(ptStackTree, root->arrPt[cnt]);

	free(root);
}	

int main() {
	int numRow, numCol, startRow, startCol, **matrix = NULL, cnt, cntJmp, tmpRow, tmpCol, cntRow, cntCol, exist, cnt1;
	PtStack rowStack, colStack, state;
	PtTree root, ptTmpTree;
	PtStackTree ptStackTree;

	//freopen("ulaz.in", "r", stdin);
	//freopen("izlaz.out", "w", stdout);
	
	rowStack = (PtStack)malloc(sizeof(struct Stack)); colStack = (PtStack)malloc(sizeof(struct Stack));
	state = (PtStack) malloc(sizeof(struct Stack));
	ptStackTree = (PtStackTree)malloc(sizeof(struct StackTree));
	ptStackTree->begin = NULL;

	printf("unesite dimenzije matrice\n");
	scanf("%d%d", &numRow, &numCol);

	printf("unesite pocetne koordinate\n");
	scanf("%d%d", &startRow, &startCol);

	while (numRow > 0 && numCol > 0) {
		
		AllocateMatrix(&matrix, numRow, numCol);
		
		InitializeStack(rowStack); InitializeStack(colStack);
		Push(rowStack, startRow); Push(colStack, startCol);
		matrix[startRow][startCol] = 1;

		InitializeStack(state); Push(state, -1);
		cntJmp = 2; exist = 0;

		root = NewTree();
		PushTree(ptStackTree, root);

		while (!Empty(rowStack)) {
			
			cnt = Pop(state) + 1;

			if (cnt == NUMJMPPOS) { // implicitno je u uslovu dato da kad prodje dubinu m * n zaustavlja se
				int numNull = 0;
				tmpRow = Pop(rowStack); tmpCol = Pop(colStack);
				matrix[tmpRow][tmpCol] = 0;
				cntJmp--;
				ptTmpTree = PopTree(ptStackTree);	
				for (cnt1 = 0; cnt1 < NUMJMPPOS; cnt1++)
					if (cntJmp < numCol * numRow && (ptTmpTree->arrPt[cnt1] == NULL || ptTmpTree->arrPt[cnt1]->end)) {
						free(ptTmpTree->arrPt[cnt1]); // oslobodi sve "nivoe" ispod 
						
						ptTmpTree->arrPt[cnt1] = NULL;
						numNull ++;
					}
					ptTmpTree->end = numNull == NUMJMPPOS ? 1 : 0; // ne vodi nikud
			}
			else {
				tmpRow = Top(rowStack) + IndexRow[cnt]; tmpCol = Top(colStack) + IndexCol[cnt];
				if (CanJump(tmpRow, tmpCol, numRow, numCol) && matrix[tmpRow][tmpCol] == 0) {
					matrix[tmpRow][tmpCol] = cntJmp++;
					Push(state, cnt); 

					ptTmpTree = TopTree(ptStackTree);
					ptTmpTree->arrPt[cnt] = NewTree();
					
					Push(rowStack, tmpRow); Push(colStack, tmpCol);
					Push(state, -1);
					PushTree(ptStackTree, ptTmpTree->arrPt[cnt]);
				}
				else Push(state, cnt);
			}
			if (cntJmp == numCol * numRow + 1)
				exist = 1;
		
		}

		if (!exist) printf("Nema resenja\n");
		else WalkTree(&matrix, numRow, numCol, startRow, startCol, root);
			
		DealocateMatrix(&matrix, numRow, numCol);
		DealocateTree(ptStackTree, root);
		Clear(rowStack); Clear(colStack);
		Clear(state);

		printf("unesite dimenzije matrice\n");
		scanf("%d%d", &numRow, &numCol);

		printf("unesite pocetne koordinate\n");
		scanf("%d%d", &startRow, &startCol);
	}

	free(rowStack); free(colStack);
	free(state);
	free(ptStackTree);

	return 0;
}
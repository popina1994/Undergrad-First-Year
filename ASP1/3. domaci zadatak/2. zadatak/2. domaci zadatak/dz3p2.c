#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#define LEN_KEY 10 // duzina kljuca, i broj cifara

typedef struct Node Node;

typedef Node *NodePt;

struct Node {
	int vertex, weight; // oznacava koliko treba okretanja od cvora u listi, do cvora u kojoj listi po redu se nalazi
	NodePt next;
};

//prioritetna lista cvorova
typedef struct PQueue {
	NodePt begin;
} PQueue;

typedef PQueue *PQueuePt;

// sadrzi niz listi, i broj cvorova u grafu
typedef struct Graph {
	PQueuePt vertex;
	int numVertices;
	char (*key)[LEN_KEY];
	// mst[i], oznacava da li je i-ti cvor vec u mst-u
	// weight predstavlja sifru
} Graph;

typedef Graph *GraphPt;

// inicijalizuje vrednosti liste
void InitializePQ(PQueuePt ptPQ) {
	ptPQ->begin = NULL;
}

// vraca 1 ako je lista prazna, 0 ako nije
int EmptyPQ(PQueuePt ptPQ) {
	return (ptPQ->begin == NULL);
}

// stavlja granu u PQ
// ako je neuspelo stavljanje vraca 0
// ako je uspesno stavljanje vraca 1
int PushPQ(PQueuePt ptPQ, int u, int weight) {
	NodePt newNode, iteratorPQ = NULL;	

	newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Nedovoljno memorije\n");
		return 0; // izlazi ako nema memorije na heap-u
	}
	newNode->vertex = u;
	newNode->weight = weight;
	newNode->next = NULL;

	iteratorPQ = ptPQ->begin;

	if (iteratorPQ == NULL || iteratorPQ->weight > weight) { // ako je prazna lista ili se element stavlja na pocetak
		newNode->next = ptPQ->begin;
		ptPQ->begin = newNode;
	}
	else {
		while ((iteratorPQ->next != NULL) && (iteratorPQ->next->weight <= weight)) // dok ne dodje elementa koji je 
			iteratorPQ = iteratorPQ->next;										  // manji od trazenog
		newNode->next = iteratorPQ->next; // sledeci od novog cvora je prvi koji je veci
		iteratorPQ->next = newNode; // pokazivac se preusmerava na novi
	}

	return 1;
}


// vraca cvor iz grafa uz brisanje cvora iz liste
//-1 ako je lista prazna
int PopPQ(PQueuePt ptPQ) {
	int u;
	NodePt newNode;

	if (ptPQ->begin == NULL) {
		printf("Prazna lista");
		return -1;
	}
	else {
		newNode = ptPQ->begin;
		u = newNode->vertex;
		ptPQ->begin = ptPQ->begin->next;
		free(newNode);

		return u;
	}
}

// vraca tezinu grane
// -1 ako je lista prazna
int TopWeight(PQueuePt ptPQ) {
	if (ptPQ->begin == NULL)
		return -1;
	return ptPQ->begin->weight;
}

// vraca 
//
int TopVertex(PQueuePt ptPQ) {
	if (ptPQ->begin == NULL)
		return -1;
	return ptPQ->begin->vertex;
}

// postavlja broj cvorova u grafu na 0, pokazivac na niz listi je NULL, svi pokazivaci su NULL
void InitializeGraph(GraphPt ptG) {
	ptG->numVertices = 0;
	ptG->vertex = NULL;
	ptG->key = NULL;
}

//brise ceo graf, postavlja vrednosti numVertices na NULL, vertex mst, key na NULL
void DeleteGraph(GraphPt ptG) {
	int cnt;

	for (cnt = 0; cnt < ptG->numVertices; cnt++)
		while (!EmptyPQ(ptG->vertex + cnt))
			PopPQ(ptG->vertex + cnt);
	free(ptG->vertex);
	
	free(ptG->key);
	InitializeGraph(ptG);
}

// 0 neuspesno stvaranje grafa sa datim brojem cvrova , 1 uspesno
int CreateGraph(GraphPt ptG, int numVertices) {
	int cnt;

	DeleteGraph(ptG);
	ptG->vertex = realloc(ptG->vertex, sizeof(PQueue)* numVertices); // realociraj prostor
	if (ptG->vertex == NULL)
		return 0;

	ptG->numVertices = numVertices; // broj cvorova u grafu
	for (cnt = 0; cnt < numVertices; cnt++)
		InitializePQ(ptG->vertex + cnt); // inicijalizovanje svake inverzne liste susednosti

	if ( (ptG->key = realloc(ptG->key, numVertices * sizeof(char[LEN_KEY]))) == NULL) {
		printf("Nema dovoljno memorije\n");
		return 0;
	}

	return 1;
}

//dodaje granu koja izlazi iz cvora u, ulazi u cvor v
// 1 vraca ako je uspesno dodata
// 0 ako nije uspesno dodata
int AddEdge(GraphPt ptG, int u, int v, int weight) {
	return PushPQ(ptG->vertex + v, u, weight);
}


// cita iz ulaznog fajla i formira graf koij sadrzi tezine grana, i
void Input(GraphPt ptG) {
	FILE *input;
	int numVertices, cnt, cntKey;

	if ((input = fopen("ulaz.in", "r")) == NULL) {
		printf("Greska u citanju\n");
		exit(1);
	}

	fscanf(input, "%d\n", &numVertices);

	CreateGraph(ptG, numVertices + 1); // prvi cvor je 00
	for (cntKey = 0; cntKey < LEN_KEY; cntKey++)
		ptG->key[0][cntKey] = '0';

	for (cnt = 1; cnt <= numVertices; cnt++) {// citanje iz datoteke
		for (cntKey = 0; cntKey < LEN_KEY; cntKey++)
			ptG->key[cnt][cntKey] = fgetc(input);
		fgetc(input);

	}
	fclose(input);
}


// izracuna tezinu svake grane i doda je u graf
void InitalizeWeights(GraphPt ptG) {
	int i, j, cntKey, weight;

	for (i = 0; i < ptG->numVertices - 1; i++) 
		for (j = i + 1; j < ptG->numVertices; j++) {
			for (cntKey = 0, weight = 0; cntKey < LEN_KEY; cntKey++) {
				int tmpWeight = abs(ptG->key[i][cntKey] - ptG->key[j][cntKey]); // koliko treba pomeranja
				if (tmpWeight > LEN_KEY / 2)
					tmpWeight = LEN_KEY - tmpWeight; 
				weight += tmpWeight; // ukupna tezina
			}
			AddEdge(ptG, i, j, weight); AddEdge(ptG, j, i, weight); // dodaj ivice u graf
		}
}

// prim's mst
// obradi i ispise tezinu MST-a, i kojim redom su cvorovi
void MSTOutput(GraphPt ptG) {
	int *visit, minWeight, minVertex, weightMST = 0,
		u, *mst, cnt, cntVertex, vertexProc, leftNode;
		// mst kojim redom su dodavane grane u stablu
		// vertexProc koliko je cvorova dodato
		// visit oznacava kojim redom su cvorovi posecivani
		// minVal trenutnu minimalnu granu, minVertex minimalni cvor

	visit = calloc(ptG->numVertices, sizeof(int)); // prvi cvor nece se pisati
	mst = malloc(sizeof(int)* ptG->numVertices); 
	if (visit == NULL || mst == NULL) {
		printf("Nema memorije\n");
		exit(1);
	}

	mst[0] = 0; visit[0] = 1;  vertexProc = 1;// prvi cvor se ubacuje

	for (cnt = 0; cnt < ptG->numVertices - 1; cnt++) { // broji po granama mst-a
		minWeight = INT_MAX; minVertex = -1; leftNode = -1;
		
		for (cntVertex = 0; cntVertex < vertexProc; cntVertex++) {
			u = mst[cntVertex]; // cvor koji proveravamo
			while (visit[TopVertex(ptG->vertex + u)]) // dok ne dodjemo do grane koja spaja nespojene oblasti
				PopPQ(ptG->vertex + u);
			if (TopWeight(ptG->vertex + u) < minWeight) { // ako je nadjena grana koja ima manju tezinu od trenutne
				minWeight = TopWeight(ptG->vertex + u);
				minVertex = TopVertex(ptG->vertex + u);
				leftNode = cntVertex;
			}
		}
		PopPQ(ptG->vertex + leftNode);
		mst[vertexProc++] = minVertex; visit[minVertex] = 1; // dodaje se nadjeni cvor u MST
		weightMST += minWeight;			// tezina MST-a se uvecava
	}

	printf("%d\n", weightMST);
	for (cnt = 1; cnt < vertexProc; cnt++)
		printf("%d ", mst[cnt]);

	free(visit);
	free(mst);
}

int main() {
	Graph g;

	InitializeGraph(&g);
	Input(&g);
	InitalizeWeights(&g);
	MSTOutput(&g);
	DeleteGraph(&g);
	getchar();
	return 0;

}
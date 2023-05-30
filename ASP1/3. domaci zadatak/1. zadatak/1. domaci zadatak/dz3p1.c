#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

typedef Node *NodePt;

struct Node {
	int vertex;
	NodePt next;
};

//lista cvorova
typedef struct Queue {
	NodePt begin;
} Queue;

typedef Queue *QueuePt;

// sadrzi niz listi, i broj cvorova u grafu
typedef struct Graph {
	QueuePt vertex;
	int numVertices;
} Graph;

typedef Graph *GraphPt;

typedef struct VisitTime {
	int visit, start, finish;
} VisitTime;

// inicijalizuje vrednosti liste
void InitializeQ(QueuePt ptQ) {
	ptQ->begin = NULL;
}

// vraca 1 ako je lista prazna, 0 ako nije
int EmptyQ(QueuePt ptQ) {
	return (ptQ->begin == NULL);
}

// stavlja cvor na pocetak liste, 1 ako je uspelo u stavljanju, 0 inace
int PushQ(QueuePt ptQ, int u) {
	NodePt newNode;

	newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Nedovoljno memorije\n");
		return 0; // izlazi ako nema memorije na heap-u
	}
	newNode->vertex = u;
	newNode->next = ptQ->begin;
	ptQ->begin = newNode;

	return 1;
}

// vraca element sa pocetka liste, -1 ako je lista prazna
int PopQ(QueuePt ptQ) {
	int u;
	NodePt newNode;

	if (ptQ->begin == NULL) {
		printf("Prazna lista");
		return -1;
	}
	else {
		newNode = ptQ->begin;
		u = newNode->vertex;
		ptQ->begin = ptQ->begin->next;
		free(newNode);

		return u;
	}
}

// postavlja broj cvorova u grafu na 0, pokazivac na niz listi je NULL
void InitializeGraph(GraphPt ptG) {
	ptG->numVertices = 0;
	ptG->vertex = NULL;
}

//brise ceo graf, postavlja vrednosti numVertices na NULL i vertex na NULL
void DeleteGraph(GraphPt ptG) {
	int cnt;

	for (cnt = 0; cnt < ptG->numVertices; cnt++)
		while (!EmptyQ(ptG->vertex + cnt))
			PopQ(ptG->vertex + cnt);
	free(ptG->vertex);
	InitializeGraph(ptG);
}

// 0 neuspesno stvaranje grafa sa datim broje , 1 uspesno
int CreateGraph(GraphPt ptG, int numVertices) {
	int cnt;

	DeleteGraph(ptG);
	ptG->vertex = realloc(ptG->vertex, sizeof(Queue)* numVertices); // realociraj prostor
	if (ptG->vertex == NULL)
		return 0;

	ptG->numVertices = numVertices; // broj cvorova u grafu
	
	for (cnt = 0; cnt < numVertices; cnt++)
		InitializeQ(ptG->vertex + cnt); // inicijalizovanje svake inverzne liste susednosti
	return 1;
}

// dodaje novi cvor u listu cvorova
// vraca vrednost 1 ako je uspela
int AddVertex(GraphPt ptG, int u) {
	QueuePt ptError;
	int cnt;

	if (ptG->numVertices > u) {
		printf("Cvor je vec dodat\n");
		return 1;
	}
	else {
		ptError = realloc(ptG->vertex, sizeof(Queue)* (u + 1));
		if (ptError == NULL) {
			printf("Nedovoljno memorije na heapu-u");
			return 0;
		}
		else ptG->vertex = ptError; // uvecava se niz listi

		for (cnt = ptG->numVertices; cnt <= u; cnt++) 
			InitializeQ(ptG->vertex + cnt); // pravljenje praznih lista susednosti
		ptG->numVertices = u + 1;
	}
	return 1;
}

//dodaje kranu koja izlazi iz cvora u, ulazi u cvor v
// 1 vraca ako je uspesno dodata
// 0 ako nije uspesno dodata
int AddEdge(GraphPt ptG, int u, int v) {
	return PushQ(ptG->vertex + v, u);
}

// brise granu koja izlazi iz cvora u, ulazi u cvor v
// 1 vraca ako je brisanje uspesno
// 0 vraca ako ne postoji grana
int RemoveEdge(GraphPt ptG, int u, int v) {
	NodePt iteratorQ, newNode;
	
	if (ptG->numVertices <= u || ptG->numVertices <= v || EmptyQ(ptG->vertex + v))
		return 0;	// ne postoje cvorovi
					// prazna lista
	iteratorQ = ptG->vertex[v].begin;
	if (iteratorQ->vertex == u){
		ptG->vertex[v].begin = iteratorQ->next; // ako je trazena grana prva u listi 
		free(iteratorQ);
		return 1; // grana se nalazi na pocetku
	}
	while (iteratorQ->next != NULL && iteratorQ->next->vertex != u)
	iteratorQ = iteratorQ->next;
	if (iteratorQ->next != NULL) {
		newNode = iteratorQ->next;
		iteratorQ->next = newNode->next;
		free(newNode);
		return 1;			 // grana se nalazi u sredini
	}
	
	return 0;
}


// brise cvor u iz grafa *ptG
void RemoveVertex(GraphPt ptG, int u) {
	int cnt;
	if (u >= ptG->numVertices) {
		printf("Cvor ne postoji\n");
		return; // cvor vec ne postoji
	}
	while (!EmptyQ(ptG->vertex + u))
		PopQ(ptG->vertex + u); // po inverznoj listi susednosti prodje
	
	for (cnt = 0; cnt < ptG->numVertices; cnt++)
		while (RemoveEdge(ptG, u, cnt) != 0); // prodje po svim mogucim cvorovima
	printf("Cvor je uspesno obrisan\n");
}

//racuna ulazni stepen cvora
// -1 vraca kad ne postoji cvor u grafu
// U ostalim slucajevima pravi stepen
int InputDegree(const GraphPt ptG, int u) {
	NodePt iteratorQ;
	int cnt = 0;

	if (u >= ptG->numVertices)
		return -1;

	for (iteratorQ = ptG->vertex[u].begin; iteratorQ != NULL; iteratorQ = iteratorQ->next)
		cnt++; // prolazi po inverznoj listi susesdnosti i broj ulazne grane
	return cnt;
}

// racuna izlazni stepen cvora
// -1 vraca kad ne postoji cvor u grafu
// U ostalim slucajevima pravi stepen
int OutputDegree(const GraphPt ptG, int u) {
	NodePt iteratorQ;
	int cnt = 0, cntVertex;

	if (u >= ptG->numVertices)
		return -1;

	for (cntVertex = 0; cntVertex < ptG->numVertices; cntVertex++) {
		iteratorQ = ptG->vertex[cntVertex].begin;
		while (iteratorQ != NULL) {
			cnt += iteratorQ->vertex == u; // u ulazi u cntVertex
			iteratorQ = iteratorQ->next;
		}
	}
	return cnt;
}

// vraca 1 ako je cvor u dostizan iz v
// 0 inace
int Adjacent(const GraphPt ptG, int u, int v) {
	Queue stack;
	NodePt iteratorStack;
	int *visit; // oznacava koji cvorovi su poseceni, 1 zavrseno, -1 u obradi, 0 neposecen
	
	if (u >= ptG->numVertices) {
		printf("Lose ste uneli cvorove\n");
		return 0;
	}

	visit = (int*)calloc(ptG->numVertices, sizeof(int));
	InitializeQ(&stack);
	PushQ(&stack, u); // cvor od koga krecemo

	while (!EmptyQ(&stack)) {

		u = PopQ(&stack);
		if (visit[u] == -1) visit[u] = 1; // vraca iz rekurzije
	
		if (!visit[u])  { 
			visit[u] = -1; 
			PushQ(&stack, u);
		} // ulazi u rekurziju

		for (iteratorStack = ptG->vertex[u].begin; iteratorStack != NULL; iteratorStack = iteratorStack->next) 
			if (iteratorStack->vertex == v) { // kad nadje resenje
				printf("%d ", v);
				
				while (!EmptyQ(&stack)) { // pise put
					u = PopQ(&stack);
					if (visit[u] == -1)
						printf("%d ", u);
				}
				free(visit);
				return 1;
			}
			else if (!visit[iteratorStack->vertex])  // ako nije posecen predji na sledeci
				PushQ(&stack, iteratorStack->vertex); 
	}
	free(visit);
	return 0;
}

// Napravi transponovani graf ptG2 od grafa ptG1
// vraca 1 ako je uspesno izvedeno
// vraca 0 ako nije uspelo 
int TransposeGraph(GraphPt ptG1, GraphPt ptG2) {
	int cnt;
	NodePt iteratorQ;

	InitializeGraph(ptG2);
	CreateGraph(ptG2, ptG1->numVertices);

	for (cnt = 0; cnt < ptG1->numVertices; cnt++)
		for (iteratorQ = ptG1->vertex[cnt].begin; iteratorQ != NULL; iteratorQ = iteratorQ->next)
			if (!AddEdge(ptG2, cnt, iteratorQ->vertex)) // ako nije uspelo stvaranje
				return 0;
	return 1;
}

// Depth first search iz trenutnog cvora po grafu, cvorovi ce biti smesteni po zavrsnim vremenima u stackNodes
// vraca 1 ako je uspesno izvedeno
// vraca 0 inace
int DFSTime(GraphPt ptG, QueuePt stackNodes) {
	int time = 1, cnt, u;
	Queue stack;
	VisitTime * x;// oznacavac cvorove koji su poseceni, vreme
	NodePt iteratorStack;

	InitializeQ(&stack);
	x = (VisitTime*)calloc(ptG->numVertices, sizeof(VisitTime)); // sve postavi na nule

	if (x == NULL) { printf("Nema dovoljno memorije"); return 0;}
	
	for (cnt = 0; cnt < ptG->numVertices; cnt++)
		if (!x[cnt].visit) {	// ako nije posecen, stavimo ga na stek
			if (!PushQ(&stack, cnt)) { printf("Nema memorije\n"); return 0; }

			while (!EmptyQ(&stack)) {
				u = PopQ(&stack);

				if (x[u].start == 0) {
					x[u].start = time++;
					x[u].visit = 1;
					if (!PushQ(&stack, u)) return NULL;
				}
				else {
					x[u].finish = time++;
					if (!PushQ(stackNodes, u)) { printf("Nema memorije\n"); return 0; }
				}
				for (iteratorStack = ptG->vertex[u].begin; iteratorStack != NULL; iteratorStack = iteratorStack->next) {
					int v = iteratorStack->vertex;
					if (!x[v].visit)
						if (!PushQ(&stack, v)) return 0;
				}
			}
		}
	free(x);
		
	return 1;
}

// DFS-uje po grafu ptG
// vraca 1 ako je uspesno DFS-ovalo
// vraca 0 ako nije uspelo
int DFS(GraphPt ptG, int u, int *visit) {
	Queue stack;
	NodePt iteratorStack;

	InitializeQ(&stack);

	if (!PushQ(&stack, u)) return 0;  // stavi cvor od koga se krece
	while (!EmptyQ(&stack)) {
		u = PopQ(&stack);

		if (visit[u] == 0) { // ako je WHITE node
			visit[u] = -1;
			if (!PushQ(&stack, u)) return 0;
		}
		else visit[u] = 1; // ako je GRAY node
		for (iteratorStack = ptG->vertex[u].begin; iteratorStack != NULL; iteratorStack = iteratorStack->next) {
			int v = iteratorStack->vertex;
			if (!visit[v])
				if (!PushQ(&stack, v)) return 0;
		}
	}
	return 1;
}

// vraca broj jako povezanih komponenti
int StronglyConnected(GraphPt ptG) {
	int cntCmp = 0, cnt, indexMax; // oznacava cvor sa maksimalnim zavrsnim vremenom
	Graph gTranspose;
	int *visit; // posecenost cvora, pocetno i zavrsno vreme
	Queue stack; // sadrzi cvorove po zavrsnim vremenima posecenosti

	visit = calloc(ptG->numVertices, sizeof(int));
	if (visit == NULL) { printf("Nema dovoljno memorij\n"); return 0; }
	InitializeQ(&stack);
	
	if (!DFSTime(ptG, &stack)) return 0;

	for (cnt = 0; cnt < ptG->numVertices; cnt++)
		visit[cnt] = 0;// svi cvorovi ce se ponovo posetiti

	if (!TransposeGraph(ptG, &gTranspose)) { printf("Greska u obilasku"); return 0; }
	
	while (!EmptyQ(&stack)) { // dok se ne predje ceo graf
		indexMax = PopQ(&stack);
		if (!visit[indexMax]) {
			if (!DFS(&gTranspose, indexMax, visit)) return 0;
			cntCmp++;
		}
	}
	free(visit);
	DeleteGraph(&gTranspose);
	return cntCmp;
}

// ispis menija, citanje izbora
void MenuOutput(int *choice) {

	printf("0) kraj\n");
	printf("1) ako zelite da kreirate novi graf \n");
	printf("21) dodavanje cvora\n");
	printf("22) uklanjanje cvora\n");
	printf("31) dodavanje grane izmedju dva cvora\n");
	printf("32) uklanjanje grane izmedju dva cvora\n");
	printf("4) racunanje ulaznog stepena cvora\n");
	printf("5) racunanje izlaznog stepena cvora\n");
	printf("6) dostiznost dva cvora\n");
	printf("7) broj jako povezanih komponenti\n");
	printf("\n");

	scanf("%d", choice);
}



int main() {
	int choice;
	Graph g;
	InitializeGraph(&g);

	MenuOutput(&choice);
	
	while (choice != 0) {
		int numVertices, u, v;
		switch (choice) {
		case 1: 
			printf("Unesite broj cvorova u grafu\n");
			scanf("%d", &numVertices); 
			
			if (CreateGraph(&g, numVertices)) // stvaranje grafa
				printf("Uspesno stvoren graf\n");
			else printf("Neuspesno stvaranje grafa\n");
			break;
		case 21: 
			printf("Unesite cvor koji dodajete\n");
			scanf("%d", &u);
			
			if (AddVertex(&g, u))
				printf("Uspesno dodat cvor\n");
			else printf("Neuspesno dodat cvor\n");
			break;
		case 22: 
			printf("Unesite cvor koji brisete\n"); 
			scanf("%d", &u);
			
			RemoveVertex(&g, u);
			break;
		
		case 31: 
			printf("Unesite granu koju hocete da dodate\n"); 
			scanf("%d%d", &u, &v);

			if (AddEdge(&g, u, v))
				printf("Uspesno dodavanje grane\n");
			else printf("Neuspesno dodavanje grane\n");
			break;
		
		case 32: 
			printf("Unesite grane koje hocete da brisete\n");
			scanf("%d%d", &u, &v);
			
			if (RemoveEdge(&g, u, v))
				printf("Grana uspesno obrisana\n");
			else printf("Grana nije ni postojala\n");
			break;
		
		case 4: 
			printf("Unesite cvor ciji ulazni stepen zelite da racunate\n");
			scanf("%d", &u);
			
			if ((v = InputDegree(&g, u)) == -1) // koristim v da ne uvodim novu promenljivus
				printf("Ne postoji trazeni cvor\n");
			else printf("Ulazni stepen je %d\n", v);
			break;

		case 5: 
			printf("Unesite cvor ciji izlazni stepen zelite da racuante\n");
			scanf("%d", &u);

			if ((v = OutputDegree(&g, u)) == -1)
				printf("Ne postoji trazeni cvor\n");
			else printf("Izlazni stepen je %d\n", v);
			break;
		case 6:
			printf("Unesite cvorove za koje hocete da proverite dostiznost\n");
			scanf("%d%d", &u, &v);

			if (Adjacent(&g, u, v) || Adjacent(&g, v, u))
				printf("\nDostizni su\n");
			else printf("Nisu dostizni\n");
			break;
		case 7: 
			if (!(u = StronglyConnected(&g)))
				printf("Greska\n");
			else printf("Broj jako povezanih komponenti %d\n", u);
			break;
		default: printf("Ponovo unesite izbor\n");
		}
		MenuOutput(&choice);
	}

	DeleteGraph(&g);

	return 0;
}
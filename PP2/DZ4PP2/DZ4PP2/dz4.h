#ifndef _dz4_h_
#define _dz4_h_
#define _CRT_SECURE_NO_DEPRECATE
typedef struct Node Node;
typedef struct Node *NodePt;

struct  Node {
	char name[30];
	int mass, start, finish, inElevator, reach;
	NodePt next;
};

// brise sve elemente iz date liste
void DeleteList(NodePt *ptList);

// ucitava listu
// vraca 1 ako je uspesno ucitavanje 
// vraca 0 ako je neuspesno
int InputList(NodePt *ptList, int element);

// dodaje element na kraj liste 
// vraca 1 ako je uspesno dodavanje
// vraca 0 ako je neuspesno
int PushBack(NodePt *ptList, char name[], int mass, int start, int finish);

// dodaje element na pocetak liste
// vraca 1 ako je uspesno dodavanje
// vraca 0 ako je neuspesno dodavanje
int PushFront(NodePt *ptList, char name[], int mass, int start, int finish);

// brise dati element iz liste
void Delete(NodePt *ptList, char name[]);

// brise sve elemente iz liste
void DeleteList(NodePt *ptList);

// ispisuje datu listu
void OutputList(NodePt list);

// utovara i istovara putnike ako se njihov sprat nalazi na relaciji
void ListLoading(NodePt list, int maxMass, int startFloor, int finishFloor);



#endif
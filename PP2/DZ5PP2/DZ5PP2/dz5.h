#ifndef _dz5_h_
#define _dz5_h_
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NodeSong NodeSong;

typedef struct NodeSong *NodeSongPt;

struct NodeSong {
	char *artistName, *songName, *path; // ime izvodjaca i pesma
	int length; // duzina pesme
};

typedef struct Node Node;

typedef struct Node *NodePt;

struct Node {
	NodePt prev, next; // pokazivaci na sledeci i prethodni cvor u dvostruko povezanoj listi
	NodeSongPt song; // pokazivac na strukturu pesma
};

// los broj argumenata
void BadArgumentNum();

// nedovoljno memorije
void NotEnoughMemory();

// lose citanje iz datoteke
void BadRead();

// loce pisanje datoteke
void BadWrite();

// ispisuje trenutno vreme
void PrintCurrentTime();

// cita iz datoteke dok ne dodje do datog znaka
char *ReadStrSgn(FILE *f, char sign);

// cita strukturu pesma iz fajla f, vraca NULL ako je doslo do kraja
NodeSongPt ReadSong(FILE *f);

//dodaje pesmu u listu (oprezno, ne pravi kopiju od *songPt)
void AddNode(NodePt *list, NodeSongPt songPt);

// cita datoteku tipa M3U
void ReadM3U(char *inFileName, NodePt *list);

// pravi trecu listu od dve 
void Procc(NodePt list1, NodePt list2, NodePt *listOut);

// pise pesmu u dati format
void WriteSong(FILE *f, NodeSongPt songPt);

// pise listu u ASX formatu
void WriteASX(char *outFileName, NodePt list);

// vraca broj cvorova u datoj listi
int NumNumber(NodePt list);

// duzina liste
int LengthPlaylist(NodePt list);

//vraca pokazivac na ime  sa najvise numera
char *NameMostNumera(NodePt list);

// brise listu M3U tipa
void DeleteM3U(NodePt *list);

// brise listu .asx tipa
void DeleteASX(NodePt *list);

#endif
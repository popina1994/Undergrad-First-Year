#include "dz5.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
char *ReadStrSgn(FILE *f, char sign) {
	char *str = NULL, c;
	int len = 0;
	if ((str = (char*)malloc(10*sizeof(char))) == NULL) NotEnoughMemory();
	str[0] = '\0';
	while (c = fgetc(f)) {
		if (c == sign && c != '-')
			break; // '\n'
		if (c == '-' && str[len - 1] == ' ')
			break; // dvostruko ime
		if ((len + 1) % 10 == 0)
			str = (char*)realloc(str, (len + 11) * sizeof(char));
		str[len++] = c;
		str[len] = '\0';
	}
	return str;
}


NodeSongPt ReadSong(FILE *f) {
	NodeSongPt tmpNode;

	if (fgetc(f) == EOF) return NULL; // kraj datoteke

	tmpNode = (NodeSongPt)malloc(sizeof(NodeSong)); // memorija za novi cvor
	if (tmpNode == NULL) NotEnoughMemory();
	fscanf(f, "EXTINF:%d,", &(tmpNode->length)); // duzina pesme
	tmpNode->artistName = ReadStrSgn(f, '-');
	tmpNode->songName = ReadStrSgn(f, '\n');
	tmpNode->path = ReadStrSgn(f, '\n');

	return tmpNode;
}



void ReadM3U(char *inFileName, NodePt *list) {
	FILE *f;
	NodeSongPt songPt;
	
	if ((f = fopen(inFileName, "r")) == NULL) BadRead();
	*list = NULL;

	fscanf(f, "#EXTM3U\n"); // pocetna ekstenzija
	while ((songPt = ReadSong(f)) != NULL)  // dok citas
		AddNode(list, songPt); // 

	fclose(f);
}


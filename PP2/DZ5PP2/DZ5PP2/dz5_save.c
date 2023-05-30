#include "dz5.h"
#include "dz5.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void WriteSong(FILE *f, NodeSongPt songPt) {
	int cal;
	fprintf(f, "<Entry>\n");
	fprintf(f, "<Title>\"%s-%s\"</Title>\n", songPt->artistName, songPt->songName);
	fprintf(f, "<Ref href = \"%s\"/>\n", songPt->path);
	fprintf(f, "<//Entry>\n\n");
}

void WriteASX(char *outFileName, NodePt list) {
	FILE *out;

	out = fopen(outFileName, "w");
	if (out == NULL) BadWrite();

	fprintf(out, "<Asx Version = \"3.0\" >\n\n");

	while (list != NULL) {
		WriteSong(out, list->song);
		list = list->next;
	}

	fprintf(out, "</Asx>");
}
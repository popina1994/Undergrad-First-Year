#include "spisci.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void WriteStudent(FILE *f, NodePt nodePt, int cnt) {
	fprintf(f, "%-3d %.2s %s %s %s\n", cnt, nodePt->info->index, nodePt->info->index + 2, nodePt->info->name, nodePt->info->surName);
}

void WriteSTD(NodePt list){
	NodePt end;
	int cnt = 0;

	end = End(list);

	for (cnt = 0; end != NULL; cnt++) {
		WriteStudent(stdout, end, cnt);
		end = end->prev;
	}
}
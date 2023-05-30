#include "dz4.h"
#include <stdio.h>

void OutputList(NodePt list) {
	int cnt;
	
	for (cnt = 0; list != NULL; cnt++) {
		printf("%d Ime: %s masa %d pocetni %d krajnji %d\n", cnt, list->name, list->mass, list->start, list->finish);
		list = list->next;
	}
}
#include "dz5.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Procc(NodePt list1, NodePt list2, NodePt *listOut) {
	NodePt list2tmp = list2; // privremeno smestanje pokazivaca na drugu listu

	*listOut = NULL; // pocetak
	for (; list1 != NULL; list1 = list1->next)
		for (list2 = list2tmp; list2 != NULL; list2 = list2->next) {
		if (strcmp(list1->song->songName, list2->song->songName) == 0)
			AddNode(listOut, list1->song);
		}
}

int NumNumber(NodePt list) {
	int cnt;

	for (cnt = 0; list != NULL; list = list->next)
		cnt++;
	return cnt;
}


int LengthPlaylist(NodePt list) {
	int length;
	for (length = 0; list != NULL; list = list->next) {
		length += list->song->length;
	}
	return length;
}

char *NameMostNumera(NodePt list) {
	char  *mostName = NULL, *curName = NULL;
	int  curCnt, mostCnt = 0;
	NodePt iterator1, iterator2;
	
	for (iterator1 = list; iterator1 != NULL; iterator1 = iterator1->next) {
		curName = iterator1->song->artistName;
		// nije prvi u listi i nije razlicit od imena prethodnika
		curCnt = 0;
		for (iterator2 = iterator1; iterator2 != NULL; iterator2 = iterator2->next) // ako postoji pre vec je izbrojan
			if (strcmp(curName, iterator2->song->artistName) == 0)
				curCnt++;

		if (curCnt > mostCnt) {
			mostName = curName;
			mostCnt = curCnt;
		}
	}

	return mostName;
}
	
void DeleteM3U(NodePt *list) {
	NodePt tmpPt;
	while (*list != NULL) {
		free((*list)->song->artistName);
		free((*list)->song->path);
		free((*list)->song->songName);
		tmpPt = *list;
		*list = (*list)->next;
		free(tmpPt);
	}
}

void DeleteASX(NodePt *list) {
	NodePt tmpPt;
	while (*list != NULL) {
		tmpPt = *list;
		*list = (*list)->next;
		free(tmpPt);
	}
}
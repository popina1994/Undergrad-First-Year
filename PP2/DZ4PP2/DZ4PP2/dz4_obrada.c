#include "dz4.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void DeleteList(NodePt *ptList) {
	NodePt ptTmp;
	while (*ptList != NULL) {
		ptTmp = *ptList;
		*ptList = (*ptList)->next; // brisi prvi cvor u listi
		free(ptTmp);
	}
}

void Delete(NodePt *ptList, char name[]) {
	NodePt ptTmp, ptTmp2; // pomocni pokazivac

	if (*ptList == NULL)
		return;
	
	ptTmp = *ptList;
	if (strcmp((*ptList)->name, name) == 0) {
		*ptList = (*ptList)->next;
		free(ptTmp);
		return;
	}

	while (ptTmp->next != NULL && (strcmp(ptTmp->next->name, name) != 0))
		ptTmp = ptTmp->next;
	if (ptTmp->next == NULL) {
		printf("Nema datog elementa u listi\n");
		return;
	}
	ptTmp2 = ptTmp->next;
	ptTmp->next = ptTmp2->next;
	free(ptTmp2);
	printf("Uspesno izvrseno brisanje\n");
	return;
}

void ListLoading(NodePt list, int maxMass, int startFloor, int finishFloor) {
	int cntFloor, currentMass = 0;
	NodePt  ptTour;// prolazi po listi

	
	if (startFloor < finishFloor) 
		for (cntFloor = startFloor; cntFloor <= finishFloor; cntFloor++) {
			for (ptTour = list; ptTour != NULL; ptTour = ptTour->next)
				if (ptTour->finish == cntFloor && ptTour->inElevator){ // u liftu i treba da izadje
					ptTour->reach = 1;
					ptTour->inElevator = 0;
					currentMass -= ptTour->mass;
					
				}

			for (ptTour = list; ptTour != NULL; ptTour = ptTour->next) 
				if (ptTour->start == cntFloor && ptTour->finish > cntFloor && ptTour->finish <= finishFloor &&  // uslovi za sprat
					!ptTour->inElevator && ptTour->mass + currentMass <= maxMass && !ptTour->reach){// uslovi da nije usao u lift i da moze da udje u lift
					ptTour->inElevator = 1; // usao u lift
					currentMass += ptTour->mass;
				}
			printf("U liftu su trenutno na spratu %d\n", cntFloor);
			for (ptTour = list; ptTour != NULL; ptTour = ptTour->next)
				if (ptTour->inElevator)
					printf("%s\n", ptTour->name);
		}
	else if (startFloor > finishFloor) 
		for (cntFloor = startFloor; cntFloor >= finishFloor; cntFloor--) {
		for (ptTour = list; ptTour != NULL; ptTour = ptTour->next)
			if (ptTour->finish == cntFloor && ptTour->inElevator){ // u liftu i treba da izadje
			ptTour->reach = 1;
			ptTour->inElevator = 0;
			currentMass -= ptTour->mass;
			}

		for (ptTour = list; ptTour != NULL; ptTour = ptTour->next)
			if (ptTour->start == cntFloor && ptTour->finish < cntFloor && ptTour->finish >= finishFloor &&  // uslovi za sprat
				!ptTour->inElevator && ptTour->mass + currentMass <= maxMass && !ptTour->reach){// uslovi da nije usao u lift i da moze da udje u lift
			ptTour->inElevator = 1; // usao u lift
			currentMass += ptTour->mass;
			}
			printf("U liftu su trenutno na spratu %d\n", cntFloor);
			for (ptTour = list; ptTour != NULL; ptTour = ptTour->next)
				if (ptTour->inElevator)
					printf("%s\n", ptTour->name);
		}
}
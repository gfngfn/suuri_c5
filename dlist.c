#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

dlobj *dlobj_new(int c, data x) {
	dlobj *po;

	mymalloc(po, dlobj, 1);
	po->next = INDEPENDENT_DLOBJ;
	po->prev = INDEPENDENT_DLOBJ;
	po->col = c;
	po->v = x;

	return po;
}

dlist *dlist_new() {
	dlist *pl;
	dlobj *headofpl;

	headofpl = dlobj_new(0, 0.0);
	headofpl->next = headofpl;
	headofpl->prev = headofpl;

	mymalloc(pl, dlist, 1);
	pl->head = headofpl;

	return pl;
}

void dlist_append(dlist *pl, dlobj *pnewo) {

	pnewo->next = pl->head;
	pnewo->prev = pl->head->prev;
	pl->head->prev->next = pnewo;
	pl->head->prev = pnewo;

	return;
}

void dlist_free(dlist *pl) {
	dlobj *po, *ponx;

	po = pl->head->next;
	while(po != pl->head) {
		ponx = po->next;
		free(po);
		po = ponx;
	}
	free(pl->head);
	free(pl);

	return;
}


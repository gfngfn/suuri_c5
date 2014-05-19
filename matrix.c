#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

smatrix *smatrix_new(int rofsmt, int cofsmt) {
	smatrix *smt;
	dlist **dl;
	int i;

	mymalloc(smt, smatrix, 1);
	smt->row = rofsmt;
	smt->col = cofsmt;

	mymalloc(dl, dlist*, rofsmt);
	for(i = 0; i < rofsmt; i++) {
		dl[i] = dlist_new();
	}
	smt->root = dl;

	return smt;
}

void smatrix_insert(smatrix *smt, int insr, int insc, data x) {
	dlobj *po;

	po = dlobj_new(insc, x);
	dlist_append((smt->root)[insr], po);

	return;
}

smatrix *smatrix_transpose(smatrix *smt) {
	smatrix *smttrps;
	dlobj *po;
	int i, j;

	smttrps = smatrix_new(smt->col, smt->row);
	for(i = 0; i < smt->row; i++) {
		po = (smt->root)[i]->head->next;
		while(po != (smt->root)[i]->head) {
			smatrix_insert(smttrps, po->col, i, po->v);
			po = po->next;
		}
	}

	return smttrps;
}

void smatrix_print(smatrix* smt) {
	dlobj *po;
	int i, j, beginningofzero;

	for(i = 0; i < smt->row; i++) {
		printf("| ");
		po = ((smt->root)[i])->head->next;
		beginningofzero = 0;
		while(po != ((smt->root)[i])->head) {
			for(j = beginningofzero; j < po->col; j++) { printf("%lf ", 0.0); }
			printf("%lf ", po->v);
			beginningofzero = po->col+1;
			po = po->next;
		}
		for(j = beginningofzero; j < smt->col; j++) { printf("%lf ", 0.0); }
		printf("|\n");
	}

	return;
}

smatrix *smatrix_read(char *filename) {
	FILE *fp;
	smatrix *smt;
	int rofsmt, cofsmt, i, sci;
	data scf;

	myfopen(fp, filename, "r");

	fscanf(fp, "%d %d", &rofsmt, &cofsmt);

	smt = smatrix_new(rofsmt, cofsmt);
	for(i = 0; i < rofsmt; i++) {
		while(TRU) {
			fscanf(fp, "%d", &sci);
			if(sci == -1) {
				break;
			} else {
				if(sci < 1 || cofsmt < sci) {
					printf("[smatrix_read] file '%s' contains illegal data\n", filename);
					exit(EXIT_FAILURE);
				} else {
					fscanf(fp, "%lf", &scf);
					smatrix_insert(smt, i, sci-1, scf);
				}
			}
		}
	}

	fclose(fp);
	return smt;
}

void smatrix_write(char *filename, smatrix *smt) {
	FILE *fp;
	dlobj *po;
	int i;

	myfopen(fp, filename, "w");

	fprintf(fp, "%d %d\n", smt->row, smt->col);
	for(i = 0; i < smt->row; i++) {
		po = ((smt->root)[i])->head->next;
		while(po != ((smt->root)[i])->head) {
			fprintf(fp, "%d %lf ", (po->col)+1, po->v);
			po = po->next;
		}
		fprintf(fp, "%d\n", -1);
	}

	fclose(fp);
	return;
}

smatrix *smatrix_product(smatrix *smta, smatrix *smtb) {
	smatrix *smtc, *smtbtrps;
	dlobj *poa, *pobtrps;
	int i, j;
	double sum;

	if(smta->col != smtb->row) {
		printf("[smatrix_product] product undefined between (%d, %d) and (%d, %d)\n", smta->row, smta->col, smtb->row, smtb->col);
		return NULL;		
	} else {

		smtc = smatrix_new(smta->row, smtb->col);
		smtbtrps = smatrix_transpose(smtb);

		for(i = 0; i < smtc->row; i++) {
			for(j = 0; j < smtc->col; j++) {
				sum = 0.0;
				poa = ((smta->root)[i])->head->next;
				pobtrps = ((smtbtrps->root)[j])->head->next;
				/* a[i][k]*bt[j][k] */
				while(poa != ((smta->root)[i])->head && pobtrps != ((smtbtrps->root)[j])->head) {
					if(poa->col == pobtrps->col) {
						sum += poa->v * pobtrps->v;
						poa = poa->next;
						pobtrps = pobtrps->next;
					} else {
						if(poa->col < pobtrps->col) {
							poa = poa->next;
						} else {
							pobtrps = pobtrps->next;
						}
					}
				}
				if(sum != 0.0) {
					smatrix_insert(smtc, i, j, sum);
				}
			}
		}
	}

	return smtc;
}


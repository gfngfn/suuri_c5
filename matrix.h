#include "dlist.h"

typedef struct {
	int row, col;
	dlist **root;
} smatrix;

smatrix *smatrix_new(int, int);
void smatrix_insert(smatrix*, int, int, data);
smatrix *smatrix_transpose(smatrix*);
void smatrix_print(smatrix*);

smatrix *smatrix_read(char*);
void smatrix_write(char*, smatrix*);
smatrix *smatrix_product(smatrix*, smatrix*);


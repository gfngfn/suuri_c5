#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char *argv[]) {
	smatrix *a, *b, *c;

	if(argc != 4) {
		printf("[main] wrong number of arguments\n");
		return EXIT_FAILURE;
	} else {
		a = smatrix_read(argv[1]);
		printf("A:\n"); smatrix_print(a);
		b = smatrix_read(argv[2]);
		printf("B:\n"); smatrix_print(b);
		c = smatrix_product(a, b);
		printf("C:\n"); smatrix_print(c);
		smatrix_write(argv[3], c);
		return EXIT_SUCCESS;
	}
}


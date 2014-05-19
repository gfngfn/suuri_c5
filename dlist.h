#ifndef MyStandardDefinition
#define MyStandardDefinition 0
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define TRU 1
#define FLS 0
typedef int BOOL;
#define mymalloc(p, type, n) {\
	p = (type*)malloc(sizeof(type) * n);\
	if(p == NULL) {\
		printf("[mymalloc] not enough memories\n");\
		exit(EXIT_FAILURE);\
	}\
}
#define myfopen(fp, fn, m) {\
	fp = fopen(fn, m);\
	if(fp == NULL) {\
		printf("[myfopen] cannot open file '%s'\n", fn);\
		exit(EXIT_FAILURE);\
	}\
}
#endif

#define INDEPENDENT_DLOBJ NULL

#define DLOBJ_NOT_FOUND NULL

typedef double data;

typedef struct dlobj_ {
	struct dlobj_ *next;
	struct dlobj_ *prev;
	int col;
	data v;
} dlobj;

typedef struct {
	dlobj *head;
} dlist;

dlobj *dlobj_new(int, data);
dlist *dlist_new();
void dlist_append(dlist*, dlobj*);
void dlist_free(dlist*);


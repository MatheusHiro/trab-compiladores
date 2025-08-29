#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>

#define HASH_SIZE 997

#define SYMBOL_IDENTIFIER 1
#define SYMBOL_VAR 2
#define SYMBOL_VEC 3
#define SYMBOL_FUNC 4
#define SYMBOL_CHAR 5
#define SYMBOL_INT 6
#define SYMBOL_FLOAT 7
#define SYMBOL_STRING 8
#define SYMBOL_LABEL 9

#define DATATYPE_INTE 1
#define DATATYPE_FLOAT 2
#define DATATYPE_CARA 3
#define DATATYPE_BOOL 4


typedef struct hash_node
{
	int type;
	int dataType;
	char *text;
	struct hash_node *next;
	
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
int hashCheckUndeclared(void);
HASH_NODE *makeTemp(void);
HASH_NODE *makeLabel(void);

#endif


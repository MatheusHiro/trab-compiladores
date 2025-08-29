// AST

#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"
#define MAX_SONS 4

enum ast_types{
	AST_SYMBOL = 1,
	AST_ADD,
	AST_SUB,
	AST_MUL,
	AST_DIV,
	AST_LST,
	AST_GRT,
	AST_LE,
	AST_GE,
	AST_EQ,
	AST_DIF,
	AST_AND,
	AST_OR,
	AST_TIL,
	AST_FUN,
	AST_ARG,
	AST_VEC,
	AST_ENTRADA,
	AST_DECL,
	AST_DECVAR,
	AST_DECVEC,
	AST_VELE,
	AST_DECF,
	AST_BODY,
	AST_PARAM,
	AST_LCMD,
	AST_ASS,
	AST_ASS_VEC,
	AST_ESCREVA,
	AST_RETORNE,
	AST_SE,
	AST_SENAUM,
	AST_ENQUANTO,
	AST_LELE,
	AST_LARG,
	AST_INTE,
	AST_REAL,
	AST_CARA,

};

typedef struct astnode
{
	int type;
	HASH_NODE *symbol;
	struct astnode *son[MAX_SONS];
	int dataType;
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);
void astDescompila(AST *node);
void printAsm(FILE *fout, AST *node);
void addDataVarHash(AST *node);



#endif
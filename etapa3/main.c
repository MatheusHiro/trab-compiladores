#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

void initMe();
extern int lineNumber;
extern FILE *yyin;
extern int yyparse();
typedef struct ast_node AST;
extern FILE *yyout;
extern void astDescompila(AST *node);
extern AST *ASTroot;

int main(int argc, char **argv)
{
	int tok;

	if(argc < 3)
	{
		fprintf(stderr, "Call: ./a.out file_name\n");
		exit(1);
	}

	if((yyin = fopen(argv[1], "r")) == NULL)
	{
		printf("Failed to open file %s\n", argv[1]);
		exit(2);
	}

	if((yyout = fopen(argv[2], "w")) == NULL)
	{
		printf("Failed to open file %s\n", argv[2]);
		exit(2);
	}

	initMe();

	yyparse();
	hashPrint();
	astDescompila(ASTroot);

	printf("Main done, file has %d lines\n", lineNumber);
	exit(0);
}
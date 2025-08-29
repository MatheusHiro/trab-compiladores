// AST

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyout;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3) {
	AST *newnode;
	newnode = (AST*) calloc(1, sizeof(AST));
	newnode->type = type;
	newnode->symbol = symbol;
	newnode->son[0] = s0;
	newnode->son[1] = s1;
	newnode->son[2] = s2;
	newnode->son[3] = s3;

	return newnode;
}

void astPrint(AST *node, int level) {

	if(!node) return;
	int i;
	for (int i = 0; i < level; ++i){
		fprintf(stderr, " ");
	}
	fprintf(stderr, "ast(");
	switch(node->type){
		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
		case AST_ADD: fprintf(stderr, "AST_ADD"); break;
		case AST_SUB: fprintf(stderr, "AST_SUB"); break;
		case AST_MUL: fprintf(stderr, "AST_MUL"); break;
		case AST_DIV: fprintf(stderr, "AST_DIV"); break;
		case AST_LST: fprintf(stderr, "AST_LST"); break;
		case AST_GRT: fprintf(stderr, "AST_GRT"); break;
		case AST_LE: fprintf(stderr, "AST_LE"); break;
		case AST_GE: fprintf(stderr, "AST_GE"); break;
		case AST_EQ: fprintf(stderr, "AST_EQ"); break;
		case AST_DIF: fprintf(stderr, "AST_DIF"); break;
		case AST_AND: fprintf(stderr, "AST_AND"); break;
		case AST_OR: fprintf(stderr, "AST_OR"); break;
		case AST_TIL: fprintf(stderr, "AST_TIL"); break;
		case AST_FUN: fprintf(stderr, "AST_FUN"); break;
		case AST_ARG: fprintf(stderr, "AST_ARG"); break;
		case AST_VEC: fprintf(stderr, "AST_VEC"); break;
		case AST_ENTRADA: fprintf(stderr, "AST_ENTRADA"); break;
		case AST_DECL: fprintf(stderr, "AST_DECL"); break;
		case AST_DECVAR: fprintf(stderr, "AST_DECVAR"); break;
		case AST_DECVEC: fprintf(stderr, "AST_DECVEC"); break;
		case AST_VELE: fprintf(stderr, "AST_VELE"); break;
		case AST_DECF: fprintf(stderr, "AST_DECF"); break;
		case AST_BODY: fprintf(stderr, "AST_BODY"); break;
		case AST_PARAM: fprintf(stderr, "AST_PARAM"); break;
		case AST_LCMD: fprintf(stderr, "AST_LCMD"); break;
		case AST_ASS: fprintf(stderr, "AST_ASS"); break;
		case AST_ESCREVA: fprintf(stderr, "AST_ESCREVA"); break;
		case AST_RETORNE: fprintf(stderr, "AST_RETORNE"); break;
		case AST_SE: fprintf(stderr, "AST_SE"); break;
		case AST_SENAUM: fprintf(stderr, "AST_SENAUM"); break;
		case AST_ENQUANTO: fprintf(stderr, "AST_ENQUANTO"); break;
		case AST_LELE: fprintf(stderr, "AST_LELE"); break;
		case AST_LARG: fprintf(stderr, "AST_LARG"); break;
		case AST_INTE: fprintf(stderr, "AST_INTE"); break;
		case AST_REAL: fprintf(stderr, "AST_REAL"); break;
		case AST_CARA: fprintf(stderr, "AST_CARA"); break;
		default: fprintf(stderr, "AST_UNKNOWN"); break;

	}
	if (node->symbol){
		fprintf(stderr,",%s\n", node->symbol->text);
	} else {
		fprintf(stderr, ")\n");
	}
	for (i = 0; i < MAX_SONS; ++i)
	{
		astPrint(node->son[i], level+1);
	}


}

void astDescompila(AST *node){
	
	if(!node) return;

	switch(node->type){
		case AST_SYMBOL: fprintf(yyout, "%s", node->symbol->text); break;
		case AST_ADD: astDescompila(node->son[0]);
			fprintf(yyout, " + ");
			astDescompila(node->son[1]);
			break;

		case AST_SUB: astDescompila(node->son[0]);
			fprintf(yyout, " - ");
			astDescompila(node->son[1]);
			break;

		case AST_MUL: astDescompila(node->son[0]);
			fprintf(yyout, " * ");
			astDescompila(node->son[1]);
			break;

		case AST_DIV: astDescompila(node->son[0]);
			fprintf(yyout, " / ");
			astDescompila(node->son[1]);
			break;

		case AST_LST: astDescompila(node->son[0]);
			fprintf(yyout, " < ");
			astDescompila(node->son[1]);
			break;

		case AST_GRT: astDescompila(node->son[0]);
			fprintf(yyout, " > ");
			astDescompila(node->son[1]);
			break;

		case AST_LE: astDescompila(node->son[0]);
			fprintf(yyout, " <= ");
			astDescompila(node->son[1]);
			break;

		case AST_GE: astDescompila(node->son[0]);
			fprintf(yyout, " >= ");
			astDescompila(node->son[1]);
			break;

		case AST_EQ: astDescompila(node->son[0]);
			fprintf(yyout, " == ");
			astDescompila(node->son[1]);
			break;

		case AST_DIF: astDescompila(node->son[0]);
			fprintf(yyout, " != ");
			astDescompila(node->son[1]);
			break;

		case AST_AND: astDescompila(node->son[0]);
			fprintf(yyout, " & ");
			astDescompila(node->son[1]);
			break;

		case AST_OR: astDescompila(node->son[0]);
			fprintf(yyout, " | ");
			astDescompila(node->son[1]);
			break;

		case AST_TIL: astDescompila(node->son[0]);
			fprintf(yyout, " ~ ");
			astDescompila(node->son[1]);
			break;

		case AST_FUN: fprintf(yyout, "%s(", node->symbol->text);
		    astDescompila(node->son[0]);
			fprintf(yyout, ")");
			break;

		case AST_ARG: fprintf(yyout, "(");
			astDescompila(node->son[0]);
			fprintf(yyout, ")");
			break;

		case AST_VEC: fprintf(yyout, "%s[", node->symbol->text);
			astDescompila(node->son[0]);
			fprintf(yyout, "]");
			break;

		case AST_ENTRADA: fprintf(yyout, "entrada"); break;

		case AST_DECL: astDescompila(node->son[0]);
			if(node->son[1])
				astDescompila(node->son[1]);
			break;

		case AST_DECVAR: astDescompila(node->son[0]);
			fprintf(yyout, "%s = ", node->symbol->text);
			astDescompila(node->son[1]);
			fprintf(yyout, ";\n");
			break;

		case AST_DECVEC: astDescompila(node->son[0]);
			fprintf(yyout, "%s", node->symbol->text);
			if(node->son[2]){
				fprintf(yyout, "[%s] ", node->son[1]->symbol->text);
				astDescompila(node->son[2]);
				fprintf(yyout, ";\n");
				break;
			}
			fprintf(yyout, "[%s]", node->son[1]->symbol->text);
			fprintf(yyout, ";\n");
			break;

		case AST_VELE: astDescompila(node->son[0]);
			if(node->son[1]){
				fprintf(yyout, " ");
				astDescompila(node->son[1]);
			} else
				fprintf(yyout, ";\n");
			break;

		case AST_DECF: astDescompila(node->son[0]);
			fprintf(yyout, "%s", node->symbol->text);
			if(node->son[1]){
				fprintf(yyout, "(");
				astDescompila(node->son[1]);
				fprintf(yyout, ")");
			} else
				fprintf(yyout, "()");
			if(node->son[2])
				astDescompila(node->son[2]);
			break;

		case AST_BODY: fprintf(yyout, "{\n");
			astDescompila(node->son[0]);
			fprintf(yyout, "}\n");
			break;

		case AST_PARAM: astDescompila(node->son[0]);
			fprintf(yyout, "%s", node->symbol->text);
			if(node->son[1]){
				fprintf(yyout, " ");
				astDescompila(node->son[1]);
			}
			break;

		case AST_LCMD: astDescompila(node->son[0]);
			fprintf(yyout, ";\n");
			if(node->son[1]){
				astDescompila(node->son[1]);
			}
			break;

		case AST_ASS: fprintf(yyout, "%s", node->symbol->text);
			if(node->son[1]) {
				fprintf(yyout, "[");
				astDescompila(node->son[0]);
				fprintf(yyout, "]");
			}
			fprintf(yyout, " = ");
			if(node->son[1]) {
				astDescompila(node->son[1]);
			} else
				astDescompila(node->son[0]);
			break;

		case AST_ESCREVA: fprintf(yyout, "escreva "); 
			astDescompila(node->son[0]);
			break;
		case AST_RETORNE: fprintf(yyout, "retorne "); 
			astDescompila(node->son[0]);
			break;

		case AST_SE: fprintf(yyout, "entaum");
			astDescompila(node->son[0]);
			fprintf(yyout, "se(");
			astDescompila(node->son[1]);
			fprintf(yyout, ")");
			break;

		case AST_SENAUM: fprintf(yyout, "entaum");
			astDescompila(node->son[0]);
			fprintf(yyout, "senaum ");
			astDescompila(node->son[1]);
			fprintf(yyout, " se(");
			astDescompila(node->son[2]);
			fprintf(yyout, ")");
			break;

		case AST_ENQUANTO: astDescompila(node->son[0]);
			fprintf(yyout, "enquanto(");
			astDescompila(node->son[1]);
			fprintf(yyout, ")");
			break;

		case AST_LELE: astDescompila(node->son[0]);
			if(node->son[1]){
				fprintf(yyout, " ");
				astDescompila(node->son[1]);
			}
			break;

		case AST_LARG: astDescompila(node->son[0]);
			if(node->son[1]){
				fprintf(yyout, " ");
				astDescompila(node->son[1]);
			}
			break;
			
		case AST_INTE: fprintf(yyout, "inte "); break;
		case AST_REAL: fprintf(yyout, "real "); break;
		case AST_CARA: fprintf(yyout, "cara "); break;

	}

}



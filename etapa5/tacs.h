#ifndef TACS_HEADER
#define TACS_HEADER

#include <stdio.h>
#include "hash.h"
#include "ast.h"

enum tac_type{
    TAC_SYMBOL = 1,
    TAC_ADD,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,
    TAC_LST,
    TAC_GRT,
    TAC_LE,
    TAC_GE,
    TAC_EQ,
    TAC_DIF,
    TAC_AND,
    TAC_OR,
    TAC_TIL,
    TAC_MOVE,
    TAC_IFZ, 
    TAC_LABEL,
    TAC_BEGINFUN,
    TAC_ENDFUN,
    TAC_JUMP,
    TAC_CALL,
    TAC_ARG,
    TAC_RET,
    TAC_ENTRADA,
    TAC_MOVE_VEC,
    TAC_VEC, 
    TAC_LELE, 
    TAC_VELE, 
    TAC_VECINDEX,
    TAC_DECVAR

};

typedef struct tac_node{
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_node *next;
    struct tac_node *prev;

} TAC;

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
void tacPrintSingle(TAC *tac);
void tacPrintBackwards(TAC *tac);
TAC *tacJoin(TAC *l1, TAC *l2);
TAC *generateCode(AST *node);


#endif
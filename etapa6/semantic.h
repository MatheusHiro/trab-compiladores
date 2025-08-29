#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "ast.h"
#include "hash.h"

extern int SemanticErrors;

void check_and_set_declarations(AST *node);
void set_types(AST *node);
void check_undeclared(void);
int validate_arithmetic_operand(AST *node);
void check_usage(AST *node);
void check_vector_size(AST *node);
int check_vector_elements(int father_dataType, AST *node);
int check_compatibility(int father_dataType, AST *node2);
int get_elements_qty(AST *node, int size);
int is_float(int father_dataType, AST *node2);
int is_int_or_char(int father_dataType, AST *node2);
void verify_escalares();
AST *findDeclaration(char *name, AST *nome);

#endif
#include "semantic.h"
#include <stdlib.h>

int SemanticErrors = 0;
AST *root;

int check_semantic(AST *node){
    root = node;

    check_and_set_declarations(root);
    set_node_types(root);
    check_undeclared();
    check_usage(root);

    return SemanticErrors;
}


void run_vector(int father_datatype, AST *vector,AST *node);
int isAritmeticOp(int type);
int isComparisonOp(int type);
int isLogicalOp(int type);
int get_dataType(int type1, int type2);
int check_dataType_compatibility(int dataType1, int dataType2);
void check_function(AST *node);
int check_arguments_qty(AST *node, AST *declaration);
void check_arguments(AST* node, AST *declaration);
int get_arguments_qty(AST *node);
void check_return(AST *node, int type, AST *body);

void check_and_set_declarations(AST *node) {
    
    int i;
    int father_dataType = 0;
    if (!node)
        return;

    switch (node->type){
        case AST_DECVAR: 
            if(node->symbol) {
                if(node->symbol->type != SYMBOL_IDENTIFIER){
                    fprintf(stderr,"Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                } else {
                    node->symbol->type = SYMBOL_VAR;
                    set_types(node);

                    if(node->son[1])
                        father_dataType = node->symbol->dataType;
                        if(!(check_compatibility(father_dataType, node->son[1]))){
                            fprintf(stderr,"Semantic ERROR: value attributed %s in declaration does not match variable type\n", node->son[1]->symbol->text);
                            SemanticErrors++;
                        }   
                }
            }
            break;
        
        case AST_DECVEC:
            if(node->symbol) {
                if(node->symbol->type != SYMBOL_IDENTIFIER){
                    fprintf(stderr,"Semantic ERROR: vector %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                } else {
                    node->symbol->type = SYMBOL_VEC;
                    set_types(node);
                    check_vector_size(node);
                    father_dataType = node->symbol->dataType;
                    if(!check_vector_elements(father_dataType, node->son[2]))
                    {
                        fprintf(stderr,"Semantic ERROR: vector elements must have the same type as vector\n");
                        SemanticErrors++;
                    }
                    AST *vector = node;
                    run_vector(father_dataType, vector,node->son[2]);

                }

  
            }
            break;

        case AST_DECF:
            if(node->symbol) {
                if(node->symbol->type != SYMBOL_IDENTIFIER){
                    fprintf(stderr,"Semantic ERROR: function %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                } else {
                    node->symbol->type = SYMBOL_FUNC;
                    set_types(node);
                
                }
            }
            check_return(node, node->symbol->dataType, node->son[2]->son[0]);
            break;
    }

    for(i = 0; i<MAX_SONS; i++){
        check_and_set_declarations(node->son[i]);
    }
}

void set_types(AST *node){
    if(node->son[0]){
        switch (node->son[0]->type){
            case AST_CARA:
                node->symbol->dataType = DATATYPE_CARA;
                break;
            case AST_REAL:
                node->symbol->dataType = DATATYPE_FLOAT;
                break;
            case AST_INTE:
                node->symbol->dataType = DATATYPE_INTE;
                break;        
        }
    }


}

void check_undeclared(){
    SemanticErrors += hashCheckUndeclared();
}

void check_usage(AST *node){

    int i;
    int father_dataType = 0;

    if (!node)
        return;

    switch (node->type)
    {
        case AST_ASS:

            if(node->symbol){
                if(node->symbol->type != SYMBOL_VAR){
                    fprintf(stderr, "Semantic ERROR: Identifier %s must be scalar!\n", node->symbol->text);
                    SemanticErrors++;
                }
                father_dataType = node->symbol->dataType;
                if(!check_compatibility(father_dataType, node->son[0])){
                    fprintf(stderr, "Semantic ERROR: value attributed %s does not match variable type\n", node->symbol->text);
                    SemanticErrors++;
                }
            }
            break;
        
        case AST_ASS_VEC:

            if(node->symbol){
                if(node->symbol->type != SYMBOL_VEC){
                    fprintf(stderr, "Semantic ERROR: can only index vectors!\n");
                    SemanticErrors++;
                }
                father_dataType = node->symbol->dataType;
                if(!check_compatibility(father_dataType, node->son[1])){
                    fprintf(stderr,"Semantic ERROR: value attributed must match vector type!\n");
                    SemanticErrors++;
                }
                if(!is_int_or_char(father_dataType, node->son[0])){
                    fprintf(stderr,"Semantic ERROR: index must have be an integer!\n");
                    SemanticErrors++;
                }

            }
            break;

        case AST_VEC:

            if(node->son[0]->dataType != DATATYPE_CARA && node->son[0]->dataType != DATATYPE_INTE){
                fprintf(stderr,"Semantic ERROR: index must have be an integer or char!\n");
                SemanticErrors++;      
            }
            break;   

        case AST_FUN:
            check_function(node);
            break;

        case AST_ENTRADA:
            if (node->symbol->type != SYMBOL_VAR){
                fprintf(stderr, "Semantic ERROR: can only read variables!\n");
                SemanticErrors++;
            }

            break;

        case AST_SE:
        case AST_ENQUANTO:  
            if(node->son[1]->dataType != DATATYPE_BOOL) {
                fprintf(stderr, "Semantic ERROR: condition must be boolean!\n");
                SemanticErrors++;
            }
            break;
        case AST_SENAUM:
            if(node->son[2]->dataType != DATATYPE_BOOL) {
                fprintf(stderr, "Semantic ERROR: condition must be boolean!\n");
                SemanticErrors++;
            }
            break;
        }

 
    
    
    for(i = 0; i<MAX_SONS; i++){
        check_usage(node->son[i]);
    }    
}

void check_vector_size(AST *node){
    if(!node->son[1]) return;
    if(!node->son[2]) return;

    int qty = get_elements_qty(node->son[2], 0);
    if(!node->son[1]->symbol) return;
    if(atoi(node->son[1]->symbol->text) != qty)
        fprintf(stderr,"Semantic ERROR: vector size must be the same as the number of elements in declaration\n");
        SemanticErrors++;
}

int get_elements_qty(AST *node, int size){
    if(node != 0){
        return get_elements_qty(node->son[1], size + 1);
        if(node->son[1] != 0) return size;
    }
    return size;
}

int check_vector_elements(int father_dataType, AST *node){
	if(node) {
        if(node->son[0])
		    if(!(check_compatibility(father_dataType, node->son[0]))) return 0;
		if(node->son[1]) return check_vector_elements(father_dataType, node->son[1]);
	}

	return 1;
}

void run_vector(int father_dataType, AST *vector,AST *node){

	if(node) {
        addVecEle(vector->symbol, node->son[0]->symbol?node->son[0]->symbol->text:0);
        run_vector(father_dataType, vector,node->son[1]);
	}

}

int is_int_or_char(int father_dataType, AST *node2){
    int son_dataType = node2->symbol->dataType;
    if(((son_dataType == DATATYPE_CARA) && (father_dataType == DATATYPE_INTE)) || ((father_dataType == DATATYPE_CARA) && (son_dataType == DATATYPE_INTE)) || ((son_dataType == father_dataType) && ((son_dataType != DATATYPE_FLOAT) && (father_dataType!=DATATYPE_FLOAT))))
        return 1;
    else 
        return 0;
}

int is_float(int father_dataType, AST *node2){
    int son_dataType = node2->symbol->dataType;

    if((son_dataType == DATATYPE_FLOAT) && (father_dataType == DATATYPE_FLOAT))
        return 1;
    else 
        return 0;
}

int check_compatibility(int father_dataType, AST *node2){
    if((is_int_or_char(father_dataType, node2)) || (is_float(father_dataType, node2))){
        return 1;
    }else 
        return 0;
}

int check_dataType_compatibility(int dataType1, int dataType2){
    if((((dataType1 == DATATYPE_CARA) && (dataType2 == DATATYPE_INTE)) || ((dataType1 == DATATYPE_CARA) && (dataType2 == DATATYPE_INTE)) || ((dataType1 == dataType2) && ((dataType1 != DATATYPE_FLOAT) && (dataType2!=DATATYPE_FLOAT)))) || ((dataType1 == DATATYPE_FLOAT) && (dataType2 == DATATYPE_FLOAT)))
        return 1;
    else
        return 0;
}

int isAritmeticOp(int type){
    return (type == AST_ADD || type == AST_SUB || type == AST_MUL || type == AST_DIV);
}

int isComparisonOp(int type){
    return (type == AST_LST || type == AST_GRT || type == AST_GE || type == AST_LE || type == AST_EQ || type == AST_DIF);
}

int isLogicalOp(int type){
    return (type == AST_AND || type == AST_OR || type == AST_TIL);
}

void set_node_types(AST *node){
    if(!node) 
        return;

    for(int i = 0; i<MAX_SONS; i++){
        set_node_types(node->son[i]);
    }

    if(node->type == AST_SYMBOL){
        if (node->symbol->type == SYMBOL_VEC || node->symbol->type == SYMBOL_FUNC){
            fprintf(stderr, "Semantic ERROR: function or vector used as scalar variable!\n");
            SemanticErrors++;
        }

        node->dataType = node->symbol->dataType; 
        
    } else if(node->type == AST_FUN || node->type == AST_VEC) {
        node->dataType = node->symbol->dataType; 
    } else if (node->type == AST_ARG) {
        node->dataType = node->son[0]->dataType;
    } else if(isAritmeticOp(node->type)) {
        AST *son0 = node->son[0];
        AST *son1 = node->son[1];

        if(!check_dataType_compatibility(son0->dataType, son1->dataType) || son0->dataType == DATATYPE_BOOL || son1->dataType == DATATYPE_BOOL){
            fprintf(stderr, "Semantic ERROR: operators must be compatible and cannot be boolean!\n");
            SemanticErrors++;
        }

        node->dataType = get_dataType(son0->dataType, son1->dataType);
    } else if(isComparisonOp(node->type)) {
        AST *son0 = node->son[0];
        AST *son1 = node->son[1];

        if(!check_dataType_compatibility(son0->dataType, son1->dataType) || son0->dataType == DATATYPE_BOOL || son1->dataType == DATATYPE_BOOL){
            fprintf(stderr, "Semantic ERROR: operators must be compatible!\n");
            SemanticErrors++;
        }

        node->dataType = DATATYPE_BOOL;       
    } else if(isLogicalOp(node->type)) {
        if(node->type == AST_TIL){
            if (node->son[0]->dataType != DATATYPE_BOOL)
            {
                fprintf(stderr, "Semantic ERROR: operator must be boolean!\n");
                SemanticErrors++;
            } 
        } else if(node->son[0]->dataType != DATATYPE_BOOL || node->son[1]->dataType != DATATYPE_BOOL) {
            fprintf(stderr, "Semantic ERROR: operatorS must be boolean!\n");
            SemanticErrors++;
        }

        node->dataType = DATATYPE_BOOL;
    }
    

}

int get_dataType(int type1, int type2){
    return (type1 > type2) ? type1 : type2;
}

void check_function(AST *node){
    AST *declaration = find_declaration(node->symbol->text, root);

    if(declaration == NULL){
        fprintf(stderr, "Semantic ERROR: cannot called something other than function!\n");
        SemanticErrors++;
    } else if(check_arguments_qty(node, declaration)) {
        check_arguments(node->son[0], declaration->son[1]);
    }
}

void check_arguments(AST* node, AST *declaration){
    if(node){
        if(node->son[0]){
            if(check_dataType_compatibility(node->son[0]->dataType, declaration->symbol->dataType)){
                fprintf(stderr, "Semantic ERROR: argument with incompatible type!\n");
                SemanticErrors++;
            }
            if(node->son[1])
                check_arguments(node->son[1], declaration->son[1]);
        }
    }
}

AST *find_declaration(char *name, AST *node){
    if(node->symbol != NULL && node->type == AST_DECF && strcmp(node->symbol->text, name) == 0) 
        return node;

    for(int i = 0; i<MAX_SONS; i++){
        if(node->son[i] == NULL)
            return NULL;
        AST *found = find_declaration(name, node->son[i]);
        if(found != NULL)
            return found;
    }

    return NULL;
}


int check_arguments_qty(AST *node, AST *declaration){
    int argumentsCalled = get_arguments_qty(node->son[0]);
    int argumentsDeclared = get_arguments_qty(declaration->son[1]);

    if(argumentsCalled != argumentsDeclared) {
        fprintf(stderr, "Semantic ERROR: number of arguments in call does not match in declaration!\n");
        SemanticErrors++;
        return 0;
    }

    return 1;
}

int get_arguments_qty(AST *node){
    if(!node)
        return 0;
    if(node->son[1])
        return 1 + get_arguments_qty(node->son[1]);
    else
        return 0;
}

void check_return(AST *node, int type, AST *body){
    AST *retorno;

    if(!body)
        return;

    retorno = body->son[0];

    if(retorno != NULL && retorno->type == AST_RETORNE){
        if(!check_dataType_compatibility(type, retorno->son[0]? retorno->son[0]->dataType:0)){
            fprintf(stderr, "Semantic ERROR: return type does not match function type!\n");
            SemanticErrors++;
        }
    }

    check_return(node, type, retorno->son[1]);
}
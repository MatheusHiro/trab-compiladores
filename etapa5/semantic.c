#include "semantic.h"
#include <stdlib.h>

int SemanticErrors = 0;

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
                    //fprintf(stderr,"Teste dataType %d --- type %d\n", node->symbol->dataType, node->son[1]->symbol->type);

                    if(node->son[1])
                        father_dataType = node->symbol->dataType;
                        if(!(check_compatibility(father_dataType, node->son[1]))){
                            fprintf(stderr,"Semantic ERROR: value atribuited %s does not match variable type\n", node->son[1]->symbol->text);
                            SemanticErrors++;
                        }//*/
                
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

    if (!node)
        return;

    
    
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

int is_int_or_char(int father_dataType, AST *node2){
    if((node2->symbol) && ((father_dataType == DATATYPE_INTE) || (father_dataType == DATATYPE_CARA)) && node2->symbol->type != SYMBOL_FLOAT)
        return 1;
    else 
        return 0;
}

int is_float(int father_dataType, AST *node2){
    if((node2->symbol) && (father_dataType == DATATYPE_FLOAT) && (node2->symbol->type == SYMBOL_FLOAT))
        return 1;
    else 
        return 0;
}

int check_compatibility(int father_dataType, AST *node2){
    if((is_int_or_char(father_dataType, node2)) || (is_float(father_dataType, node2)))
        return 1;
    else 
        return 0;
}

void verify_escalares(){

}
#include "veclist.h"

VEC_LIST *createList(char *ele){
    VEC_LIST *newNode = (VEC_LIST*) calloc(1,sizeof(VEC_LIST));
    newNode->ele = ele;
    newNode->next = 0;

    return newNode;
}

void *appendList(VEC_LIST *vele,char *ele){

    VEC_LIST *newNode = (VEC_LIST*) calloc(1,sizeof(VEC_LIST));

    newNode->ele = ele;
    newNode->next = 0;

    while(vele->next){
        vele = vele->next;
    }

    vele->next = newNode;
}
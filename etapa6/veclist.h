#ifndef VEC_LIST_H
#define VEC_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct veclist
{
    struct veclist *next;
    char *ele;
}VEC_LIST;

VEC_LIST *createList(char *ele);
void *appendList(VEC_LIST *vele, char *ele);

#endif
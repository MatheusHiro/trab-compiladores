#include "hash.h"
#include <string.h>
#include <stdlib.h>

HASH_NODE*Table[HASH_SIZE];

void hashInit(void)
{
	int i;
	for(i = 0; i < HASH_SIZE; i++)
	{
		Table[i] = 0;
	}
}

int hashAddress(char *text)
{
	int address = 1;
	int i;
	for (i = 0; i<strlen(text); i++)
	{
		address = (address * text[i]) % HASH_SIZE + 1;
	}
	return address - 1;
}

HASH_NODE *hashFind(char *text)
{
	HASH_NODE *node;
	int address = hashAddress(text);
	for(node=Table[address]; node; node = node->next)
		if (strcmp(node->text, text) == 0)
			return node;
	return 0;
}

HASH_NODE *hashInsert(char *text, int type)
{
	HASH_NODE *newNode;
	int address = hashAddress(text);

	if((newNode = hashFind(text)) != 0)
	{
		return newNode;
	}

	newNode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
	newNode->type = type;
	newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
	strcpy(newNode->text, text);
	newNode->next = Table[address];
	Table[address] = newNode;
	return newNode;

}

void hashPrint(void)
{
	int i;
	HASH_NODE *node;
	for(i = 0; i<HASH_SIZE; i++)
	{
		for(node = Table[i]; node; node = node->next)
			printf("Table[%d] has %s, type %d, dataType %d\n", i, node->text, node->type, node->dataType);
	}
}

int hashCheckUndeclared(void){

	int undeclared = 0;
	int i;
	HASH_NODE *node;
	for(i = 0; i<HASH_SIZE; i++)
	{
		for(node = Table[i]; node; node = node->next)
			if(node->type == SYMBOL_IDENTIFIER){
				fprintf(stderr,"Semantic ERROR: identifier %s undeclared\n", node->text);
				undeclared++;
			}
	}

	return undeclared;

}

HASH_NODE *makeTemp(void){
	static int serial = 0;
	char buffer[256] = "";

	sprintf(buffer,"_temp%d", serial++);
	return hashInsert(buffer, SYMBOL_VAR);
}

HASH_NODE *makeLabel(void){
	static int serial = 0;
	char buffer[256] = "";

	sprintf(buffer,"_label%d", serial++);
	return hashInsert(buffer, SYMBOL_LABEL);
}


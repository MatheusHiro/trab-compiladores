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
	newNode->isTemp = 0;
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

HASH_NODE *createName(HASH_NODE *name){
	static int serial = 0;
	char buffer[256] = "";

	if(name->newName){
		return name->newName;
	}

	sprintf(buffer,"string%d", serial++);

	HASH_NODE *new = hashInsert(buffer, SYMBOL_TEMP);
	name->newName = new;
	new->newName = new;

	return new;
}

void addData(HASH_NODE *node, char *data){
	node->data = data;
}

void printASM(FILE *fout){
	int i;
	HASH_NODE *node;

	fprintf(fout, "## DATA SECTION\n"
	"\t.section	__DATA,__data\n");

	for(i=0; i<HASH_SIZE; i++)
		for(node=Table[i]; node; node = node->next)
			switch(node->type){
				case SYMBOL_VAR: 
					if(node->dataType == DATATYPE_INTE)
						fprintf(fout, "_%s:\t.long\t%s\n", node->text?node->text:0, node->data?node->data:0);	
					if(node->isTemp)
						fprintf(fout, "_%s:\t.long\t0\n", node->text?node->text:0);	
					break;
				case SYMBOL_STRING:
					fprintf(fout, "_%s:\t.string\t%s\n", createName(node)->text?createName(node)->text:0, node->text?node->text:0);
					break;
				case SYMBOL_INT: 
						fprintf(fout, "_%s:\t.long\t%s\n", node->text?node->text:0, node->text?node->text:0);	
					break;
				case SYMBOL_VEC:
						fprintf(fout, "_%s:\n", node->text?node->text:0);	
						VEC_LIST *vele;
						for(vele = node->vele; vele; vele = vele->next){
							fprintf(fout, "\t.long\t%s\n",vele->ele);
						}
					break;
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

	HASH_NODE *temp;
	static int serial = 0;
	char buffer[256] = "";

	sprintf(buffer,"_temp%d", serial++);
	temp = hashInsert(buffer, SYMBOL_VAR);
	temp->isTemp = 1;
	return temp;
}

HASH_NODE *makeLabel(void){
	static int serial = 0;
	char buffer[256] = "";

	sprintf(buffer,"_label%d", serial++);
	return hashInsert(buffer, SYMBOL_LABEL);
}

void addVecEle(HASH_NODE *node, char *ele){
	if(node->vele == NULL){
		node->vele = createList(ele);
	} else {
		appendList(node->vele, ele);
	}
}

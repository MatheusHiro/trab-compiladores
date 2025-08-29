#include "tacs.h"
#include <stdlib.h>
#include <string.h>

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2){
    TAC *newTac = 0;
    newTac = (TAC*) calloc(1,sizeof(TAC));
    newTac->type = type;
    newTac->res = res;
    newTac->op1 = op1;
    newTac->op2 = op2;
    newTac->next = 0;
    newTac->prev = 0;

    return newTac;
}

TAC *makeBinOp(int type, TAC **code);
TAC *makeSe(TAC *code0, TAC *code1, TAC *code2);
TAC *makeEnquanto(TAC *code0, TAC *code1);
TAC *makeFun(TAC *code0, TAC *param, TAC *body);

void tacPrintSingle(TAC *tac){
    if(!tac) return;
    if(tac->type == TAC_SYMBOL) return;
    fprintf(stderr, "TAC(");
    switch(tac->type){
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
        case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
        case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
        case TAC_LST: fprintf(stderr, "TAC_LST"); break;
        case TAC_GRT: fprintf(stderr, "TAC_GRT"); break;
        case TAC_LE: fprintf(stderr, "TAC_LE"); break;
        case TAC_GE: fprintf(stderr, "TAC_GE"); break;
        case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
        case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
        case TAC_AND: fprintf(stderr, "TAC_AND"); break;
        case TAC_OR: fprintf(stderr, "TAC_OR"); break;
        case TAC_TIL: fprintf(stderr, "TAC_TIL"); break;
        case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
        case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
        case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
        case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
        case TAC_BEGINFUN: fprintf(stderr, "TAC_BEGINFUN"); break;
        case TAC_ENDFUN: fprintf(stderr, "TAC_ENDFUN"); break;
        case TAC_MOVE_VEC: fprintf(stderr, "TAC_MOVE_VEC"); break;
        case TAC_VEC: fprintf(stderr, "TAC_VEC"); break;
        case TAC_VECINDEX: fprintf(stderr, "TAC_VECINDEX"); break;
        case TAC_RET: fprintf(stderr, "TAC_RET"); break;
        case TAC_ENTRADA: fprintf(stderr, "TAC_ENTRADA"); break;
        case TAC_LELE: fprintf(stderr, "TAC_LELE"); break;
        case TAC_ARG: fprintf(stderr, "TAC_ARG"); break;
        case TAC_CALL: fprintf(stderr, "TAC_CALL"); break;
        case TAC_DECVAR: fprintf(stderr, "TAC_DECVAR"); break;
        case TAC_VELE: fprintf(stderr, "TAC_VELE"); break;
        case TAC_IFNZ: fprintf(stderr, "TAC_IFNZ"); break;
        default: fprintf(stderr, "TAC_UNKNOWN"); break;
    }
    fprintf(stderr, ",%s",(tac->res)?tac->res->text:"0");
    fprintf(stderr, ",%s",(tac->op1)?tac->op1->text:"0");
    fprintf(stderr, ",%s",(tac->op2)?tac->op2->text:"0");
    fprintf(stderr, ");\n");
}

void tacPrintBackwards(TAC *tac){
    if(!tac) return;
    else{
        tacPrintBackwards(tac->prev);
        tacPrintSingle(tac);
    }

}

TAC *tacJoin(TAC *l1, TAC *l2){

    TAC *tac;
    if(!l1) return l2;
    if(!l2) return l1;
    tac = l2;

    for(tac = l2; tac->prev; tac = tac->prev);
    tac->prev = l1;
    return l2;
}


TAC *generateCode(AST *node){
    if(!node) return NULL;

    int i;
    TAC *result = 0;
    TAC *code[MAX_SONS];
  
    for(i=0; i<MAX_SONS; i++)
        code[i] = generateCode(node->son[i]);

    switch (node->type)
    {
        case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol,0,0);
        break;
        case AST_ADD: result = makeBinOp(TAC_ADD, code); 
        break;
        case AST_SUB: result = makeBinOp(TAC_SUB, code); 
        break;
        case AST_MUL: result = makeBinOp(TAC_MUL, code); 
        break;
        case AST_DIV: result = makeBinOp(TAC_DIV, code); 
        break;        
        case AST_LST: result = makeBinOp(TAC_LST, code); 
        break;
        case AST_GRT: result = makeBinOp(TAC_GRT, code); 
        break;
        case AST_LE: result = makeBinOp(TAC_LE, code); 
        break;
        case AST_GE: result = makeBinOp(TAC_GE, code); 
        break;
        case AST_EQ: result = makeBinOp(TAC_EQ, code); 
        break;
        case AST_DIF: result = makeBinOp(TAC_DIF, code); 
        break;
        case AST_AND: result = makeBinOp(TAC_AND, code); 
        break;
        case AST_OR: result = makeBinOp(TAC_OR, code); 
        break;
        case AST_TIL: result = makeBinOp(TAC_TIL, code); 
        break;
        case AST_ASS: result = tacJoin(code[0],tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0)); 
        break;

        case AST_ASS_VEC: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_MOVE_VEC, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0)));
        break;

        case AST_DECVAR: result = tacJoin(code[0],tacCreate(TAC_DECVAR, node->symbol, code[1]?code[1]->res:0, 0));

        break;
        case AST_SE: result = makeSe(code[1], code[0], NULL); 
        break;
        case AST_SENAUM: result = makeSe(code[2], code[1], code[0]); 
        break;   
        case AST_ENQUANTO: result = makeEnquanto(code[1], code[0]);    
        break;
        case AST_DECF: result = makeFun(tacCreate(TAC_SYMBOL, node->symbol,0,0), code[1], code[2]);
        break;
        case AST_DECVEC: result = tacJoin(tacCreate(TAC_VEC, node->symbol, code[1]?code[1]->res:0, 0),tacJoin(code[1],code[2]));
        break;
        case AST_RETORNE: result = tacJoin(code[0],tacCreate(TAC_RET, code[0]?code[0]->res:0, 0,0));
        break;
        case AST_LELE: result = tacJoin(code[0],tacJoin(tacCreate(TAC_LELE, code[0]?code[0]->res:0, 0,0), code[1]));
        break;
        case AST_VEC: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_VECINDEX, node->symbol,code[0]?code[0]->res:0, code[1]?code[1]->res:0)));
        break;
        case AST_ENTRADA: result = tacCreate(TAC_ENTRADA, makeTemp(), 0,0);
        break;
        case AST_LARG: result = tacJoin(code[1], tacJoin(code[0],tacCreate(TAC_ARG, code[0]?code[0]->res:0,0,0)));
        break;
        case AST_FUN: result = tacJoin(code[1],tacJoin(code[0],tacCreate(TAC_CALL,makeTemp(),node->symbol,0)));
        break;
        case AST_VELE: result = tacJoin(tacCreate(TAC_VELE,code[0]?code[0]->res:0,0,0), code[1]);
        break;
        default: result = tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
        break;
    }

    return result;
    
}

TAC *makeBinOp(int type, TAC **code){
    return tacJoin(tacJoin(code[0],code[1]), tacCreate(type, makeTemp(),code[0]?code[0]->res:0,code[1]?code[1]->res:0));
}

TAC *makeSe(TAC *code0, TAC *code1, TAC *code2){
    TAC *jumpTac = 0;
    TAC *labelTac = 0;
    HASH_NODE *newLabel = 0;

    newLabel = makeLabel();
    jumpTac = tacCreate(TAC_IFZ, newLabel,code0?code0->res:0,0);
    jumpTac->prev = code0;
    labelTac = tacCreate(TAC_LABEL, newLabel, 0,0);

    if(code2){
        HASH_NODE *elseLabel = makeLabel();
        TAC *elseJumpTac = tacCreate(TAC_JUMP, elseLabel,0,0);

        jumpTac = tacCreate(TAC_IFNZ, newLabel,code0?code0->res:0,0);
        TAC *elseLabelTac = tacCreate(TAC_LABEL, elseLabel,0,0);
        return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code0, jumpTac), code1), elseJumpTac), labelTac), code2),elseLabelTac);
    }else
        labelTac->prev = code1;
        return tacJoin(jumpTac, labelTac);

}

TAC *makeEnquanto(TAC *code0, TAC *code1){
    TAC *jumpTac = 0;
    TAC *jumpLabelTac = 0;
    TAC *loopLabelTac = 0;
    TAC *loopTac = 0;

    HASH_NODE *newLabel = 0;
    HASH_NODE *loopLabel = 0;

    newLabel = makeLabel();
    loopLabel = makeLabel();

    loopTac = tacCreate(TAC_IFZ, newLabel,code0?code0->res:0,0);
    jumpLabelTac = tacCreate(TAC_LABEL, newLabel, 0,0);
    jumpTac = tacCreate(TAC_JUMP, loopLabel,0,0);
    loopLabelTac = tacCreate(TAC_LABEL, loopLabel, 0,0);
    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(loopLabelTac,code0), loopTac),code1),jumpTac),jumpLabelTac);

}

TAC *makeFun(TAC *code0, TAC* param, TAC *body){
    return tacJoin(tacJoin(tacJoin(tacCreate(TAC_BEGINFUN, code0->res,0,0),param),body),tacCreate(TAC_ENDFUN,code0->res,0,0));
}

TAC *tacReverse(TAC *tac){
    TAC *t = tac;
    for (t = tac; t->prev; t = t->prev)
        t->prev->next = t;
    return t;
}

void generateAsm(TAC *first, AST *node){
    FILE *fout;
    fout = fopen("out.s", "w");
    TAC *tac;

    fprintf(fout, "## FIXED INIT\n"
    "\t.section	__TEXT,__cstring,cstring_literals\n"
"printintstr: .asciz	\"%%d\"\n"
"printstringstr: .asciz \"%%s\"\n"
"scanfintstr: .asciz \"%%d\"\n"
"\n"
    "\t.section	__TEXT,__text,regular,pure_instructions\n\n");

    for(tac = first; tac; tac = tac->next)
        switch (tac->type)
        {
            case TAC_BEGINFUN:
                fprintf(fout, "## TAC_BEGINFUN\n"
                "\t.globl	_%s\n"
    "_%s: \n"                                                           
        "\tpushq	%%rbp\n"
        "\tmovq	%%rsp, %%rbp\n\n", tac->res?tac->res->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_ENDFUN: 
                fprintf(fout, "## TAC_ENDFUN\n"
	"\tpopq	%%rbp\n"
	"\tretq\n\n");
                break;
            case TAC_LELE: fprintf(fout, "## TAC_LELE");
                if(tac->res->type == SYMBOL_STRING) {
                    fprintf(fout, "\t(string)\n"
                    "\tleaq	printstringstr(%%rip), %%rdi\n"
	"\tleaq	_%s(%%rip), %%rsi\n"
	"\tmovb	$0, %%al\n"
	"\tcallq	_printf\n\n", tac->res?createName(tac->res)->text:0);
                }else {
                    fprintf(fout, "\t(int)\n" 
	"\tleaq	printintstr(%%rip), %%rdi\n"
	"\tmovl	_%s(%%rip), %%esi\n"
	"\tmovb	$0, %%al\n"
	"\tcallq	_printf\n\n", tac->res?tac->res->text:0);}
                break;

            case TAC_ADD: fprintf(fout,"## TAC_ADD\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\taddl	_%s(%%rip), %%eax\n"
	"\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_ENTRADA: fprintf(fout, "## TAC_ENTRADA\n"
	"\tleaq	scanfintstr(%%rip), %%rdi\n"
	"\tmovq	_%s@GOTPCREL(%%rip), %%rsi\n"
	"\tmovb	$0, %%al\n"
	"\tcallq	_scanf\n\n", tac->res?tac->res->text:0);
                break;

            case TAC_MOVE: fprintf(fout, "## TAC_MOVE\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_MOVE_VEC: fprintf(fout, "## TAC_MOVE_VEC\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tmovl	%%eax, _%s(%%rip)\n\n", tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_VECINDEX: fprintf(fout, "## TAC_VECINDEX\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_MUL: fprintf(fout, "## TAC_MUL\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\timull	_%s(%%rip), %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_SUB: fprintf(fout, "## TAC_SUB\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tsubl	_%s(%%rip), %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_DIV: fprintf(fout, "## TAC_DIV\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tcltd\n"
	"\tidivl	_%s(%%rip)\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;
    
            case TAC_LST: fprintf(fout, "## TAC_LST\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tcmpl	_%s(%%rip), %%eax\n"
	"\tsetl	%%al\n"
	"\tmovzbl	%%al, %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;            

            case TAC_GRT: fprintf(fout, "## TAC_GRT\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tcmpl	_%s(%%rip), %%eax\n"
	"\tsetg	%%al\n"
	"\tmovzbl	%%al, %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;            

            case TAC_LE: fprintf(fout, "## TAC_LE\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tcmpl	_%s(%%rip), %%eax\n"
	"\tsetle	%%al\n"
	"\tmovzbl	%%al, %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;            

            case TAC_GE: fprintf(fout, "## TAC_GE\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tcmpl	_%s(%%rip), %%eax\n"
	"\tsetge	%%al\n"
	"\tmovzbl	%%al, %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_EQ: fprintf(fout, "## TAC_EQ\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tcmpl	_%s(%%rip), %%eax\n"
	"\tsete	%%al\n"
	"\tmovzbl	%%al, %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_DIF: fprintf(fout, "## TAC_DIF\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tcmpl	_%s(%%rip), %%eax\n"
	"\tsetne	%%al\n"
	"\tmovzbl	%%al, %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_AND: fprintf(fout, "## TAC_AND\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\tandl	_%s(%%rip), %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_OR: fprintf(fout, "## TAC_OR\n"
	"\tmovl	_%s(%%rip), %%eax\n"
	"\torl	_%s(%%rip), %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->op2?tac->op2->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_TIL: fprintf(fout, "## TAC_NOT\n"
	"\tcmpl	$0, _%s(%%rip)\n"
	"\tsete	%%al\n"
	"\tmovzbl	%%al, %%eax\n"
    "\tmovl	%%eax, _%s(%%rip)\n\n", tac->op1?tac->op1->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_IFZ: fprintf(fout, "## TAC_IFZ\n"
    "\tmovl	_%s(%%rip), %%eax\n"
	"\tandl	$1, %%eax\n"
	"\tjz	_%s\n\n", tac->op1?tac->op1->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_IFNZ: fprintf(fout, "## TAC_IFNZ\n"
    "\tmovl	_%s(%%rip), %%eax\n"
	"\tandl	$1, %%eax\n"
	"\tjnz	_%s\n\n", tac->op1?tac->op1->text:0, tac->res?tac->res->text:0);
                break;

            case TAC_JUMP: fprintf(fout, "## TAC_JUMP\n"
    "\tjmp	_%s\n\n", tac->res?tac->res->text:0);
                break;

            case TAC_LABEL: fprintf(fout, "## TAC_LABEL\n"
    "\t _%s:\n\n", tac->res?tac->res->text:0);
                break;

            case TAC_CALL: fprintf(fout, "## TAC_CALL\n");
            if(strcmp(tac->res?tac->res->text:0, "main") == 0){
                fprintf(fout, "\tcallq %s\n", tac->op1?tac->op1->text:0);
            }else {
                fprintf(fout, "\tcallq _%s\n", tac->op1?tac->op1->text:0);
            }
            fprintf(fout,"\tmovl	%%eax, _%s(%%rip)\n\n", tac->res?tac->res->text:0);
                break;

            case TAC_ARG: fprintf(fout, "## TAC_ARG\n"
    "\tmovl %%eax, _%s(%%rip)\n\n",tac->res?tac->res->text:0);
                break;

            case TAC_RET: fprintf(fout, "## TAC_RET\n"
    "\tmovl	_%s(%%rip), %%eax\n"
	"\tpopq	%%rbp\n"
	"\tretq\n\n", tac->res?tac->res->text:0);
                break;
            default:
                break;
        }
    

    printASM(fout);
    fclose(fout);
}

%{
	#include "hash.h"
	#include "ast.h"
	#include "semantic.h"
	#include <stdlib.h>
	#include "tacs.h"
    int yyerror(const char* s);
    int getLineNumber();
    int yylex();
    AST *ASTroot = NULL;
	int syntax_error = 0;
%}

%union
{
	HASH_NODE *symbol;
	AST *ast;
}

%token<symbol> KW_CARA           
%token<symbol> KW_INTE           
%token<symbol> KW_REAL           

%token KW_SE             
%token KW_ENTAUM         
%token KW_SENAUM         
%token KW_ENQUANTO       
%token KW_ENTRADA        
%token KW_ESCREVA        
%token KW_RETORNE        

%token OPERATOR_LE       
%token OPERATOR_GE       
%token OPERATOR_EQ       
%token OPERATOR_DIF      

%token <symbol> TK_IDENTIFIER     

%token <symbol> LIT_INTEIRO       
%token <symbol> LIT_FLOAT         
%token <symbol> LIT_CHAR          
%token <symbol> LIT_STRING  

%token TOKEN_ERROR	

%type <ast> programa
%type <ast> dec
%type <ast> decl
%type <ast> dec_var
%type <ast> dec_vec
%type <ast> dec_func
%type <ast> vec_ele
%type <ast> lit
%type <ast> body
%type <ast> param
%type <ast> lcmd
%type <ast> cmd
%type <ast> expr
%type <ast> lele
%type <ast> arg
%type <ast> type


%left '&' '|'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'
%left '~'



%%

programa: decl {$$=$1; ASTroot=$$; if(syntax_error) exit(3); TAC *code; astPrint($$,0); check_and_set_declarations($1); check_undeclared(); code = generateCode($1); tacPrintBackwards(code); code = tacReverse(code); addDataVarHash($1);generateAsm(code, $1);}
	;


decl: dec decl {$$=astCreate(AST_DECL,0,$1,$2,0,0);}
	| 		   {$$=0;}
	;


dec: dec_var {$$=$1;}
	| dec_func {$$=$1;}
	;


dec_var: type TK_IDENTIFIER '=' lit ';'  {$$=astCreate(AST_DECVAR, $2, $1,$4,0,0);}
	| type TK_IDENTIFIER '=' lit error  {$$=0; fprintf(stderr, "Expecting ;\n");}
	| dec_vec {$$=$1;}
	;


dec_vec: type TK_IDENTIFIER '[' LIT_INTEIRO ']' vec_ele ';' {$$=astCreate(AST_DECVEC, $2, $1,astCreate(AST_SYMBOL, $4 ,0,0,0,0),$6,0);}
	| type TK_IDENTIFIER '[' LIT_INTEIRO ']' vec_ele error {$$=0; fprintf(stderr, "Expecting ;\n");}
	;

vec_ele:  lit vec_ele {$$=astCreate(AST_VELE, 0, $1,$2,0,0);}
	| {$$=0;}
    ;

lit: LIT_INTEIRO {$$=astCreate(AST_SYMBOL, $1, 0,0,0,0);}
	| LIT_FLOAT {$$=astCreate(AST_SYMBOL, $1, 0,0,0,0);}
	| LIT_CHAR {$$=astCreate(AST_SYMBOL, $1, 0,0,0,0);}
	;

dec_func: type TK_IDENTIFIER '(' param ')' body {$$=astCreate(AST_DECF, $2, $1,$4,$6,0);}
	;



body: '{' lcmd '}' {$$=astCreate(AST_BODY, 0, $2,0,0,0);}
	| '{' lcmd error {$$=0; fprintf(stderr, "Missing }\n");}
	;

param: type TK_IDENTIFIER param {$$=astCreate(AST_PARAM, $2, $1,$3,0,0);}
	| {$$ = 0;}
	;

lcmd: cmd ';' lcmd {$$=astCreate(AST_LCMD, 0, $1,$3,0,0);}
	| cmd {$$=$1;}
	;

cmd: TK_IDENTIFIER '=' expr {$$=astCreate(AST_ASS, $1, $3,0,0,0);}
	| TK_IDENTIFIER '[' expr ']' '=' expr {$$=astCreate(AST_ASS_VEC, $1, $3,$6,0,0);}
	| KW_ESCREVA lele {$$=astCreate(AST_ESCREVA, 0, $2,0,0,0);}
	| KW_RETORNE expr {$$=astCreate(AST_RETORNE, 0, $2,0,0,0);}
	| KW_ENTAUM cmd KW_SE '(' expr ')' {$$=astCreate(AST_SE, 0, $2,$5,0,0);}
	| KW_ENTAUM cmd KW_SE '(' error ')' {$$=0; fprintf(stderr, "Wrong if condition\n");}
	| KW_ENTAUM cmd KW_SENAUM cmd KW_SE '(' expr ')' {$$=astCreate(AST_SENAUM, 0, $2,$4,$7,0);}
	| cmd KW_ENQUANTO '(' expr ')' {$$=astCreate(AST_ENQUANTO, 0, $1,$4,0,0);}
	| cmd KW_ENQUANTO '(' error ')' {$$=0; fprintf(stderr, "Wrong while condition\n");}
	| body {$$=$1;}
	| {$$=0;}
	;

expr: TK_IDENTIFIER {$$=astCreate(AST_SYMBOL, $1,0,0,0,0);}
	| lit 			{$$=$1;}
	| expr '+' expr {$$=astCreate(AST_ADD, 0,$1,$3,0,0);}
	| expr '-' expr {$$=astCreate(AST_SUB, 0,$1,$3,0,0);}
	| expr '*' expr {$$=astCreate(AST_MUL, 0,$1,$3,0,0);}
	| expr '/' expr {$$=astCreate(AST_DIV, 0,$1,$3,0,0);} 
	| expr '<' expr {$$=astCreate(AST_LST, 0,$1,$3,0,0);}
	| expr '>' expr {$$=astCreate(AST_GRT, 0,$1,$3,0,0);}
	| expr OPERATOR_LE expr {$$=astCreate(AST_LE, 0,$1,$3,0,0);}
	| expr OPERATOR_GE expr {$$=astCreate(AST_GE, 0,$1,$3,0,0);}
	| expr OPERATOR_EQ expr {$$=astCreate(AST_EQ, 0,$1,$3,0,0);}
	| expr OPERATOR_DIF expr {$$=astCreate(AST_DIF, 0,$1,$3,0,0);}
	| expr '&' expr {$$=astCreate(AST_AND, 0,$1,$3,0,0);}
	| expr '|' expr {$$=astCreate(AST_OR, 0,$1,$3,0,0);}
	| '~' expr {$$=astCreate(AST_TIL, 0,$2,0,0,0);}
	| TK_IDENTIFIER '(' arg ')'  {$$=astCreate(AST_FUN, $1,$3,0,0,0);}
	| TK_IDENTIFIER '(' arg error  {$$=0; fprintf(stderr, "Missing )\n");}
	| '(' expr ')' {$$=$2;}
	| TK_IDENTIFIER '[' expr ']' {$$=astCreate(AST_VEC, $1,$3,0,0,0);}
	| TK_IDENTIFIER '[' expr error {$$=0; fprintf(stderr, "Missing ]\n");}
	| KW_ENTRADA {$$=astCreate(AST_ENTRADA, 0,0,0,0,0);}
	;



lele: LIT_STRING lele {$$=astCreate(AST_LELE, 0, $$=astCreate(AST_SYMBOL, $1, 0,0,0,0),$2,0,0);}
	| expr lele {$$=astCreate(AST_LELE, 0, $1, $2, 0, 0);}
	| {$$=0;}
	;


arg: expr arg {$$=astCreate(AST_LARG, 0, $1,$2,0,0);}
	| {$$=0;}
	;

type: KW_INTE {$$=astCreate(AST_INTE, 0, 0,0,0,0);}
	| KW_REAL {$$=astCreate(AST_REAL, 0, 0,0,0,0);}
	| KW_CARA {$$=astCreate(AST_CARA, 0, 0,0,0,0);}
	;


%%

int yyerror(const char* s)
{
	fprintf(stderr, "Syntax error at line %d!\n", getLineNumber());
	syntax_error = 1;
	return 0;
}

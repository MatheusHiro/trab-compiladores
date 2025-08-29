%{
	#include "hash.h"
    int yyerror(const char* s);
    int getLineNumber();
%}

%token KW_CARA           
%token KW_INTE           
%token KW_REAL           

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

%left '&' '|'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'
%left '~'



%%

programa: decl
	;

decl: dec decl
	|
	;


dec: dec_var
	| dec_func
	;


dec_var: type TK_IDENTIFIER '=' lit ';'
	| dec_vec
	;


dec_vec: type TK_IDENTIFIER '[' LIT_INTEIRO ']' ';'
    | type TK_IDENTIFIER '[' LIT_INTEIRO ']' vec_ele ';'
	;

vec_ele: lit 
    | lit vec_ele
    ;

lit: LIT_INTEIRO 
	| LIT_FLOAT 
	| LIT_CHAR 
	;

dec_func: type func body
	;


body: '{' lcmd '}'
	;

param: type TK_IDENTIFIER param
	|
	;

lcmd: cmd ';' lcmd
	| cmd
	;

cmd: TK_IDENTIFIER '=' expr
	| TK_IDENTIFIER '[' expr ']' '=' expr 
	| KW_ESCREVA lele
	| KW_RETORNE expr
	| KW_ENTAUM cmd KW_SE '(' expr ')'
	| KW_ENTAUM cmd KW_SENAUM cmd KW_SE '(' expr ')'
	| cmd KW_ENQUANTO '(' expr ')'
	| body
	| 
	;

expr: TK_IDENTIFIER
	| lit
	| expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| expr '<' expr
	| expr '>' expr
	| expr OPERATOR_LE expr
	| expr OPERATOR_GE expr
	| expr OPERATOR_EQ expr
	| expr OPERATOR_DIF expr
	| expr '&' expr
	| expr '|' expr
	| expr '~' expr
	| fun
	| '(' expr ')' 
	| TK_IDENTIFIER '[' expr ']'
	| KW_ENTRADA
	;

ele: LIT_STRING
	| expr
	;

lele: ele lele
	| ele
	;

func: TK_IDENTIFIER '(' param ')'
	;

fun: TK_IDENTIFIER '(' arg ')'
	;

arg: expr arg
	| expr
	;

type: KW_INTE
	| KW_REAL
	| KW_CARA
	;


%%

int yyerror(const char* s)
{
	fprintf(stderr, "Syntax error at line %d!\n", getLineNumber());
	exit(3);
}

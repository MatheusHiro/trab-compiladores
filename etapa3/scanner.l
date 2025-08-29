%{
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
int running = 1;
int isRunning(void);
int getLineNumber(void);
void initMe(void);
int lineNumber = 0;
#define  FALSE 0

%}

%x COMMENT


%%
cara		{ return(KW_CARA); }
inte 		{ return(KW_INTE); }
real 		{ return(KW_REAL); } 
se   		{ return(KW_SE); }
entaum  	{ return(KW_ENTAUM); }
senaum  	{ return(KW_SENAUM); }
enquanto 	{ return(KW_ENQUANTO); }
entrada   	{ return(KW_ENTRADA); }
escreva     { return(KW_ESCREVA); }
retorne     { return(KW_RETORNE); }
[0-9]+ {yylval.symbol = hashInsert(yytext, LIT_INTEIRO); return(LIT_INTEIRO); }
([0-9]+([.][0-9])) {yylval.symbol = hashInsert(yytext, LIT_FLOAT); return(LIT_FLOAT); }
'.' {yylval.symbol = hashInsert(yytext, LIT_CHAR); return(LIT_CHAR); }
\"(\\.|[^\\"])*\" {yylval.symbol = hashInsert(yytext, LIT_STRING); return(LIT_STRING); }
[a-z._][0-9a-z._]* {yylval.symbol = hashInsert(yytext, TK_IDENTIFIER); return(TK_IDENTIFIER); }
[-;(){}=+/<>&[~&] { return(yytext[0]); }
"]" { return(yytext[0]); }
"|" { return(yytext[0]); }
"*" { return(yytext[0]); }
"\n" { lineNumber++; }
[ \t\n,] 
(<=) { return(OPERATOR_LE); }
(>=) { return(OPERATOR_GE); }
(==) { return(OPERATOR_EQ); }
(!=) { return(OPERATOR_DIF); }
"///" { BEGIN(COMMENT); }
"//".* 
. { return(TOKEN_ERROR); }

<COMMENT>"\\\\\\" { BEGIN(INITIAL); }
<COMMENT>"\n" { lineNumber++; }
<COMMENT>. { }


%%






void initMe(void)
{
	hashInit();
}

int isRunning(void)
{
	return running;
}

int getLineNumber(void)
{
	return lineNumber;
}

int yywrap()
{
	running = FALSE;
	return 1;
}

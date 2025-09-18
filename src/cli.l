%option nounput
%option noinput
%option noyywrap

%{
#include "cli.tab.h"
#include <stdlib.h>
#include <string.h>

extern char *yytext;
int yylex(void);
void yyerror(const char *s);
%}

%%

"create"      { return CREATE; }
"project"     { return PROJECT; }
"file"        { return FILE_KW; }
"delete"      { return DELETE; }
"recover"     { return RECOVER; }
"empty"       { return EMPTY; }
"trash"       { return TRASH; }
"clear"       { return CLEAR; }
"args"        { return ARGS; }

[a-zA-Z_][a-zA-Z0-9_.]*  { yylval.string = strdup(yytext); return IDENTIFIER; }

[ \t\r]+      { /* skip whitespace */ }

\n            { return NEWLINE; }

.             { return yytext[0]; }

%%
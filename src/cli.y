%{
#include <stdio.h>
#include <stdlib.h>
#include "cli.tab.h"
#include "commands/commands.h"

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char *string;
}

%token CREATE PROJECT FILE_KW DELETE RECOVER EMPTY TRASH CLEAR ARGS
%token <string> IDENTIFIER
%token NEWLINE

%type <string> type

%%

commands:
      command NEWLINE { printf("> "); fflush(stdout); }
    | commands command NEWLINE { printf("> "); fflush(stdout); }
;

command:
    create_file_cmd
  | delete_file_cmd
  | recover_file_cmd
  | empty_trash_cmd
  | clear_cmd
;

type:
    IDENTIFIER { $$ = $1; } 
;

create_file_cmd:
     CREATE FILE_KW IDENTIFIER type { create_file($3, $4, false); }
   | CREATE FILE_KW IDENTIFIER type ARGS { create_file($3, $4, true); }
;

delete_file_cmd:
    DELETE IDENTIFIER { delete_file($2); }
;

recover_file_cmd:
    RECOVER IDENTIFIER { recover_file($2); }
;

empty_trash_cmd:
    EMPTY TRASH { empty_trash(); }
;

clear_cmd:
    CLEAR { clear(); }

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    fflush(stderr);
    printf("> ");
    fflush(stdout);
}
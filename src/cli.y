%{
#include <stdio.h>
#include <stdlib.h>
#include "cli.tab.h"
#include "commands/commands.h"
#include "commands/template/template.h"

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char *string;
}

%token CREATE LIST FILE_KW DELETE RECOVER EMPTY TRASH CLEAR NEW TEMPLATES CTMPL
%token <string> IDENTIFIER
%token NEWLINE

%type <string> type

%%

commands:
      command NEWLINE { fflush(stdout); }
    | commands command NEWLINE { fflush(stdout); }
;

command:
    create_file_cmd
  | delete_file_cmd
  | recover_file_cmd
  | empty_trash_cmd
  | clear_cmd
  | create_template_cmd
  | create_file_from_template_cmd
  | list_templates_cmd
;

type:
    IDENTIFIER { $$ = $1; } 
;


create_file_cmd:
    CREATE FILE_KW IDENTIFIER type { create_file($3, $4, false); }
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
;

create_template_cmd:
    CTMPL IDENTIFIER IDENTIFIER { create_template($2, $3); }
;

create_file_from_template_cmd:
    CREATE NEW FILE_KW IDENTIFIER IDENTIFIER
    {
        // $3 = new file name
        // $4 = template name
        create_file_from_template($4, $5);
    }
;

list_templates_cmd: 
    LIST TEMPLATES { list_templates(); }
;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    fflush(stderr);
    fflush(stdout);
}
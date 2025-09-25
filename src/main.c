#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

int yyparse(void);
extern int yylex(void);
extern FILE* yyin;
extern void yyrestart(FILE* input_file);

int main(void) {
  char* input;

  while ((input = readline("> ")) != NULL) {
    if (*input) add_history(input);

    if (strlen(input) == 0) {
      free(input);
      continue;
    }

    size_t len = strlen(input);
    char* buffer = malloc(len + 2);
    strcpy(buffer, input);
    buffer[len] = '\n';
    buffer[len + 1] = '\0';

    yyin = fmemopen(buffer, len + 1, "r");
    yyrestart(yyin);  // reset lexer
    yyparse();
    fclose(yyin);

    free(buffer);
    free(input);
  }

  return 0;
}
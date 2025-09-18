#include <stdio.h>

int yyparse(void);

int main(void) {
    while (1) {
        printf("> ");
        fflush(stdout);  
        yyparse();
    }
    return 0;
}
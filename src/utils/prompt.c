#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/utils/prompt.h"

#define BLUE  "\x1b[34m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void display_prompt() {
    char *cwd = getcwd(NULL, 0); 
    if (cwd != NULL) {
        char *pos = strstr(cwd, "cli/");
        if (pos != NULL) {
            pos += strlen("cli/");
            printf(BLUE "%.*s" RESET, (int)(pos - cwd), cwd);
            printf(GREEN "%s" RESET, pos);
        } else {
            
            printf(BLUE "%s" RESET, cwd);
        }
        printf("> ");
        free(cwd);
    } else {
        perror("getcwd");
        printf("> ");
    }
    fflush(stdout);
}
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/utils/prompt.h"

#define BLUE  "\x1b[34m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void display_prompt() {
    char *cwd = getcwd(NULL, 0); // allocates the needed size
    if (cwd != NULL) {
        // Look for "cli/" in cwd
        char *pos = strstr(cwd, "cli/");
        if (pos != NULL) {
            pos += strlen("cli/"); // move past "cli/"

            // Print everything up through "cli/" in blue
            printf(BLUE "%.*s" RESET, (int)(pos - cwd), cwd);

            // Print everything after "cli/" in green
            printf(GREEN "%s" RESET, pos);
        } else {
            // If "cli/" not found, print whole cwd in blue
            printf(BLUE "%s" RESET, cwd);
        }
        printf("> ");
        free(cwd); // free the allocated memory
    } else {
        perror("getcwd");
        printf("> ");
    }
    fflush(stdout);
}
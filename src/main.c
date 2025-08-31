#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/structs.h"
#include "../include/commands.h"

#define MAX_INPUT 256

Command commands[] = {
    {"hello", hello_world, "Hello World"},
    {"mkdir", cmd_mkdir, "Create new folder"},
    {NULL, NULL, NULL},
};

int main(void)
{
    char input[MAX_INPUT];

    while (1)
    {
        printf("> ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0; // remove trailing newline

        int valid = 0;

        for (int i = 0; commands[i].name != NULL; i++)
        {
            int len = strlen(commands[i].name);

            if (strncmp(input, commands[i].name, len) == 0)
            {
                char *args = input + len;
                while (*args == ' ')
                    args++;

                commands[i].func(args);
                valid = 1;
                break;
            }
        }

        if (!valid && strlen(input) > 0)
        {
            printf("Unknown command: %s\n", input);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "../include/commands.h"

void hello_world()
{
    printf("Hello world!\n");
}

void cmd_mkdir(char *args)
{
    if (!args || args[0] == '\0')
    {
        printf("Usage: mkdir <folder>\n");
        return;
    }
    if (mkdir(args, 0755) == 0)
    {
        printf("Directory '%s' created.\n", args);
    }
    else
    {
        printf("Error creating '%s' : '%s\n", args, strerror(errno));
    }
}

void cmd_rmdir(char *args)
{
    if (!args || args[0] == '\0')
    {
        printf("Usage: rmdir <folder>\n");
        return;
    }
    if (rmdir(args) == 0)
    {
        printf("Folder '%s' deleted successfully.\n", args);
    }
    else
    {
        printf("Error deleting folder '%s': %s\n", args, strerror(errno));
    }
}
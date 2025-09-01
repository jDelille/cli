/**
 * Docs for commands: man7.org
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/commands.h"


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

void cmd_touch(char *args)
{
    if (!args || args[0] == '\0')
    {
        printf("Usage: touch <filename>\n");
        return;
    }

    int fd = open(args, O_CREAT | O_WRONLY, 0644);

    if (fd >= 0)
    {
        printf("File '%s' created successfully.\n", args);
        close(fd);
    }
    else
    {
        printf("Error creating file '%s': %s\n", args, strerror(errno));
    }
}

void cmd_cd(char *args)
{
    if (!args || args[0] == '\0')
    {
        printf("Usage: cd <directory>\n");
        return;
    }

    if (chdir(args) == 0)
    {
        printf("Changed directory to '%s'\n", args);
    }
    else
    {
        printf("Error changing directory to '%s': %s\n", args, strerror(errno));
    }
}
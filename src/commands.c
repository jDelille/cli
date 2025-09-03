/**
 * Docs for COMMANDS: https://man7.org/linux/man-pages/index.html
 * Docs for ANSI: https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html?utm_source=chatgpt.com#colors
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include "../include/commands.h"

#define BLUE "\x1b[34m"
#define FILE_COLOR "\x1b[38;5;40m"
#define DIR_COLOR "\x1b[4;37m"
#define RESET "\x1b[0m"

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

    chdir(args);
}

void cmd_clear(char *args)
{
    (void)args;
    printf("\033[2J\033[H");
    fflush(stdout);
}

void cmd_exit(char *args)
{
    (void)args;
    printf("Exiting...\n");
    exit(EXIT_SUCCESS);
}

void cmd_rm(char *args)
{
    if (!args || args[0] == '\0')
    {
        printf("Usage: rm <filename>\n");
        return;
    }

    if (unlink(args) == 0)
    {
        printf("File '%s' deleted successfully.\n", args);
    }
    else
    {
        printf("Error deleting file '%s': %s\n", args, strerror(errno));
    }
}

void cmd_ls(char *args)
{
    char *dir = (args && args[0]) ? args : ".";
    DIR *d = opendir(dir);
    if (!d)
    {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    struct stat st;
    char path[4096];

    while ((entry = readdir(d)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        if (stat(path, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode))
        {
            printf("%s%s%s  ", DIR_COLOR, entry->d_name, RESET);
        }
        else
        {
            printf("%s%s%s  ", FILE_COLOR, entry->d_name, RESET);
        }
    }
    closedir(d);
    printf("\n");
}
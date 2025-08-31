#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/commands.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

int folder_exists(const char *name)
{
    struct stat st;
    return stat(name, &st) == 0 && S_ISDIR(st.st_mode);
}

void test_mkdir()
{
    const char *test_folder = "test_folder";

    if (folder_exists(test_folder))
        rmdir(test_folder);

    if (fork() == 0)
    {
        cmd_mkdir((char *)test_folder);
        if (folder_exists(test_folder))
        {
            printf("\n");
            printf(GREEN "test_mkdir passed!\n" RESET);
            printf("\n");
        }
        else
        {
            printf("\n");
            printf(RED "test_mkdir failed!\n" RESET);
            printf("\n");
        }
        rmdir(test_folder);
        return;
    }
}

int main(void)
{
    test_mkdir();
    return 0;
}
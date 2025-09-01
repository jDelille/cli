#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "../include/commands.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

int folder_exists(const char *name)
{
    struct stat st;
    return stat(name, &st) == 0 && S_ISDIR(st.st_mode);
}

void suppress_stdout_start(FILE **orig)
{
    *orig = stdout;
    stdout = fopen("/dev/null", "w");
}

void suppress_stdout_end(FILE *orig)
{
    fclose(stdout);
    stdout = orig;
}

void test_mkdir()
{
    const char *folder = "test_folder";

    if (folder_exists(folder))
        rmdir(folder);

    FILE *orig;
    suppress_stdout_start(&orig);
    cmd_mkdir((char *)folder);
    suppress_stdout_end(orig);

    if (folder_exists(folder))
    {
        printf(GREEN "test_mkdir passed!\n" RESET);
    }
    else
    {
        printf(RED "test_mkdir failed!\n" RESET);
    }

    rmdir(folder);
}

void test_rmdir()
{
    const char *folder = "test_rmdir";

    if (folder_exists(folder))
        rmdir(folder);

    mkdir(folder, 0755);

    FILE *orig;
    suppress_stdout_start(&orig);
    cmd_rmdir((char *)folder);
    suppress_stdout_end(orig);

    if (!folder_exists(folder))
    {
        printf(GREEN "test_rmdir passed!\n" RESET);
    }
    else
    {
        printf(RED "test_rmdir failed!\n" RESET);
    }
}

int file_exists(const char *name)
{
    struct stat st;
    return stat(name, &st) == 0 && S_ISREG(st.st_mode);
}

void test_touch()
{
    const char *filename = "test_file.txt";

    if (file_exists(filename))
        unlink(filename);

    FILE *orig;
    suppress_stdout_start(&orig);
    cmd_touch((char *)filename);
    suppress_stdout_end(orig);

    if (file_exists(filename))
    {
        printf(GREEN "test_touch passed!\n" RESET);
    }
    else
    {
        printf(RED "test_touch failed!\n" RESET);
    }

    unlink(filename);
}

void test_rm() {
    const char *file = "test_file.txt";

     int fd = open(file, O_CREAT | O_WRONLY, 0644);
    if (fd >= 0) close(fd);

    if (!file_exists(file)) {
        printf(RED "Failed to create file for test.\n" RESET);
        return;
    }

    FILE *orig = stdout;
    stdout = fopen("/dev/null", "w");

    cmd_rm((char *)file);  

    fclose(stdout);
    stdout = orig;

    if (!file_exists(file)) {
        printf(GREEN "test_rm passed!\n" RESET);
    } else {
        printf(RED "test_rm failed!\n" RESET);
    }
}

int main(void)
{
    test_mkdir();
    test_rmdir();
    test_touch();
    test_rm();
    return 0;
}
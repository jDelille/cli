#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "../include/commands.h"

void hello_world() {
    printf("Hello world!\n");
}

void cmd_mkdir(char *args) {
    if (mkdir(args, 0755) == 0) {
        printf("Directory '%s' created.\n", args);
    } else {
        printf("Error creating '%s' : '%s\n", args, strerror(errno));
    }
}
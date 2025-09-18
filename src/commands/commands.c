#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include "commands.h"

void create_c_file(FILE *f, const char *name, bool has_args) {
    fprintf(f, "#include <stdio.h>\n\n");
    has_args ? fprintf(f, "int main(int argc, char *argv[]) {\n") : fprintf(f, "int main() {\n");
    fprintf(f, "    printf(\"This is the %s file\\n\");\n", name);
    fprintf(f, "    return 0;\n");
    fprintf(f, "}\n");
}

void create_file(const char *name, const char *type, bool has_args) {
    char filename[256];
    snprintf(filename, sizeof(filename), "%s.%s", name, type);

    // check if file exists first
    if (access(filename, F_OK) == 0) {
        printf("Error: file %s already exists\n", filename);
        return;
    }

    FILE *f = fopen(filename, "w");
    if (!f) { 
        perror("Error creating file"); 
        return; 
    }

    if (strcmp(type, "c") == 0) {
        create_c_file(f, name, has_args);
    } else {
        fprintf(f, "Unknown type, creating empty file\n");
    }

    fclose(f);
    printf("Created file: %s\n", filename);
}

void delete_file(const char *filename) {
    mkdir(".trash", 0700);

    char trash_path[512];
    snprintf(trash_path, sizeof(trash_path), ".trash/%s", filename);

    if (rename(filename, trash_path) == 0) {
        printf("Moved %s to .trash\n", filename);
        fflush(stdout);

    } else {
        perror("Error deleting file.");
    }
}

void recover_file(const char *filename) {
    char trash_path[512];
    snprintf(trash_path, sizeof(trash_path), ".trash/%s", filename);

    if (access(trash_path, F_OK) != 0) {
        printf("File %s not found in .trash\n", filename);
        return;
    }

    if (rename(trash_path, filename) == 0) {
        printf("Recovered file: %s\n", filename);
        fflush(stdout);

    } else {
        perror("Error recovering file");
    }
}

void empty_trash() {
    DIR *dir = opendir(".trash");
    if (!dir) {
        perror("Error opening .trash");
        return;
    }

    struct dirent *entry;
    char filepath[512];

    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;

        snprintf(filepath, sizeof(filepath), ".trash/%s", entry->d_name);
        if (remove(filepath) != 0) {
            perror("Error deleting file");
        }
    }

    closedir(dir);
    puts("Trash emptied.");
}

void clear() {
    system("clear");
}
#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

void create_file(const char *name, const char *ext, bool has_args);
void delete_file(const char *filename);
void recover_file(const char *filename);
void empty_trash();
void clear();

#endif
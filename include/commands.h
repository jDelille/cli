#ifndef COMMANDS_H
#define COMMANDS_H

#include "../include/structs.h"

void cmd_mkdir();
void cmd_rmdir();
void cmd_touch();
void cmd_cd(char *args);
void cmd_clear();
void cmd_exit();
void cmd_rm();
void cmd_ls();
void cmd_help(char *args);

extern Command commands[];


#endif
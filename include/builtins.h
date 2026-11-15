#ifndef BUILTINS_H
#define BUILTINS_H

#include "parser.h"



void exec_echo(args* cmd);
void exec_cd(args* cmd);
void exec_pwd();
void exec_exit();

#endif
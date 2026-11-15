#ifndef PIPE_EXEC_H
#define PIPE_EXEC_H

#include "builtins.h"
#include "parser.h"
#include "process.h"
#include "redirections.h"

void exec_pipe(args* cmd);

#endif
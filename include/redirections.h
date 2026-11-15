#ifndef REDIRECTIONS_H
#define REDIRECTIONS_H

#include "builtins.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void redir_in(redirections* redir);
void redir_out(redirections* redir);
void redir_append(redirections* redir);
void redirect_exec(args* cmd);

#endif
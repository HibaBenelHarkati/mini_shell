#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"




typedef struct redirections{
    char* file;                             
    const char* type_redir;                 //operation of redirections: redir_in , redir_out , append , heredoc
    redirections *next_red;    
}redirections;

typedef struct args{
    char** argv;                            //commands or files 
    size_t argc;
    redirections *ptr1;                     //ptr1:  
    args *next_part;
}args;
 
args* add_cmd(char* val, args* current);
void add_args(char* val, args* current);
void add_redir(args* current, const char* type, char* value);
void init_redir(args* current, const char* type, char* value);
args* parser(partition* tokens);

#endif
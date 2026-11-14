#include "redirections.h"
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <unistd.h>
#include <sys/wait.h>

void redirect_exec(args* cmd){
    redirections* redir = cmd->ptr1;
    pid_t process=fork();

    if (process<0){std::cout<<"error in fork";}
    else if(process==0){
        while(redir!=NULL){
            if(redir!=NULL){
                if(strcmp(redir->type_redir,"REDIR_IN")==0){
                    redir_in(redir);
                }
                else if(strcmp(redir->type_redir,"REDIR_OUT")==0){
                    redir_out(redir);
                }
                else if(strcmp(redir->type_redir,"APPEND")==0){
                    redir_append(redir);
                }
            }
            redir = redir->next_red;}
        if(strcmp(cmd->argv[0],"echo")==0){ //builtins
            exec_echo(cmd);
        }
        else{
            execvp(cmd->argv[0], cmd->argv);
        }
    }
    else{
        int wc=wait(NULL);
    }
}


void redir_out(redirections* redir){
    int f=open(redir->file, O_CREAT |O_TRUNC |O_WRONLY, 00700);
    dup2(f, STDOUT_FILENO);
    close(f);
}
void redir_in(redirections* redir){
    int f=open(redir->file, O_RDONLY, 00700);
    dup2(f, 0);
    close(f);
}
void redir_append(redirections* redir){
    int f=open(redir->file, O_CREAT |O_APPEND |O_WRONLY, 00700);
    dup2(f, STDOUT_FILENO);
    close(f);
}

/*
int main(){
    char* input=NULL;
    size_t size=0;

    std::cout << "Enter a command: ";
    getline(&input,&size, stdin);
    partition* liste= tokenize_input(input);
    size=strlen(input);
    partition* ptr;
    ptr=liste;
    args* head=parser(liste);
    redirect_exec(head);
}
*/
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <unistd.h>
#include <sys/wait.h>
#include "include/parser.h"
#include "include/builtins.h"
#include "include/pipe_exec.h"
#include "include/redirections.h"
#include "include/tokenizer.h"
#include "include/process.h"


void integration(args* cmd){
        args* temp=cmd; 
        if (temp->next_part != NULL){
            exec_pipe(temp);
        }
        else if (temp->ptr1 != NULL){
            redirect_exec(temp);
        }

        //builtins
        else if(strcmp(temp->argv[0],"cd") ==0){
            exec_cd(temp);
        }
        else if( strcmp(temp->argv[0],"echo")==0){
                exec_echo(temp);
        }
        else if( strcmp(temp->argv[0],"pwd")==0){
            exec_pwd();
        }
        else{

            pid_t pid = fork();
            if (pid == 0) {
                exec_cmd(temp);
                _exit(EXIT_SUCCESS);

            }
            else if (pid > 0) {
                waitpid(pid, NULL, 0);
            }
            else {
                perror("fork");
            }
                }
    }



int main(){
    char* input=NULL;
    size_t size;
    for(;;){
        std::cout << "Enter a command: "<<std::flush;
        getline(&input,&size, stdin);

    

        partition* liste= tokenize_input(input);
        size=strlen(input);
        partition* ptr;
        ptr=liste;
        
        args* head=parser(liste);
        integration(head);
    }
    return 0;
}
#include<stdio.h>
#include "process.h"
#include<iostream>
#include<cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>


void exec_cmd(args* cmd){
    pid_t process=fork();

    if(process<0){
        std::cout<<"fork failed";
    }

    else if (process==0){
        execvp(cmd->argv[0],cmd->argv);
    }
    else{
        int wc=wait(NULL);
    }
}
/*
int main(){
    char* input=NULL;
    size_t size;
    std::cout << "Enter a command: ";
    getline(&input,&size, stdin);
    partition* liste= tokenize_input(input);
    size=strlen(input);
    partition* ptr;
    ptr=liste;
    
    args* head=parser(liste);
    exec_cmd(head);
    return 0;
}*/
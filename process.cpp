#include<stdio.h>
#include "include/process.h"
#include<iostream>
#include<cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

 
void exec_cmd(args* cmd){
    
    execvp(cmd->argv[0],cmd->argv);
    
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
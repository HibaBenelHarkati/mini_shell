#include<stdio.h>
#include "shell.h"
#include<iostream>
#include<cstdlib>

char** parse_input(char* input){
    size_t buffer_size=MAX_INPUT;
    size_t size_token;                  //do not know the size of each token 
    
    char** tokens;
    char* token=NULL;

    tokens=(char**)malloc(buffer_size*sizeof(char*));

    if (tokens==NULL){    
        std::cerr<<"Memory allocation FAILED !"
        exit(EXIT_FAILURE);
    }

    //tokenisation





    return token;
}

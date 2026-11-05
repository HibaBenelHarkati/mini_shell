#include<stdio.h>
//#include "shell.h"
#include<iostream>
#include<cstdlib>
#include <cstring>


char** parse_input(char* input){

    size_t buffer_size=strlen(input)+1;
    size_t size_token=0;                  //do not know the size of each token 
    size_t j=0;
    size_t i=0;

    char** tokens=(char**)malloc(buffer_size*sizeof(char*));
    size_t length=0;
    size_t ptr=0;

    
    
    while(input[i]!='\0'){
    
        while(input[i]!=' '&& input[i]!='\0' && input[i]!='\n'){
            size_token++;       //counts the lenghth of each token
            i++;
        }
        //space allocation
        tokens[j]=(char*)malloc((size_token+1)*sizeof(char));
        
        if (tokens[j]==NULL){
            std::cerr<<"Memory allocation FAILED !";
            exit(EXIT_FAILURE);
        }
        for(size_t k=0; k<size_token; k++){
            tokens[j][k]=input[ptr+k];
        }
        tokens[j][size_token]='\0';
        ptr=i+1;                     //add the loops break +1 tp avoid the space
        j++;
        i++;
        size_token = 0;
    }
    //tokenisation

    return tokens ;


}
int main(){
    char* input=NULL;
    size_t size;
    std::cout << "Enter a command: ";
    getline(&input,&size, stdin);

    char** tokens = parse_input(input);
    size=strlen(input);


    for (int i = 0; i<size; i++) {
        std::cout<<tokens[i]<<std::endl;
    }


    return 0;
}


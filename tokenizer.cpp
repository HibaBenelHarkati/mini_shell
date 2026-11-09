#include<stdio.h>
#include "tokenizer.h"
#include<iostream>
#include<cstdlib>
#include <cstring>


partition* tokenize_input(char* input){

    size_t buffer_size=strlen(input)+1;
    size_t size_token=0;                  //do not know the size of each token 
    size_t i=0;


    //initiating the header of the linked list
    partition* tokens=NULL; //head

    partition* ptr=NULL;
    ptr=tokens;

    size_t length=0;
    size_t start=0;

    
    
    while(input[i]!='\0'){
    
        while(input[i]!=' '&& input[i]!='\0' && input[i]!='\n'){
            size_token++;       //counts the lenghth of each token
            i++;
        }

        partition* current=(partition*)malloc(sizeof(partition));
        current->next=NULL;

        if (current==NULL){
            std::cout<<"allocation error";
        }
        if(tokens==NULL){
            tokens=current; //head of the list 
        }

        else{
            ptr->next=current;
        }

        current->value=(char*)malloc(size_token + 1);
        //fill the struct
        //value
        for(size_t k=0; k<size_token; k++){
            current->value[k]=input[start+k];
        }
        current->value[size_token]='\0';

      
        if (strcmp(current->value, "|") == 0)
            current->type = "PIPE";

        else if (strcmp(current->value, "<") == 0)
            current->type = "REDIR_IN";

        else if (strcmp(current->value, ">") == 0)
            current->type = "REDIR_OUT";

        else if (strcmp(current->value, ">>") == 0)
            current->type = "APPEND";

        else if (strcmp(current->value, "<<") == 0)
            current->type = "HEREDOC";

        else
            current->type = "WORD";

     
        ptr=current;      //increment the ptr

        start=i+1;                     //add the loops break +1 tp avoid the space
        i++;
        size_token = 0;
    }
    //tokenisation
    
    return tokens ;


}

/*
int main(){
    char* input=NULL;
    size_t size;
    std::cout << "Enter a command: ";
    getline(&input,&size, stdin);

    partition* liste= parse_input(input);
    size=strlen(input);
    partition* ptr;
    ptr=liste;
    
    while(ptr!=NULL){
        std::cout<<ptr->value<<" Type "<<ptr->type<<std::endl;
        ptr=ptr->next;
    }


    return 0;
}*/


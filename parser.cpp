

#include "parser.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <iostream>


//linkedList partition commands, linked_list files(files_names, ope)=>partions commands2


//adds args (linked list) and adds the values retrieved from our tokens previous defined linkedlist


//creates a new node
args* add_cmd(char* val, args* current){
    args* node= (args*)malloc(sizeof(args));
    if(node==NULL){
        return NULL; 
    }
    node->argv=(char**)malloc(sizeof(char*)*2); //token + null 
    
    node->argv[0]=strdup(val);
    node->argv[1]=NULL;
    node->argc=1;
    node->ptr1=NULL;
    node->next_part=NULL;

    current->next_part=node;
    return node;    //previous address
}

    
void add_args(char* val, args* current){
    char** tmp=(char**)realloc(current->argv, sizeof(char*)*(current->argc+2));
    if (tmp==NULL){
        return;
    }
    current->argv=tmp;
    current->argv[current->argc]=strdup(val);
    current->argc++;
    current->argv[current->argc]=NULL;
}    



void add_redir(args* current, const char* type, char* value){
    redirections* ptr=(redirections*)malloc(sizeof(redirections));
    if(ptr==NULL){return;}


    ptr->file=strdup(value);
    ptr->type_redir=strdup(type);

    ptr->next_red=NULL;
    redirections* temp=current->ptr1;       //debut de
    while(temp->next_red!=NULL){
        temp=temp->next_red;
    }
    temp->next_red=ptr;

}


void init_redir(args* current, const char* type, char* value){
    
    redirections* ptr=(redirections*)malloc(sizeof(redirections));
    current->ptr1=ptr;      //ou head
    current->ptr1->file=strdup(value);;
    current->ptr1->type_redir=strdup(type);
    current->ptr1->next_red=NULL;
}




args* parser(partition* tokens){
    
    args* head=NULL;       //linked list"1" (head): args (commandes)
    args* current=(args*)malloc(sizeof(args));
    current->argv=NULL;      
    current->argc=0;
    current->ptr1=NULL;      
    current->next_part=NULL;
    head=current;

    partition* iter;        //linked list"2":tokens
    iter=tokens;
    
    while(iter!=NULL){

        if(strcmp(iter->type,"WORD")==0  && current->argc==0){
            current->argv=(char**)malloc(sizeof(char*)*2);
            current->argv[0] = strdup(iter->value);
            current->argv[1] = NULL;

            current->argc=1;
        }

        else if(strcmp(iter->type,"WORD")==0 && current->argc!=0){
            add_args(iter->value, current); //on ne cree pas le node mais on ajoute jsute ñle lement a la liste si ell est initalisse
        }
        
        else if(strcmp(iter->type,"REDIR_IN")==0 || strcmp(iter->type,"REDIR_OUT")==0 || strcmp(iter->type,"APPEND")==0 || strcmp(iter->type,"HEREDOC")==0 ){
            if(current->ptr1==NULL){        //no redirections before
                init_redir(current, iter->type, iter->next->value);
            }
            else{ 
                add_redir(current,iter->type, iter->next->value);
            }   
            //here we have to increment(skip twicethe current which is the files name)
            iter = iter->next;
        }
        
        else if(strcmp(iter->type,"PIPE")==0){   //create a new commande 
            iter=iter->next;    //point to the next node
            current=add_cmd(iter->value,  current);
        }
        iter=iter->next;

    }
    return head;
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
    args* temp=head;
    while(temp!=NULL){
        for (size_t  i=0; i <temp->argc; i++){
            std::cout << "argument"<<i<<" : "<<temp->argv[i] << std::endl;
        }
        std::cout<<"Number of args:"<<" "<<temp->argc<<std::endl;

        redirections* temp1=temp->ptr1;
        if(temp1!=NULL){
            std::cout<<"redirections"<<std::endl;

            while(temp1!=NULL){
                std::cout<<"type of redirection:"<<temp1->type_redir<<std::endl;
                std::cout<<"redirection files:"<<temp1->file<<std::endl;
                temp1=temp1->next_red;
            }
        }
       
        
        temp=temp->next_part;
    }
        
    


    return 0;
}
*/


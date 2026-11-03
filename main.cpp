#include <stdio.h>
#include<iostream>
#include "shell.h"

//shell loop : infinite command loop ; cause the shel displays a prompt waiting for users input => cmd is broken into tokens to interpret commands and their args
//signal handling (shell termination , inetrruptipon ) 
//error handling: incorrect commands
// processs management: each command runs in  a sperate process 
//shell three main things: init this is done in the main function where the config shell state is done and init of the variables , interpret:read the command from stdin, terminate after the commadns execution the shell frees up any memory and terminates 
//&cmd adresse du pointer cmd adresse du cmd 




void shell_loop(){
    char* cmd=NULL;                       
    size_t  buffer_size;                                 
    
    for(;;){
       auto nread= getline(&cmd, &buffer_size, stdin)  ;   
       if (nread==-1){
            break;
       } 

       //std::cout<<cmd<< std::endl ;      
       args=parse_input(cmd)
    }
}




int main(){
    std::cout<<"hiba"<<std::endl;
    shell_loop();
    return 0;
}
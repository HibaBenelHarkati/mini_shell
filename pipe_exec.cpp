#include "include/pipe_exec.h"

#include <unistd.h>
#include <sys/wait.h>


void exec_pipe(args* cmd){
    args* temp = cmd;
    size_t n = 0;

    while (temp != NULL){
        n++;
        temp = temp->next_part;
    }

    temp = cmd;
    int dfs[n-1][2];

    for (size_t i = 0; i < n-1; i++){
        pipe(dfs[i]);
    }

    for (size_t i = 0; i < n; i++){
        pid_t pid = fork();
        if (pid == 0){
            if (i > 0)
                dup2(dfs[i-1][0], STDIN_FILENO);

            if (i < n-1)
                dup2(dfs[i][1], STDOUT_FILENO);

            for (size_t j = 0; j < n-1; j++){
                close(dfs[j][0]);
                close(dfs[j][1]);
            }

            if (temp->ptr1 != NULL)
                redirect_exec(temp);
            
            exec_cmd(temp);
            _exit(127);
        }
        else if (pid > 0){
            temp = temp->next_part;
        }
    } 
    //parent process its importnant to close all the dfs
    for (size_t i = 0; i < n-1; i++){
        close(dfs[i][0]);
        close(dfs[i][1]);
    }
   for (int i = 0; i < n; i++){
    wait(NULL);
    }
}

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
    exec_pipe(head);
}

#include "include/builtins.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <unistd.h>

#include <unistd.h>
//use linux venv

//echo 
void exec_echo(args* cmd){
    for(size_t i = 1; i < cmd->argc; i++){
        std::cout << cmd->argv[i] << " ";
    }
    std::cout << std::endl;
}

//cd
void exec_cd(args* cmd){
   // std::cout << "PID exec_cd : " << getpid() << std::endl;
    char current_path[PATH_MAX];
    char new_path[PATH_MAX];
    char *path;

    if (cmd->argc == 1){  //cd :: home
        getcwd(current_path, sizeof(current_path));
        path = getenv("HOME");
        chdir(path);
        setenv("OLDPWD", current_path, 1);
        getcwd(new_path, sizeof(new_path));
        setenv("PWD", new_path, 1);
        std::cout << new_path << std::endl;

    }

    else if (strcmp(cmd->argv[1], "-") == 0){   //go back to the latest visited path
        getcwd(current_path, sizeof(current_path));
        path = getenv("OLDPWD");
        chdir(path);
        setenv("OLDPWD", current_path, 1);
        getcwd(new_path, sizeof(new_path));
        setenv("PWD", new_path, 1);
        std::cout << new_path << std::endl;
    }

    else if (strcmp(cmd->argv[1], "..") == 0){   
        getcwd(current_path, sizeof(current_path));
        chdir("..");
        setenv("OLDPWD", current_path, 1);
        getcwd(new_path, sizeof(new_path));
        setenv("PWD", new_path, 1);
        std::cout << new_path << std::endl;

    }

    else if (strcmp(cmd->argv[1], "~") == 0){   
        getcwd(current_path, sizeof(current_path));
        path = getenv("HOME");
        chdir(path);
        setenv("OLDPWD", current_path, 1);
        getcwd(new_path, sizeof(new_path));
        setenv("PWD", new_path, 1);
        std::cout << new_path << std::endl;

    }

    else {  //full path
        std::cout << "Chemin reçu : " << cmd->argv[1] << std::endl;

        if (chdir(cmd->argv[1]) == -1) {
            perror("chdir");
            return;
        }
        char path[PATH_MAX];
        if (getcwd(path, sizeof(path)) == NULL) {
            perror("getcwd");
            return;
        }

        std::cout << "Nouveau répertoire : " << path << std::endl;
    }

}


void exec_pwd(){
    char current_path[PATH_MAX];
    getcwd(current_path, sizeof(current_path));
    std::cout<<current_path<<std::endl;
}



















//pwd
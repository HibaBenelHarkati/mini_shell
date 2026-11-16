#ifndef TOKENIZER_H
#define TOKENIZER_H


#include<stdio.h>
#include<cstdlib>



typedef struct partition{
    char* value; 
    const char* type;
    struct partition *next;
}partition;


partition* tokenize_input(char* input);
#endif
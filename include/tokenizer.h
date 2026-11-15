#include<stdio.h>
#include<cstdlib>

#define MAX_INPUT 1000


typedef struct partition{
    char* value; 
    const char* type;
    struct partition *next;
}partition;


partition* tokenize_input(char* input);

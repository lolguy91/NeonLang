
#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdio.h>



typedef struct {
    void* prev;

    char type;
    int val;

    void* next;
} word;

word* parse(FILE* fp);


#endif // __PARSER_H__
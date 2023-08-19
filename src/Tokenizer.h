
#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdio.h>
#include <ctype.h>

#define TYPE_KEYWORD 1
#define TYPE_INT_LIT 2
#define TYPE_SEMI    3


typedef struct {
    void* prev;

    char type;
    int val;

    void* next;
} Token;

Token* tokenize(FILE* fp);


#endif // __PARSER_H__

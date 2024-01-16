#ifndef DATATYPE_H
#define DATATYPE_H
struct data;

struct datatype {
    int keyword_id;
    int size;
    int align;
    struct data (*index)(struct data toindex,bool use_string_index,int numerical_index,char* string_index);
}

#endif
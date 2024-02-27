#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stdbool.h>

#define PROGSIG 0x00
#define STMTSIG 0x01
#define EXPRSIG 0x02
#define DATASIG 0x03
#define IDENTSIG 0x04
#define SCOPESIG 0x05
#define CONDSIG 0x06

#define STMTTYPE_DECL 0
#define STMTTYPE_ASSIGN 1
#define STMTTYPE_CALL 2
#define STMTTYPE_BRANCH 3
#define STMTTYPE_LOOP 4

#define EXPRTYPE_LITERAL 0
#define EXPRTYPE_UNARY 1
#define EXPRTYPE_BINARY 2
#define EXPRTYPE_TRINARY 3

struct identifier{
    uint8_t signature;
    uint16_t id;
    char* name;
};

struct expression{
    uint8_t signature;
    uint8_t type;
    union{
        struct {
            struct identifier data;
        } literal;
        struct {
            uint16_t op;
            struct expression* expr;
        } unary;
        struct {
            uint16_t op;
            struct expression* left;
            struct expression* right;
        } binary;
        struct {
            uint16_t op;
            struct expression* left;
            struct expression* middle;
            struct expression* right;
        } trinary;
    };
};
struct scope;

struct condition{
    uint8_t signature;
    struct expression* condition;
    struct scope* iftrue;
    struct scope* iffalse;
};
struct statement{
    uint8_t signature;
    uint8_t type;
    union{
        struct decl{
            bool hasinit;
            struct identifier id;
            struct expression* init;
        };
        struct assign{
            struct expression left;
            struct expression* right;
        };
        struct call{
            struct expression* callee;
            struct expression* args;
            uint8_t num_args;
        };
        struct branch{
            uint16_t num_conditions;
            struct condition* conditions;
        };
        struct loop{
            struct expression* exit_condition;
            struct scope* body;
        };
    };
};
struct scope{
    uint8_t signature;
    struct statement* statements;
    struct identifier *idents;
    uint16_t num_idents;
    uint16_t num_statements;
    struct scope* parent;
};
struct program{
    uint8_t signature;
    struct scope *godscope;
};

#endif
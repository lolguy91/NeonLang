#ifndef __PARSER_H__
#define __PARSER_H__

#include <Tokenizer.h>
#include <stdbool.h>

#define AST_PROGRAM_NODE        1
#define AST_DECLARATION_NODE    2
#define AST_ASSIGNMENT_NODE     3
#define AST_VARIABLE_NODE       4
#define AST_FUNCTION_NODE       5
#define AST_RETURN_NODE         6
#define AST_IF_NODE             7
#define AST_WHILE_LOOP_NODE     8
#define AST_FOR_LOOP_NODE       9
#define AST_BINARY_EXPR_NODE    11
#define AST_PRIMARY_EXPR_NODE   12
#define AST_IDENTIFIER_NODE     13
#define AST_INT_LIT_NODE        14
#define AST_BOOL_LIT_NODE       15

typedef enum {
    OP_BIN_ADD,
    OP_BIN_SUB,
    OP_BIN_MUL,
    OP_BIN_DIV,
    OP_BIN_MOD,
    OP_BIN_AND,
    OP_BIN_OR
} BinaryOperator;

typedef enum {
    OP_NOT,
    OP_NOPE
} PrimaryOperator;

// AST Node Struct
struct ASTNode{
    int type; // Type ID for the AST node
    union {
        struct {
            struct ASTNode** statements;
            int num_statements;
        } program;

        struct {
            int data_type; // Data type identifier (e.g., 'u8', 'i32')
            char* identifier;
            struct ASTNode* expression;
        } declaration;

        struct {
            char* identifier;
            struct ASTNode* expression;
        } assignment;

        struct {
            int data_type; // Data type identifier (e.g., 'float')
            char* identifier;
            struct ASTNode* expression; // For variable initialization
        } varible;

        struct {
            int return_type; // Return data type (e.g., 'int', 'float')
            char* identifier;
            struct ASTNode** parameters; // Function parameters as AST nodes
            int num_parameters;
            struct ASTNode* compound_statement; // Function body
        } function;

        struct {
            struct ASTNode* expression;
        } return_statement;

        struct {
            struct ASTNode* condition;
            struct ASTNode** if_statements;
            int num_if_statements;
            struct ASTNode** else_statements;
            int num_else_statements;
        } if_statement;

        struct {
            struct ASTNode* condition;
            struct ASTNode** statements;
            int num_statements;
        } while_loop;

        struct {
            struct ASTNode* initialization;
            struct ASTNode* condition;
            struct ASTNode* increment;
            struct ASTNode** statements;
            int num_statements;
        } for_loop;

        struct {
            int operator; // Operator type (e.g., '+', '-', '*', '/', '%', '&&', '||', '!', '==', '!=', '<', '>', '<=', '>=')
            struct ASTNode* left;
            struct ASTNode* right;
        } binary_expression;

        struct {
            int value;
        } int_lit;

        struct {
            bool value;
        } bool_lit;

        struct {
            char* name;
        } identifier;

        struct {
            int type;
            struct ASTNode* expression;
        } primary_expression;
    };
};

struct ASTNode* parse(struct Token* tokens);

#endif // __PARSER_H__
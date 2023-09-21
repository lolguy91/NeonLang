#include "Parser.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <Tokenizer.h>

struct ASTNode* current_node;
struct Token* current_token;

//Forward declarations

// Function to parse an expression
struct ASTNode* parse_expression(struct Token* tokens);

// Function to parse a primary expression (e.g., integer literals, identifiers, parentheses)
struct ASTNode* parse_primary_expression(struct Token* tokens);

// Helper function to parse binary expressions recursively
struct ASTNode* parse_binary_expression(struct Token* tokens, int precedence);


bool is_type_keyword(struct Token* token) {

    return token->val > 0 && token->val < 9;
}

// Function to parse a binary expression based on operator precedence
struct ASTNode* parse_binary_expression(struct Token* tokens, int precedence)
{
    // Implement operator precedence parsing here
    // You need to consider the precedence of operators to build the AST correctly
    // For simplicity, let's assume left-associative operators

    struct ASTNode* left = parse_primary_expression(tokens);

    while (current_token->type == TYPE_ADD || current_token->type == TYPE_SUB ||
           current_token->type == TYPE_MUL || current_token->type == TYPE_DIV ||
           current_token->type == TYPE_MOD || current_token->type == TYPE_OR ||
           current_token->type == TYPE_AND) {
        // Determine the operator and its precedence
        BinaryOperator op;
        int OP_BIN_precedence;

        switch (current_token->type) {
            case TYPE_ADD:
                op = OP_BIN_ADD;
                OP_BIN_precedence = 1;
                break;
            case TYPE_SUB:
                op = OP_BIN_SUB;
                OP_BIN_precedence = 1;
                break;
            case TYPE_MUL:
                op = OP_BIN_MUL;
                OP_BIN_precedence = 2;
                break;
            case TYPE_DIV:
                op = OP_BIN_DIV;
                OP_BIN_precedence = 2;
                break;
            case TYPE_MOD:
                op = OP_BIN_MOD;
                OP_BIN_precedence = 2;
                break;
            case TYPE_AND:
                op = OP_BIN_AND;
                OP_BIN_precedence = 2;
                break;
            case TYPE_OR:
                op = OP_BIN_OR;
                OP_BIN_precedence = 2;
                break;
            default:
                // Handle error: Invalid operator
                // You should implement appropriate error handling logic here
                return NULL;
        }

        // Check operator precedence
        if (OP_BIN_precedence < precedence) {
            return left; // Return the current left node
        }

        // Move to the next token
        current_token = current_token->next;

        // Parse the right operand recursively with higher precedence
        struct ASTNode* right = parse_binary_expression(tokens, OP_BIN_precedence + 1);
        if (!right) {
            // Handle error: Failed to parse the right operand
            // You should implement appropriate error handling logic here
            return NULL;
        }

        // Create a new expression node
        struct ASTNode* expr_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
        expr_node->type = AST_BINARY_EXPR_NODE;
        expr_node->binary_expression.operator = op;
        expr_node->binary_expression.left = left;
        expr_node->binary_expression.right = right;

        left = expr_node; // Update the left node for the next iteration
    }

    return left; // Return the final expression node
}

// Function to parse a primary expression (e.g., integer literals, identifiers, parentheses)
struct ASTNode* parse_primary_expression(struct Token* tokens)
{
    // Implement parsing of primary expressions here
    // This function can handle literals, identifiers, and parentheses

    // Placeholder for simplicity
    // You should extend this to handle your language's syntax

    if (current_token->type == TYPE_INT_LIT) {
        // Parse integer literal
        struct ASTNode* int_lit_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
        int_lit_node->type = AST_INT_LIT_NODE;
        int_lit_node->int_lit.value = current_token->val;

        // Move to the next token
        current_token = current_token->next;

        return int_lit_node;

    }else if (current_token->type == TYPE_KEYWORD) {
        if (current_token->val == 11)
        {
            // Parse boolean literal
            struct ASTNode* bool_lit_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
            bool_lit_node->type = AST_BOOL_LIT_NODE;
            bool_lit_node->int_lit.value = true;

            // Move to the next token
            current_token = current_token->next;

            return bool_lit_node;

        } else if (current_token->val == 12)
        {
            // Parse boolean literal
            struct ASTNode* bool_lit_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
            bool_lit_node->type = AST_BOOL_LIT_NODE;
            bool_lit_node->bool_lit.value = false;

            // Move to the next token
            current_token = current_token->next;

            return bool_lit_node;

        }
        
    } else if (current_token->type == TYPE_IDENT) {
        // Parse identifier
        struct ASTNode* ident_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
        ident_node->type = AST_IDENTIFIER_NODE;
        ident_node->identifier.name = (char*)current_token->val;

        // Move to the next token
        current_token = current_token->next;

        return ident_node;
    } else if (current_token->type == TYPE_OPEN) {
        // Handle parentheses
        // Parse the expression within parentheses
        current_token = current_token->next; // Move past the opening parenthesis
        struct ASTNode* expr_node = parse_expression(tokens);

        if (current_token->type != TYPE_CLOSE) {
            // Handle error: Expected closing parenthesis
            // You should implement appropriate error handling logic here
            return NULL;
        }

        current_token = current_token->next; // Move past the closing parenthesis
        return expr_node;
    } else if (current_token->type == TYPE_NOT) {
        // Parse identifier
        struct ASTNode* not_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
        not_node->type = AST_PRIMARY_EXPR_NODE;
        not_node->primary_expression.type = OP_NOT;

        current_token = current_token->next;
        not_node->primary_expression.expression = parse_expression(tokens);

        return not_node;
    } else if (current_token->type == TYPE_NOPE) {
        // Parse identifier
        struct ASTNode* nope_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
        nope_node->type = AST_PRIMARY_EXPR_NODE;
        nope_node->primary_expression.type = OP_NOPE;

        current_token = current_token->next;
        nope_node->primary_expression.expression = parse_expression(tokens);

        return nope_node;
    } else {
        // Handle error: Invalid primary expression
        // You should implement appropriate error handling logic here
        return NULL;
    }
}

// Function to parse an expression
struct ASTNode* parse_expression(struct Token* tokens)
{
    // Start by parsing the lowest precedence operator (e.g., '+', '-')
    // Pass 1 as the initial precedence to parse_binary_expression
    return parse_binary_expression(tokens, 1);
}

// Function to parse a function declaration
struct ASTNode* parse_function_definition(struct Token* tokens)
{
    struct ASTNode* function_declaration_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    // Initialize the fields of function_declaration_node for function declaration
    function_declaration_node->type = AST_FUNCTION_NODE; // Define AST_FUNCTION_NODE as needed

    // Parse the function declaration based on your language's syntax

    return function_declaration_node;
}

struct ASTNode* parse_declaration(struct Token* tokens)
{
    struct ASTNode* declaration_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    declaration_node->type = AST_DECLARATION_NODE;

    // Assuming 'current_token' is the current token being processed
    // Check if it's a valid data type token (e.g., 'u8', 'i32', 'float')
    if (current_token->type == TYPE_KEYWORD) {
        // Set the data type field of the declaration_node based on the token value
        declaration_node->declaration.data_type = current_token->val;

        // Move to the next token
        current_token = current_token->next;
    } else {
        // Handle error: Invalid data type
        // You should implement appropriate error handling logic here
        free(declaration_node);
        return NULL;
    }

    // Assuming 'current_token' now points to an identifier
    if (current_token->type == TYPE_IDENT) { 
        // Set the identifier field of the declaration_node
        declaration_node->declaration.identifier = (char*)current_token->val; // Assuming 'value' is the identifier's value

        // Move to the next token
        current_token = current_token->next;
    } else {
        // Handle error: Expected an identifier
        // You should implement appropriate error handling logic here
        free(declaration_node);
        return NULL;
    }
    if (current_token->type != TYPE_EQUALS) {
        // Handle error: Expected an identifier
        // You should implement appropriate error handling logic here
        free(declaration_node);
        return NULL;
    }else{
        current_token = current_token->next;
    }

    // Check if it's an function definition
    if (current_token->type == TYPE_OPEN && current_token->val == 1) { 
        // It's an function definition, call the function to parse a function definition
        declaration_node->declaration.expression = parse_function_definition(tokens);
    } else {
        // It's a variable declaration, call the function to parse variable'a expression
        declaration_node->declaration.expression = parse_expression(tokens);
    }

    return declaration_node;
}


struct ASTNode* parse(struct Token* tokens)
{
    // Create the program node
    struct ASTNode* program_node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    program_node->type = AST_PROGRAM_NODE; // Define AST_PROGRAM_NODE as needed

    current_token = tokens;
    current_node  = program_node;


    // Initialize fields of the program node
    // For example:
    program_node->program.statements = NULL; // Initialize with an empty statement list
    program_node->program.num_statements = 0; // Initialize the number of statements

    // Parse statements and add them to the program node
    while (current_token->type != 0) {
        // Parse a statement and add it to the program_node
        struct ASTNode* statement_node = parse_declaration(tokens);
        if (statement_node != NULL) {
            // Increase the number of statements
            program_node->program.num_statements++;

            // Reallocate memory to store the statements
            program_node->program.statements = (struct ASTNode**)realloc(
                program_node->program.statements,
                program_node->program.num_statements * sizeof(struct ASTNode*)
            );

            // Add the statement to the list
            program_node->program.statements[program_node->program.num_statements - 1] = statement_node;
        }else{
            current_token = current_token->next;
        }
    }

    return program_node;
}

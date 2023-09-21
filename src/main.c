#include <stdio.h>
#include <Tokenizer.h>
#include "Parser.h"



// Function to print the AST hierarchically
void print_ast(struct ASTNode* node, int depth)
{
    // Indentation based on depth
    for (int i = 0; i < depth; i++) {
        printf("     ");
    }
	if (node == NULL) {
		printf("Nothing\n");
        return;
    }

    // Print node-specific information based on type
    switch (node->type) {
		case AST_PROGRAM_NODE:
			for (size_t i = 0; i < node->program.num_statements; i++)
			{
				print_ast(node->program.statements[i],depth + 1);
			}
			break;

		case AST_DECLARATION_NODE:
			printf("Declaration Type: %u \n",node->declaration.data_type);
			print_ast(node->declaration.expression,depth + 1);
			break;

        case AST_BINARY_EXPR_NODE:
            // Print binary operator
            printf("Binary Operator: ");
            switch (node->binary_expression.operator) {
                case OP_BIN_ADD:
                    printf("+\n");
                    break;
                case OP_BIN_SUB:
                    printf("-\n");
                    break;
                case OP_BIN_MUL:
                    printf("*\n");
                    break;
                case OP_BIN_DIV:
                    printf("/\n");
                    break;
                case OP_BIN_MOD:
                    printf("%%\n");
                    break;
                case OP_BIN_AND:
                    printf("&\n");
                    break;
                case OP_BIN_OR:
                    printf("|\n");
                    break;
                default:
                    printf("Unknown\n");
            }
    	
			// Indentation based on depth
    		for (int i = 0; i < depth; i++) {
    		    printf("     ");
    		}

            // Recursively print left and right operands
            printf("Left Operand:\n");
            print_ast(node->binary_expression.left, depth + 1);

    		// Indentation based on depth
    		for (int i = 0; i < depth; i++) {
    		    printf("     ");
    		}
            printf("Right Operand:\n");
            print_ast(node->binary_expression.right, depth + 1);
            break;

		case AST_PRIMARY_EXPR_NODE:
            // Print binary operator
            printf("Primary Operator: ");
            switch (node->binary_expression.operator) {
                case OP_NOT:
                    printf("~\n");
                    break;
                case OP_NOPE:
                    printf("!\n");
                    break;
                default:
                    printf("Unknown\n");
            }
    	
			// Indentation based on depth
    		for (int i = 0; i < depth; i++) {
    		    printf("     ");
    		}
            print_ast(node->binary_expression.left, depth + 1);

        case AST_INT_LIT_NODE:
            // Print integer literal value
            printf("Integer Literal: %d\n", node->int_lit.value);
            break;

		case AST_BOOL_LIT_NODE:
		    // Print booloean literal value
            printf("Boolean Literal: %s\n", node->bool_lit.value ? "true" : "false");
            break;
        case AST_IDENTIFIER_NODE:
            // Print identifier name
            printf("Identifier\n");
            break;

        // Add cases for other node types as needed

        default:
            printf("Unknown Node Type\n");
    }
}

int main(int argc, char *argv[]){
	FILE *fp;
	if (argc!=2){
	    printf("Usage: %s filename\n",argv[0]);
	    return 1;
	}

	fp=fopen(argv[1],"r");
	if (fp==NULL){
	    printf("File not found\n");
	}
	
	
	struct Token* tokens = (struct Token*) tokenize(fp);
	//while (tokens->next != 0){
	//	if(tokens->type == TYPE_KEYWORD){
	//		printf(" %s - %s\n",names[tokens->type],keyTokens[tokens->val]);	
	//	//}else if(parsed->type == TYPE_IDENT){
	//	//	printf(" %s - %s\n",names[parsed->type],*((char**)&parsed->val));	
	//	}else{
	//		printf(" %s - %i\n",names[tokens->type],tokens->val);	
	//	}
	//	tokens = tokens->next;
	//}
	//printf("-%i--%i--\n",tokens->type,tokens->val);	

	struct ASTNode* ast = parse(tokens);
	print_ast(ast,0);

	//close the file
	fclose(fp);
	return 0;
}

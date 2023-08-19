#include <Tokenizer.h>
#include <ctype.h>
#include <stdbool.h>

char* keyTokens[] = {
"return"
};

Token* tokenize(FILE* fp)
{
    //create the string buffer
    char *buffer=malloc(1024);
    
    int fscanout = fscanf(fp,"%s",buffer);
    Token* currToken = malloc(sizeof(Token));
    Token* firstToken = currToken;
    bool semicolon = false;

    while(fscanout != -1){
        semicolon = false;
	currToken->next = malloc(sizeof(Token));
        
        if(buffer[strlen(buffer) - 1] == ';'){
	    semicolon = true;	
	}
	if(isdigit(buffer[1])){
                ((Token*)currToken->next)->type = TYPE_INT_LIT;
                ((Token*)currToken->next)->val = atoi(buffer);
	        break;
	}
	for (int i = 0; i < 1; i++)
        {
	    if(!strcmp(keyTokens[i],buffer)){
                ((Token*)currToken->next)->type = TYPE_KEYWORD;
                ((Token*)currToken->next)->val = i;
                break;
            }
        }
        ((Token*)currToken->next)->prev = currToken;
        currToken = currToken->next;
	
	if(semicolon){
	    currToken->next = malloc(sizeof(Token));
	    
	    ((Token*)currToken->next)->type = TYPE_SEMI;
            ((Token*)currToken->next)->val = 0;

            ((Token*)currToken->next)->prev = currToken;
            currToken = currToken->next;
	}


        fscanout = fscanf(fp,"%s",buffer);
    }
    return firstToken;

}

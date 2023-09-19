#include <Tokenizer.h>
#include <ctype.h>
#include <stdbool.h>

char* keyTokens[] = {
//return
"return",
//types
"u8",
"u16",
"u32",
"u64",

"i8",
"i16",
"i32",
"i64",

"bool",
"float",

//boolean stuff
"true",
"false"
};
char* names[] = {
"TYPE_INVALID     ",
"TYPE_KEYWORD     ",
"TYPE_INT_LIT     ",
"TYPE_SEMI        ",
"TYPE_OPEN        ",
"TYPE_CLOSE       ",
"TYPE_IDENT       ",
"TYPE_EQUALS      ",
"TYPE_ADD         ",
"TYPE_SUB         ",
"TYPE_MUL          ",
"TYPE_DIV          ",
"TYPE_MOD          ",
"TYPE_AND          ",
"TYPE_OR           ",
"TYPE_NOT          ",
"TYPE_NOPE         ",
"TYPE_SEPARATOR    ",
"TYPE_DECIMAL_POINT"
};

bool keyword_check(Token* currToken,char* buffer){
    for (int i = 0; i < (sizeof(keyTokens) / sizeof(char*)); i++)
    {
	    if(!strcmp(keyTokens[i],buffer)){
            ((Token*)currToken->next)->type = TYPE_KEYWORD;
            ((Token*)currToken->next)->val = i;
            return true;
        }
    }
    return false;
}
bool misc_check(Token* currToken,char* buffer,int i){
    bool val = false;
    if (buffer[i] == ';')
    {
        ((Token*)currToken->next)->type = TYPE_SEMI;
        ((Token*)currToken->next)->val = 1;

        val = true;
    }
    if (buffer[i] == '=')
    {
        ((Token*)currToken->next)->type = TYPE_EQUALS;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == ',')
    {
        ((Token*)currToken->next)->type = TYPE_SEPARATOR;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == '.')
    {
        ((Token*)currToken->next)->type = TYPE_DECIMAL_POINT;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    return val;
}
bool logic_check(Token* currToken,char* buffer,int i){
    bool val = false;
    if (buffer[i] == '&')
    {
        ((Token*)currToken->next)->type = TYPE_AND;
        ((Token*)currToken->next)->val = 1;

        val = true;
    }
    if (buffer[i] == '|')
    {
        ((Token*)currToken->next)->type = TYPE_OR;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == '~')
    {
        ((Token*)currToken->next)->type = TYPE_NOT;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == '!')
    {
        ((Token*)currToken->next)->type = TYPE_NOPE;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    return val;
}
bool arith_check(Token* currToken,char* buffer,int i){
    bool val = false;
    if (buffer[i] == '+')
    {
        ((Token*)currToken->next)->type = TYPE_ADD;
        ((Token*)currToken->next)->val = 1;

        val = true;
    }
    if (buffer[i] == '-')
    {
        ((Token*)currToken->next)->type = TYPE_SUB;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == '*')
    {
        ((Token*)currToken->next)->type = TYPE_MUL;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == '/')
    {
        ((Token*)currToken->next)->type = TYPE_DIV;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == '%')
    {
        ((Token*)currToken->next)->type = TYPE_MOD;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    return val;
}
bool open_and_close_check(Token* currToken,char* buffer,int i){
    bool val = false;
    if (buffer[i] == '(')
    {
        ((Token*)currToken->next)->type = TYPE_OPEN;
        ((Token*)currToken->next)->val = 1;

        val = true;
    }
    if (buffer[i] == '{')
    {
        ((Token*)currToken->next)->type = TYPE_OPEN;
        ((Token*)currToken->next)->val = 2;
        val = true;
    }
    if (buffer[i] == '[')
    {
        ((Token*)currToken->next)->type = TYPE_OPEN;
        ((Token*)currToken->next)->val = 3;
        val = true;
    }
    if (buffer[i] == ')')
    {
        ((Token*)currToken->next)->type = TYPE_CLOSE;
        ((Token*)currToken->next)->val = 1;
        val = true;
    }
    if (buffer[i] == '}')
    {
        ((Token*)currToken->next)->type = TYPE_CLOSE;
        ((Token*)currToken->next)->val = 2;
        val = true;
    }
    if (buffer[i] == ']')
    {
        ((Token*)currToken->next)->type = TYPE_CLOSE;
        ((Token*)currToken->next)->val = 3;
        val = true;
    }
    return val;
}

Token* tokenize(FILE* fp)
{
    //create the string buffers
    char *buffer=malloc(1024);
    char *buffer2=malloc(1024);

    int fscanout = fscanf(fp,"%s",buffer);
    Token* currToken = malloc(sizeof(Token));
    currToken->next = malloc(sizeof(Token));
    currToken->prev = currToken;
    Token* firstToken = currToken->next;
    bool dummy_pervention = false;

    while(fscanout != -1){
        dummy_pervention = false;


        if(!keyword_check(currToken,buffer)){
            int imod = 0;
            for (size_t i = 0; i < strlen(buffer); i++)
            {
                buffer2[i + imod] = buffer[i];
                buffer2[i + imod + 1] = 0;

                if(isdigit(buffer[i]) && !isdigit(buffer[i+1])){
                    ((Token*)currToken->next)->type = TYPE_INT_LIT;
                    ((Token*)currToken->next)->val = atoi(buffer2);

                    ((Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(Token));
                    dummy_pervention = true;
                    imod -= strlen(buffer2);
	            }

                if (keyword_check(currToken,buffer2))
                {
                    ((Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(Token));
                    dummy_pervention = true;
                    imod -= strlen(buffer2);
                }
                
                if (open_and_close_check(currToken,buffer,i) ||
                        arith_check(currToken,buffer,i) ||
                            logic_check(currToken,buffer,i) ||
                                misc_check(currToken,buffer,i))
                {
                    ((Token*)currToken->next)->prev = currToken;
                    currToken = currToken->next;
                    currToken->next = malloc(sizeof(Token));
                    dummy_pervention = true;
                    imod--;
                }
            }
            if(imod == 0){
                char* copy_of_buffer = malloc(strlen(buffer));
                memcpy(copy_of_buffer,buffer,strlen(buffer));

                ((Token*)currToken->next)->type = TYPE_IDENT;
                ((Token*)currToken->next)->val = (int)copy_of_buffer;

            }
        }
        if(!dummy_pervention){
            ((Token*)currToken->next)->prev = currToken;
            currToken = currToken->next;
            currToken->next = malloc(sizeof(Token));
        }

        fscanout = fscanf(fp,"%s",buffer);
    }

return firstToken;
}
#include <PArser.h>
char* keywords[] = {
"int",
"var",
"void"
};
word* parse(FILE* fp)
{
    //create the string buffer
    char *buffer=malloc(1024);
    int buflen = 1024;
    int fscanout = fscanf(fp,"%s",buffer);
    word* currword = malloc(sizeof(word));
    while(fscanout != -1){
        currword->next = malloc(sizeof(word));

        for (int i = 0; i < 3; i++)
        {
            if(strcmp(keywords[i],buffer)){
                currword->type = 0;
                currword->val = i;
                printf("%i ",i);
                break;
            }
            
        }

        ((word*)currword->next)->prev = currword;
        currword = currword->next;


        

        fscanout = fscanf(fp,"%s",buffer);
    }

}
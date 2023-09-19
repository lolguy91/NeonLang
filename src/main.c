#include <stdio.h>
#include <Tokenizer.h>


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
	
	
	Token* parsed = (Token*) tokenize(fp);
	while (parsed->next != 0){
		if(parsed->type == TYPE_KEYWORD){
			printf(" %s - %s\n",names[parsed->type],keyTokens[parsed->val]);	
		//}else if(parsed->type == TYPE_IDENT){
		//	printf(" %s - %s\n",names[parsed->type],*((char**)&parsed->val));	
		}else{
			printf(" %s - %i\n",names[parsed->type],parsed->val);	
		}
		parsed = parsed->next;
	}
	printf("-%i--%i--\n",parsed->type,parsed->val);	

	//close the file
	fclose(fp);
	return 0;
}

#include <stdio.h>
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

//create the string buffer
char *buffer=malloc(sizeof(char)*1024);
int buflen = 1024;

//read the file
fgets(buffer,buflen,fp);

//print the string buffer
printf("%s\n",buffer);

//close the file
fclose(fp);
return 0;

//free the buffer

//create an ASM file to put the compiled code in
fp = fopen(strcat(argv[1],".asm"),"w+");

//write the code to the file
fputs(buffer,fp);

//close the file
fclose(fp);

//free the buffer
free(buffer);

}
#include <stdio.h>
#include <PArser.h>


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

word* parsed = (word*) parse(fp);

//close the file
fclose(fp);
return 0;
}
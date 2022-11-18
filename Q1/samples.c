#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    FILE *textfile;
    char *text;
    long numbytes;

    //abrir o txt
    textfile =fopen("quote.txt", "r");
    if(textfile == NULL)
        return 1;

    //arranjar comprimento do txt
    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);

    //alocar memoria para o comprimento do ficheiro
    text = (char*)calloc(numbytes, sizeof(char));
    if (text == NULL)
        return 1;

    //ler o conteudo do txt e fechar //string texto c conteudo do ficheiro
    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);
}
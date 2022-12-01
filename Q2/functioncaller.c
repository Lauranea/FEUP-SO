#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t pid = getpid(); //O pid é necessário para que o utilizador saiba que processo executa cada função
    printf("[pid%d] converting %s ...\n", pid, argv[1]); //Informa o utilizador do processo e do ficheiro que este converte
    char* name;
    name = strtok(argv[1], "."); //Cortar o nome do ficheiro de forma a poder passa-lo como .txt e .epub
    fflush(stdout);
    char systemcaller[20 + strlen(name) * 2]; //Cria e define o tamanho do system caller
    sprintf(systemcaller, "pandoc %s.txt -o %s.epub", name, name); //Modifica o system caller para este ter o formato pandoc nome.txt -o nome.epub
    system(systemcaller); //Finalmente, dá a system call para que o pandoc converta o ficheiro .txt para .epub
    
    return 0;
}

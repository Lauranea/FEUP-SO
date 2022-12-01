#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

char* pipename_before;
char* pipename_after;

void sig_end(int a)
{
    unlink(pipename_before); //Fecha a pipe pipename_before
    exit(0); //Termina o processo
}



int main(int argc, char* argv[])
{
    signal(SIGINT, sig_end); //Caso o utilizador faça ctrl + c, a função sig_end será chamada
    int fd;
    pipename_before = (char*) malloc(6 + strlen(argv[2]) * 2 * sizeof(char)); //Define o tamanho da pipename_before
    pipename_after = (char*) malloc(6 + strlen(argv[2]) * 2 * sizeof(char)); //Define o tamanho da pipename_after
    if(atoi(argv[1]) == 1) //Executa caso seja o processo nº1
    {
        fd = open("pipe1to2", O_WRONLY); //Abre a primeira pipe para write only
        int x = 0;
        if(write(fd, &x, sizeof(int)) == -1) //Caso não consiga abrir, informa o utilizador e termina o processo
        {
            printf("Process one failed to write %d", 0);
            return 0;
        }
        close(fd); //Fecha a primeira pipe
        //Define o nome das pipes que irá utilizar
        sprintf(pipename_after,"pipe%ito%i", 1, 2);
        sprintf(pipename_before,"pipe%ito%i", atoi(argv[2]), 1);
    }
    else if(atoi(argv[1]) == atoi(argv[2]))
    {
        //Define o nome das pipes que irá utilizar, sendo que a pipename_after é da forma pipento1
        sprintf(pipename_after,"pipe%ito%i", atoi(argv[2]), 1);
        sprintf(pipename_before,"pipe%ito%i", atoi(argv[2]) - 1, atoi(argv[2]));
    }
    else
    {
        //Define o nome das pipes que irá utilizar
        sprintf(pipename_after,"pipe%ito%i", atoi(argv[1]), atoi(argv[1])+1);
        sprintf(pipename_before,"pipe%ito%i", atoi(argv[1]) - 1, atoi(argv[1]));
    }
    int i;
    srandom(atoi(argv[1]) + time(0)); //Define a seed utilizando o nº do processo e o time(0)
    float random;
    while(true) //Cria um loop infinito
    {
        fd = open(pipename_before, O_RDONLY); //Abre a pipe anterior para read only
        if(read(fd, &i, sizeof(int)) == -1) //Caso não consiga abrir, informa o utilizador e acaba a execução
        {
            printf("Process %d couldn't read from pipe %s\n", atoi(argv[1]), pipename_before);
            return 0;
        }
        close(fd); //Fecha a pipe anterior
        i++; //incrementa o token
        random = (float) rand() / RAND_MAX;
        if(random <= atof(argv[3])) //Probabilidade
        {
            printf("[p%d] lock on token (val = %d)\n", atoi(argv[1]), i); //Informa o utilizador de que o token foi locked, o seu valor, e o processo que lhe deu lock
            sleep(atof(argv[4])); //Dá lock ao token
            printf("[p%d] unlock token\n", atoi(argv[1])); //Informa o utilizador de que o token foi unlocked
        }
        fd = open(pipename_after, O_WRONLY); //Abre a pipe seguinte para write only
        if(write(fd, &i, sizeof(int)) == -1) //Caso não consiga abrir, informa o utilizador e acaba a execução
        {
            printf("Process %d couldn't write %d into pipe %s\n", atoi(argv[1]), i, pipename_after);
            return 0;
        }
        close(fd); //Fecha a pipe
    }
}
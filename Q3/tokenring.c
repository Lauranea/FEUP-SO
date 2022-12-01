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

int main(int argc, char* argv[])
{
    //Verifica se o número de argumentos dado está correto
    if(argc < 4)
    {
        printf("Not enough arguments (3 arguments needed)\n");
        return 0;
    }
    if(argc > 4)
    {
        printf("Too many arguments (3 arguments needed)\n");
        return 0;
    }
    char pipename[6 + strlen(argv[1]) * 2]; //Cria e define o tamanho necessario para criar as pipes
    int i = 1;
    while(i < atoi(argv[1]))
    {
        sprintf(pipename,"pipe%ito%i", i, i+1); //Define o nome da pipe ex: pipe1to2, pipe2to3
        if(mkfifo(pipename, 0777) == -1) //Cria a pipe com mkfifo e caso este de erro, informa o utilizador e para a execução
        {
            printf("Error creating %s", pipename);
            return 0;
        }
        i++;
    }
    sprintf(pipename,"pipe%ito%i", i, 1); //Define o nome da ultima pipe que vai do ultimo para o primeiro: pipento1
    if(mkfifo(pipename, 0777) == -1) //Cria a ultima pipe utilizando mkfifo e informa o utilizador caso haja algum erro, terminando tambem a execução
    {
        printf("Error creating %s", pipename);
        return 0;
    }
    i = 1;
    char c[strlen(argv[1])];
    while(i <= atoi(argv[1]))
    {
        int id = fork(); //Cria n child processes
        if(id == 0) //Caso seja um child process, este irá executar o process, tomando os mesmos argumentos que o parent recebeu mais o seu numero
        {
            sprintf(c, "%d", i); //Passa o int para char* de forma a que este seja passado como argumento para o process, o c é o número/identidade do processo
            execlp("./process", "./process", c, argv[1], argv[2], argv[3], NULL);
            printf("Process %d failed to exec\n", i);
            exit(0);
        }
        else
        {
            i++;
        }
    }
    i = 0;
    while(i < atoi(argv[1])) //Enquanto os child process não terminarem, o parent process também não chega ao fim da sua execução
    {
<<<<<<< Updated upstream
        wait(NULL);
        printf("killed process %d", i);
=======
        wait();
>>>>>>> Stashed changes
        i++;
    }
    return 0;
}
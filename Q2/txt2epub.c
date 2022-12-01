#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    //Verificar se foram dados argumentos suficientes
    if(argc < 2)
    {
        printf("Not enough arguments\n");
        return 0;
    }
    int z = 1;
    int max = 0;
    int systemcallersize = 13;
    //Definir o tamanho que o array de chars systemcaller vai ter
    while(z < argc)
    {
        systemcallersize += (strlen(argv[z]) + 2);
        if(strlen(argv[z]) > max)
        {
            max = strlen(argv[z]);
        }
        z++;
    }
    int b = 1;
    char systemcaller[systemcallersize];
    //preparar o system caller, o sistem caller é o que vai dar zip aos ficheiros .epub
    strcpy(systemcaller, "zip -r ebooks");
    char name[max+1];
    while(b < argc)
    {
        int id = fork(); //Criar um novo processo
        if(id == 0) //Caso o processo seja um child process, este irá executar o functioncaller, tomando um dos finheiros .txt como argumento
        {
            execlp("./functioncaller", "./functioncaller",argv[b], NULL);
            exit(0);
        }
        else
        {
            //Adiciona o nome do ficheiro que foi dado ao processo anteriormente criado, para poder dar zip do ficheiro epub criado pelo processo child quando este chegar ao fim da sua execução
            strcpy(name, argv[b]);
            strtok(name, ".");
            strcat(name, ".epub");
            strcat(systemcaller, " ");
            strcat(systemcaller, name);
            b++;
        }
    }
    int i = 1;
    //Enquanto os child processes estiverem a executar o parent não continua, se não, pode causar problemas na criação do zip e na remoção de ficheiros
    while(i < argc)
    {
        wait(NULL);
        i++;
    }
    system(systemcaller);
    
    
    i = 1;
    char systemcaller2[max + 4];
    while(i < argc)
    {
        //O ultimo passo da execução é remover os ficheiro to tipo epub, uma vez que estes agora estão dentro de ebooks.zip
        strcpy(name, argv[i]);
        strtok(name, ".");
        strcpy(systemcaller2, "rm ");
        strcat(systemcaller2, name);
        strcat(systemcaller2, ".epub");
        system(systemcaller2);
        i++;
    }
    //int err = errno;
    //printf("%i\n", err);
    return 0;
}
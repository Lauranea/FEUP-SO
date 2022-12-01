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
    if(argc < 2)
    {
        printf("Not enough arguments\n");
        return 0;
    }
    int z = 1;
    int max = 0;
    int systemcallersize = 13;
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
    strcpy(systemcaller, "zip -r ebooks");
    char name[max+1];
    while(b < argc)
    {
        int id = fork();
        if(id == 0)
        {
            execlp("./functioncaller", "./functioncaller",argv[b], NULL);
            exit(0);
        }
        else
        {
            strcpy(name, argv[b]);
            strtok(name, ".");
            strcat(name, ".epub");
            strcat(systemcaller, " ");
            strcat(systemcaller, name);
            b++;
        }
    }
    //printf("\n\n\n%s,%d,%i\n\n\n", systemcaller, systemcallersize, strlen(systemcaller));
    int i = 1;
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
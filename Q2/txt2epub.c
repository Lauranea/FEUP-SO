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
    
    
    int b = 1;
    char systemcaller[1];
    strcpy(systemcaller, "zip -r ebooks ");
    /*
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
            char* name;
            name = strtok(argv[1], ".");
            strcat(systemcaller, name);
            strcar(systemcaller, " ");
            b++;
        }
    }
    int i = 1;
    while(i < argc)
    {
        wait();
        i++;
    }
    */
    //int err = errno;
    //printf("%i\n", err);
    return 0;
}
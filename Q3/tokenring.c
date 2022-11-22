#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char* argv[])
{
    int i = 0;
    int fd;
    int passed = 0;
    while(i < atoi(argv[1]))
    { 
        //a minha sanidade mental foi posta em questão a fazer estas duas linhas de código
        char pipename[1024];
        sprintf(pipename,"pipe%ito%i", i, i+1);

        
        mkfifo(pipename, 0666) //so porque apareceu assim no tutorial


        // int id = fork();
        // if(id != 0);
        // else
        // {
        //     execlp();
        // }
        // i++;
    }
    // i = 0;
    // while(i < argv[1])
    // {
    //     wait();
    //     i++;
    // }
    return 0;
}
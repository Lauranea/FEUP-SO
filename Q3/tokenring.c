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
    char pipename[6 + strlen(argv[1]) * 2];
    int i = 1;
    while(i < atoi(argv[1]))
    {
        sprintf(pipename,"pipe%ito%i", i, i+1);
        if(mkfifo(pipename, 0777) == -1)
        {
            printf("Error creating %s", pipename);
            return 0;
        }
        i++;
    }
    sprintf(pipename,"pipe%ito%i", i, 1);
    if(mkfifo(pipename, 0777) == -1)
    {
        printf("Error creating %s", pipename);
        return 0;
    }
    i = 1;
    char c[strlen(argv[1])];
    while(i <= atoi(argv[1]))
    {
        int id = fork();
        if(id == 0)
        {
            sprintf(c, "%d", i);
            //printf("Process %d created\n", i);
            execlp("./process", "./process", c, argv[1], argv[2], argv[3], NULL);
            printf("Process %d failed to exec\n", i);
            exit(0);
        }
        else
        {
            i++;
        }
    }
    return 0;
}
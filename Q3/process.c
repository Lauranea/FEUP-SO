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
    unlink(pipename_before);
    exit(0);
}



int main(int argc, char* argv[])
{
    signal(SIGINT, sig_end);
    //printf("Process nº%d started\n", atoi(argv[1]));
    //printf("Values = %d, %d, %f, %d\n", atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atoi(argv[4]));
    int fd;
    pipename_before = (char*) malloc(6 + strlen(argv[2]) * 2 * sizeof(char));
    pipename_after = (char*) malloc(6 + strlen(argv[2]) * 2 * sizeof(char));
    if(atoi(argv[1]) == 1)
    {
        fd = open("pipe1to2", O_WRONLY);
        int x = 0;
        if(write(fd, &x, sizeof(int)) == -1)
        {
            printf("Process one failed to write %d", 0);
        }
        close(fd);
        sprintf(pipename_after,"pipe%ito%i", 1, 2);
        sprintf(pipename_before,"pipe%ito%i", atoi(argv[2]), 1);
    }
    else if(atoi(argv[1]) == atoi(argv[2]))
    {
        sprintf(pipename_after,"pipe%ito%i", atoi(argv[2]), 1);
        sprintf(pipename_before,"pipe%ito%i", atoi(argv[2]) - 1, atoi(argv[2]));
    }
    else
    {
        sprintf(pipename_after,"pipe%ito%i", atoi(argv[1]), atoi(argv[1])+1);
        sprintf(pipename_before,"pipe%ito%i", atoi(argv[1]) - 1, atoi(argv[1]));
    }
    //printf("Process %d defined the pipes\n", atoi(argv[1]));
    int i;
    srandom(atoi(argv[1]) + time(0));
    float random;
    while(true)
    {
        //printf("process %d\n", atoi(argv[1]));
        fd = open(pipename_before, O_RDONLY);
        if(read(fd, &i, sizeof(int)) == -1)
        {
            printf("Process %d couldn't read from pipe %s\n", atoi(argv[1]), pipename_before);
            return 0;
        }
        close(fd);
        //printf("Process %d recieved %d from %s\n", atoi(argv[1]), i, pipename_before);
        i++;
        random = (float) rand() / RAND_MAX;
        if(random <= atof(argv[3]))
        {
            printf("[p%d] lock on token (val = %d)\n", atoi(argv[1]), i);
            sleep(atof(argv[4]));
            printf("[p%d] unlock token\n", atoi(argv[1]));
        }
        fd = open(pipename_after, O_WRONLY);
        if(write(fd, &i, sizeof(int)) == -1)
        {
            printf("Process %d couldn't write %d into pipe %s\n", atoi(argv[1]), i, pipename_after);
            return 0;
        }
        close(fd);
        //printf("Process %d wrote down %d into %s\n", atoi(argv[1]), i, pipename_after);
    }
}
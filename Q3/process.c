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
    int fd;
    char pipename_before[6 + strlen(argv[2]) * 2];
    char pipename_after[6 + strlen(argv[2]) * 2];
    if(atoi(argv[1]) == 1)
    {
        fd = open("pipe1to2", O_WRONLY);
        if(write(fd, 0, sizeof(int)) == -1)
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
    while(true)
    {
        fd = open(pipename_before, O_RDONLY);
        int i;
        if(read(fd, &i, sizeof(int)) == -1)
        {
            printf("Process %d couldn't read from pipe %s", atoi(argv[1]), pipename_before);
            return 0;
        }
        close(fd);
        i++;
        printf("Process nº%d wrote down the number %i", atoi(argv[1]), i);
        fd = open(pipename_after, O_WRONLY);
        if(write(fd, &i, sizeof(int)) == -1)
        {
            printf("Process %d couldn't write %i into pipe %s", atoi(argv[1]), i, pipename_after);
            return 0;
        }
        close(fd);
    }
}
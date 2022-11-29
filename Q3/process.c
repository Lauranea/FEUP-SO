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
    //printf("Process nº%d started\n", atoi(argv[1]));
    //printf("Values = %d, %d, %f, %d\n", atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atoi(argv[4]));
    int fd;
    char pipename_before[6 + strlen(argv[2]) * 2];
    char pipename_after[6 + strlen(argv[2]) * 2];
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
    int i;
    srand(atoi(argv[1]) + time(0));
    float random;
    while(true)
    {
        fd = open(pipename_before, O_RDONLY);
        if(read(fd, &i, sizeof(int)) == -1)
        {
            printf("Process %d couldn't read from pipe %s\n", atoi(argv[1]), pipename_before);
            return 0;
        }
        close(fd);
        //printf("Process %d recieved %d from %s\n", atoi(argv[1]), i, pipename_before);
        i++;
        random = (float)rand() / RAND_MAX;
        if(random <= atof(argv[3]))
        {
            sleep(atof(argv[4]));
            printf("Process nº%d lockeded for %d seconds at value = %d\n", atoi(argv[1]), atoi(argv[4]), i);
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
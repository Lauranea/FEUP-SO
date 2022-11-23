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

#define BUFFER_SIZE 1024


int main(int argc, char* argv[])
{
    int fd;
    int passed = 0;
    int i = 1;

    while(i <= atoi(argv[1]))
    { 
        char pipename[BUFFER_SIZE];

        if(i == atoi(argv[i])){
            sprintf(pipename,"pipe%ito%i", i, 1);
            i = 1;
        }
        else {
            sprintf(pipename,"pipe%ito%i", i, i+1);
            i++;
        }


        char passed_str[BUFFER_SIZE];
        sprintf(passed_str,"%i",passed);

        mkfifo(pipename, 0666); //criar named pipe

        fd = open(pipename, O_WRONLY); //write only

        write(fd,passed_str,strlen(passed_str));
        close(fd);

        passed++;
    }

    return 0;
}
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
    int current_time = time(0);

    while(i <= atoi(argv[1]))
    { 
        srand(current_time);
        current_time++;
        double chance = rand() % 10000; //nao tenho a certeza da precisao, entao fica 0.01%
        printf("\n%f\t%f", chance,atof(argv[2]) * 10000);
        if(chance <= atof(argv[2]) * 10000){
            printf("\n[p%i] lock on token ( val = %i)",i,passed);
            sleep(atof(argv[3]));
            printf("\n[p%i] unlock token",i);
        }
        char pipename[BUFFER_SIZE];

        if(i == atoi(argv[1])){
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

        unlink(pipename);
        passed++;
    }

    return 0;
}
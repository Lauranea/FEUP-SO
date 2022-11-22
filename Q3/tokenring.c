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
    while(i < argv[1])
    {
        int id = fork();
        if(id != 0);
        else
        {
            execlp();
        }
        i++;
    }
    i = 0;
    while(i < argv[1])
    {
        wait();
        i++;
    }
    return 0;
}
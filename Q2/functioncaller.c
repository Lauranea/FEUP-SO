#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t pid = getpid();
    printf("[pid%d] converting %s ...\n", pid, argv[1]);
    char* name;
    name = strtok(argv[1], ".");
    fflush(stdout);
    char systemcaller[20 + strlen(name) * 2];
    sprintf(systemcaller, "pandoc %s.txt -o %s.epub", name, name);
    system(systemcaller);
    
    return 0;
}

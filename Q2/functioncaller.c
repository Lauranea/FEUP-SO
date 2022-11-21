#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


void functioncall(char a[])
{

}


int main(int argc, char *argv[])
{
    
    char* name;
    name = strtok(argv[1], ".");
    printf("\n\n\n Now running Pandoc : %s\n\n\n", name);
    fflush(stdout);
    char systemcaller[20 + strlen(name) * 2];
    strcpy(systemcaller, "pandoc ");
    strcat(systemcaller, name);
    strcat(systemcaller, ".txt -o ");
    strcat(systemcaller, name);
    strcat(systemcaller, ".epub");
    system(systemcaller);
    
    
    return 0;
}

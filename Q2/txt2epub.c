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
    int b = 1;
    while(b < argc)
    {
        char name[strlen(argv[b]) - 4];
        strncpy(name, argv[b], strlen(argv[b]) - 4);
        char systemcaller[20 + strlen(name) * 2];
        printf("%s\n", name);
        strcpy(systemcaller, "pandoc ");
        strcat(systemcaller, name);
        strcat(systemcaller, ".txt -o ");
        strcat(systemcaller, name);
        strcat(systemcaller, ".epub");
        printf("%s\n", systemcaller);
        system(systemcaller);
        b++;
    }
    while()
    
    return 0;
}
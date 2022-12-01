#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// nome prog; a.txt; n ; m;
int main(int argc, char *argv[])
{
    FILE *textfile;
    char *text;
    char c;

    long numbytes;
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    char frag[m];
    int count = 0;
    srand(0);

    textfile = fopen(argv[1], "r");
    if (textfile == NULL)
        return 1;

    for(c = getc(textfile); c!= EOF; c = getc(textfile)) count++;

    int num = rand() % (count - m + 1);

    while(n > 0)
    {
        putc('<', stdout);
        int num = rand() % (count - m + 1);

        fseek(textfile, num, SEEK_SET);
        for(int i = 0; i < m; i++)
        {
            char c = getc(textfile);
            if(c < 32)
            {
                i--;
                continue;
            }
            putc(c, stdout);
        }
        printf(">\n");
        n--;
    }
}
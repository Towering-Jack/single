#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char * const p = (char*)malloc(12);
    char *ptr = p;
    *ptr++ = '9'; 
    fgets(ptr, 10, stdin);
    // fputs(p, stdout);
    // putchar('\n');
    
    int i, j;
    i = 1;
    j = 0;
    int next[10] = {0};
    while (i < (p[0] - '0'))
    {
        if (j == 0 || p[i] == p[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }

    for (i = 1; i < 10; i++)
        printf("%2d", next[i]);

    return 0;
}
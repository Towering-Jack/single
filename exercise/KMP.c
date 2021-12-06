#include <stdio.h>
#include <string.h>

#define MAXS 1000001
#define MAXT 100001

void get_next(char *T, int *next)
{
    int i, j;

    i = 1;
    j = 0;
    next[1] = 0;
    while (i < strlen(T) - 1)
    {
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

void Index_KMP(char *S, char *T, int pos)
{
    int i, j;

    i = pos;
    j = 0;
    int next[MAXT];
    get_next(T - 1, next);

    while (i <= strlen(S) - 1 && j <= strlen(T) - 1)
    {
        if (j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }

    if (j > strlen(T))
        fputs(S + i - strlen(S) - 1, stdout);
    else
        printf("Not Found");
}

int main()
{
    char S[MAXS];
    int i, N;

    fgets(S, MAXS, stdin);
    scanf("%d", &N);
    getchar();

    for (i = 0; i < N; i++)
    {
        char T[MAXT];
        fgets(T, MAXT, stdin);
        Index_KMP(S, T, 0);
        if (i != N - 1)
            printf("\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Position;
#define NotFound -1
#define MaxSSize 1000005
#define MaxPSize 100005

void get_next(char *pattern, int *next)
{
    Position i, j;
    int m;

    i = 1;
    j = 0;
    next[1] = 0;
    m = strlen(pattern) - 1;
    while (i < m)
    {
        if (j == 0 || pattern[i] == pattern[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

Position KMP(char *string, char *pattern)
{
    int n, m;
    Position i, j, *next;

    n = strlen(string) - 1;
    m = strlen(pattern) - 1;
    if (n < m)
        return NotFound;

    next = (Position *)malloc(sizeof(Position) * (m + 1));
    get_next(pattern, next);

    i = j = 1;
    while (i <= n && j <= m)
    {
        if (j == 0 || string[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }

    if (j > m)
        return i - m;
    else
        return NotFound;
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    int i;

    i = 0;
    st[0] = '0';
    ret_val = fgets(st + 1, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;

        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}

int main()
{
    char string[MaxSSize], pattern[MaxPSize];
    int i, N;
    Position p;

    s_gets(string, MaxSSize);
    scanf("%d\n", &N);
    for (i = 0; i < N; i++)
    {
        s_gets(pattern, MaxPSize);
        p = KMP(string, pattern);
        if (p == NotFound)
            printf("Not Found\n");
        else
            puts(string + p);
    }
    return 0;
}
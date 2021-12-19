#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NotFound -1
#define MaxSSize 1000005
#define MaxPSize 100005
typedef int Position;

//* 计算match数组
void BuildMatch(char *pattern, int *match)
{
    Position i, j;
    int m;

    m = strlen(pattern);
    match[0] = -1;

    for (j = 1; j < m; j++)
    {
        i = match[j - 1];

        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
            i = match[i];

        if (pattern[i + 1] == pattern[j])
            match[j] = i + 1;
        else
            match[j] = -1;
    }
}

//* KMP算法实现
Position KMP(char *string, char *pattern)
{
    int n, m;
    Position s, p, *match;

    n = strlen(string);
    m = strlen(pattern);
    if (n < m)
        return NotFound;

    match = (Position *)malloc(sizeof(Position) * m);
    BuildMatch(pattern, match);

    s = p = 0;
    while (s < n && p < m)
    {
        if (string[s] == pattern[p])
        {
            s++;
            p++;
        }
        else if (p > 0)
            p = match[p - 1] + 1;
        else
            s++;
    }

    return (p == m) ? (s - m) : NotFound;
}

//* 读取字符串（C Primer Plus方法）
char *s_gets(char *st, int n)
{
    char *ret_val;
    int i;

    i = 0;
    ret_val = fgets(st, n, stdin);
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

//* 测试函数
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
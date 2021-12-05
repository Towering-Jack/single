#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int eachpro[6];
    int total;
    int perfect;
} Score;

int N, K, M;
int fullmark[6];

void Read(Score *sro)
{
    int i, j, id, num, mark, flag;

    for (i = 0; i < N; ++i)
    {
        for (j = 1; j <= K; ++j)
            sro[i].eachpro[j] = -2; //表示未曾回答,-1为通过
        sro[i].total = 0;
        sro[i].perfect = 0;
    }

    for (i = 0; i < M; ++i)
    {
        scanf("%d %d %d", &id, &num, &mark);
        if (sro[id - 1].eachpro[num] < mark)
            sro[id - 1].eachpro[num] = mark;
    }

    for (i = 0; i < N; ++i)
    {
        flag = 1;

        for (j = 1; j <= K; ++j)
        {
            if (sro[i].eachpro[j] >= 0)
            {
                flag = 0;
                sro[i].total += sro[i].eachpro[j];
                if (sro[i].eachpro[j] == fullmark[j])
                    sro[i].perfect++;
            }
        }

        if (flag)
            sro[i].total = -1;
    }
}

int Compare(Score *sro, int a, int b)
{
    if (sro[a].total > sro[b].total)
        return 1;
    else if (sro[a].total < sro[b].total)
        return 0;
    else
    {
        if (sro[a].perfect > sro[b].perfect)
            return 1;
        else if (sro[a].perfect < sro[b].perfect)
            return 0;
        else
        {
            if (a < b)
                return 1;
            else
                return 0;
        }
    }
}

void ShellSort(Score *sro, int *index)
{
    int i, j, k, d, t;

    for (k = log10(N + 1) / log10(2); k > 0; --k)
    {
        d = pow(2, k) - 1;
        for (i = d; i < N; ++i)
        {
            t = index[i];
            for (j = i; j >= d && Compare(sro, t, index[j - d]); j -= d)
                index[j] = index[j - d];
            index[j] = t;
        }
    }
}

int main()
{
    scanf("%d %d %d", &N, &K, &M);

    int i;
    for (i = 1; i <= K; ++i)
        scanf("%d", &fullmark[i]);

    Score *sro = (Score *)malloc(N * sizeof(Score));
    Read(sro);

    int *index = (int *)malloc(N * sizeof(int));
    for (i = 0; i < N; ++i)
        index[i] = i;
    ShellSort(sro, index);

    int cur, j;
    for (i = 0; i < N; ++i)
    { //输出结果
        if (sro[index[i]].total == -1)
            break;
        if (!i || (i > 0 && sro[index[i]].total != sro[index[i - 1]].total))
        { //与前一用户的总分不同，则按实际排名输出
            printf("%d ", i + 1);
            cur = i + 1; //最新用户排名
        }
        else
            printf("%d ", cur); //与前一用户总分相同，则按前一用户的排名输出

        printf("%05d ", index[i] + 1);
        printf("%d ", sro[index[i]].total);

        for (j = 1; j <= K; ++j)
        {
            if (sro[index[i]].eachpro[j] == -2) //未被回答过
                printf("-");
            else if (sro[index[i]].eachpro[j] == -1) //未通过编译
                printf("0");
            else
                printf("%d", sro[index[i]].eachpro[j]);

            if (j != K)
                printf(" ");
            else
                printf("\n");
        }
    }
    
    return 0;
}
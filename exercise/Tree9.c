#include <stdio.h>
#include <stdlib.h>
#include <string.h> //& gets()函数头文件

#define MAXSIZE 66
typedef struct LNode *HfmTree;
struct LNode
{
    char data;
    int frequency;
    int parent;
};

void FindMin_2(HfmTree T, int n, int *min1, int *min2);
int GetWeight(HfmTree T, char data, int n);

int main()
{
    int i, N, M, WPL = 0;
    scanf("%d", &N);
    HfmTree T = (HfmTree)malloc(((2 * N) - 1) * sizeof(struct LNode));
    for (i = 0; i < N; i++)
    {
        getchar();
        scanf("%c %d", &T[i].data, &T[i].frequency);
        T[i].parent = -1;
    }
    int min1, min2;
    for (i = N; i < 2 * N - 1; i++)
    {
        FindMin_2(T, i, &min1, &min2);
        T[i].frequency = T[min1].frequency + T[min2].frequency;
        T[min1].parent = i;
        T[min2].parent = i;
        WPL += T[i].frequency; //&求出题目的WPL值
        T[i].parent = -1;
    }

    scanf("%d\n", &M);
    while (M--)
    {
        int sum = 0; //& sum为学生的WPL值
        char work[MAXSIZE][MAXSIZE];
        for (i = 0; i < N; i++)
        {
            gets(work[i]);
            work[i][1] = strlen(work[i]) - 2;
            sum += GetWeight(T, work[i][0], N) * work[i][1];
        }
        if (sum != WPL)
            printf("No");
        else
        { //& 判断前缀码是否匹配
            int flag = 0;
            int j, k, len, len2;
            for (i = 0; i < N; i++)
            {
                len = work[i][1];
                for (j = 0; j < N; j++)
                {
                    if (i == j)
                        continue;
                    len2 = work[j][1];
                    if (len <= len2)
                    {
                        for (k = 2; k < 2 + len; k++)
                        {
                            if (work[i][k] != work[j][k])
                                break;
                        }
                        if (k == 2 + len)
                        {
                            flag = 1;
                            break;
                        }
                    }
                }
                if (flag)
                    break;
            }
            if (flag)
                printf("No");
            else
                printf("Yes");
        }
        if (M != 0)
            printf("\n");
    }
    return 0;
}

void FindMin_2(HfmTree T, int n, int *min1, int *min2)
{
    int i, flag = 0;
    for (i = 0; i < n; i++)
    {
        if (!flag && T[i].parent == -1)
        {
            *min1 = i;
            flag = 1;
        }
        else if (flag && T[i].parent == -1)
        {
            *min2 = i;
            break;
        }
    }
    if (T[*min1].frequency > T[*min2].frequency)
    {
        int t = *min1;
        *min1 = *min2;
        *min2 = t;
    }
    for (i++; i < n; i++)
    {
        if (T[i].parent != -1 || i == *min1 || i == *min2)
            continue;
        else if (T[i].frequency < T[*min1].frequency)
        {
            *min2 = *min1;
            *min1 = i;
        }
        else if (T[i].frequency < T[*min2].frequency)
            *min2 = i;
    }
}

int GetWeight(HfmTree T, char data, int n)
{
    for (int i = 0; i < n; i++)
        if (T[i].data == data)
            return T[i].frequency;
    return 0;
}
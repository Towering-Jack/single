#include <stdio.h>

#define MAXSIZE 100005

int FindPos(int arr[], int K, int i);
int *CalMax(int arr[], int K, int i);

int main()
{
    int K, arr[MAXSIZE];
    int last_i, pos_i, max;
    int *res_p;

    scanf("%d", &K);
    for (int i = 0; i < K; i++)
        scanf("%d", &arr[i]);

    last_i = 0;
    pos_i = FindPos(arr, K, last_i);
    if (pos_i == -1)
        printf("0");
    else
    {
        res_p = CalMax(arr, K, pos_i);
        last_i = res_p[0];
        max = res_p[1];

        while (last_i < K - 1)
        {
            pos_i = FindPos(arr, K, last_i);
            if (pos_i != -1)
            {
                res_p = CalMax(arr, K, pos_i);
                last_i = res_p[0];
                if (res_p[1] > max)
                    max = res_p[1];
            }
            else
                break;
        }

        printf("%d", max);
    }

    return 0;
}

int FindPos(int arr[], int K, int i)
{
    while (i < K)
    {
        if (arr[i] > 0)
            return i;

        i++;
    }
    return -1;
}

int *CalMax(int arr[], int K, int i)
{
    int sum_now, sum;

    sum_now = arr[i];
    sum = sum_now;
    while (sum_now > 0 && i < K - 1)
    {
        sum_now += arr[++i];
        if (sum_now > sum)
            sum = sum_now;
    }

    static int res[2];
    res[0] = i;
    res[1] = sum;
    return res;
}
#include <stdio.h>
#include <math.h>

int IsTheNumber(const int N);

int main()
{
    int n1, n2, i, cnt;

    scanf("%d %d", &n1, &n2);
    cnt = 0;
    for (i = n1; i <= n2; i++)
    {
        if (IsTheNumber(i))
            cnt++;
    }
    printf("cnt = %d\n", cnt);

    return 0;
}

/* 你的代码将被嵌在这里 */
int IsTheNumber(const int N)
{
    double result;
    int arr[10];
    int n = N;
    int i = 0;
    do
    {
        arr[i++] = n % 10;
        n /= 10;
    } while (n);
    for (int j = 0; j < i; j++)
    {
        for (int k = j + 1; k < i; k++)
        {
            if (arr[k] == arr[j])
                goto here;
        }
    }
    return 0;
here:
    result = sqrt(N);
    if (result - (int)result == 0)
        return 1;
    return 0;
}
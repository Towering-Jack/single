#include <stdio.h>

int Count_Digit(const int N, const int D);

int main()
{
    int N, D;

    scanf("%d %d", &N, &D);
    printf("%d\n", Count_Digit(N, D));
    return 0;
}

/* 你的代码将被嵌在这里 */
int Count_Digit(const int N, const int D)
{
    int arr[10];
    int n;
    if (N > 0)
        n = N;
    else
        n = -N;
    int i = 0;
    do
    {
        arr[i++] = n % 10;
        n /= 10;
    } while (n);
    int cnt = 0;
    for (int j = 0; j < i; j++)
    {
        if (arr[j] == D)
            cnt++;
    }
    return cnt;
}
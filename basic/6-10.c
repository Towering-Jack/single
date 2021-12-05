#include <stdio.h>

void Print_Factorial(const int N);

int main()
{
    int N;

    scanf("%d", &N);
    Print_Factorial(N);
    return 0;
}

/* 你的代码将被嵌在这里 */
void Print_Factorial(const int N)
{
    int num[3001] = {0};
    int ans = 1;
    int tmp = 0;
    int k = 0;
    int carry = 0;
    if (N < 0)
        printf("Invalid input\n");
    else if (N == 0)
        printf("1\n");
    else if (N > 0 && N < 12)
    {
        for (int i = 1; i <= N; i++)
            ans = ans * i;
        printf("%d\n", ans);
    }
    else
    {
        num[0] = 1;
        for (int i = 2; i <= N; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                tmp = num[j] * i + carry;
                num[j] = tmp % 10;
                carry = tmp / 10;
            }
            while (carry)
            {
                num[++k] = carry % 10;
                carry = carry / 10;
            }
        }
        for (int i = k; i >= 0; i--)
            printf("%d", num[i]);
        printf("\n");
    }
}
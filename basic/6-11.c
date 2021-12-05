#include <stdio.h>

#define MAXN 10
typedef float ElementType;

ElementType Median(ElementType A[], int N);

int main()
{
    ElementType A[MAXN];
    int N, i;

    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%f", &A[i]);
    printf("%.2f\n", Median(A, N));

    return 0;
}

/* 你的代码将被嵌在这里 */
//^希尔排序
void ShellSort(ElementType a[], int n)
{
    int i, j, dk;
    ElementType tmp;
    for (dk = n / 2; dk > 0; dk /= 2)
        for (i = dk; i < n; i++)
        {
            tmp = a[i];
            for (j = i; j >= dk; j -= dk)
                if (tmp < a[j - dk])
                    a[j] = a[j - dk];
                else
                    break;
            a[j] = tmp;
        }
}

ElementType Median(ElementType A[], int N)
{
    ShellSort(A, N);
    if (N % 2 == 1)
        return A[(N + 1) / 2 - 1];
    else
        return A[(N + 1) / 2];
}

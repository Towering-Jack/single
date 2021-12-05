#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 105
typedef int ElemType;

int JudgeArr(ElemType A[], ElemType text[], int N)
{
    int i;
    for (i = 0; i < N; i++)
        if (A[i] != text[i])
            break;
    if (i == N)
        return 1;
    return 0;
}

void PrintResule(ElemType arrData[], int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d", arrData[i]);
        if (i != N - 1)
            printf(" ");
    }
}

//^---------------插入排序---------------^//
int Insertion_Sort(ElemType A[], int N, ElemType text[])
{
    int P, i, flag;
    ElemType temp;

    flag = 0;
    for (P = 1; P < N; P++)
    {
        temp = A[P];
        for (i = P; i > 0 && A[i - 1] > temp; i--)
            A[i] = A[i - 1];
        A[i] = temp;

        if (flag)
            return flag;
        flag = JudgeArr(A, text, N);
    }
    return flag;
}
//^插入排序结束

//^---------------堆排序---------------^//
void Swap(ElemType *A, ElemType *B)
{
    ElemType temp;
    temp = *A;
    *A = *B;
    *B = temp;
}

//*将N个元素的数组中以A[p]为根的子堆调整为最大堆
void PercDown(ElemType A[], int p, int N)
{
    int parent, child;
    ElemType X;

    X = A[p];
    for (parent = p; (parent * 2 + 1) < N; parent = child)
    {
        child = parent * 2 + 1;
        if ((child != N - 1) && (A[child] < A[child + 1]))
            child++;
        if (X >= A[child])
            break;
        else
            A[parent] = A[child];
    }
    A[parent] = X;
}

void Heap_Sort(ElemType A[], int N, ElemType text[])
{
    int i, flag;

    for (i = N / 2 - 1; i >= 0; i--) //&建立最大堆
        PercDown(A, i, N);

    flag = 0;
    for (i = N - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);

        if (flag)
            return;
        flag = JudgeArr(A, text, N);
    }
}
//^堆排序结束

int main()
{
    int i, N;
    ElemType arrData1[MAXSIZE], arrData2[MAXSIZE];
    ElemType text[MAXSIZE];

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &arrData1[i]);
        arrData2[i] = arrData1[i];
    }
    for (i = 0; i < N; i++)
        scanf("%d", &text[i]);

    if (Insertion_Sort(arrData1, N, text))
    {
        printf("Insertion Sort\n");
        PrintResule(arrData1, N);
    }
    else
    {
        Heap_Sort(arrData2, N, text);
        printf("Heap Sort\n");
        PrintResule(arrData2, N);
    }

    return 0;
}
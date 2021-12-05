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

//^---------------归并排序(非递归实现)---------------^//
//*将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
void Merge1(ElemType A[], ElemType TempA[], int L, int R, int RightEnd)
{
    //&L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置
    int LeftEnd, NumElements, temp, i;

    LeftEnd = R - 1;
    temp = L;
    NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            TempA[temp++] = A[L++];
        else
            TempA[temp++] = A[R++];
    }

    //&直接复制剩下的
    while (L <= LeftEnd)
        TempA[temp++] = A[L++];
    while (R <= RightEnd)
        TempA[temp++] = A[R++];

    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TempA[RightEnd]; //&将有序的TempA[]复制回A[]
}

//*两两归并相邻有序子列, lenght为当前有序子列长度
void Merge_pass(ElemType A[], ElemType Temp[], int N, int length)
{
    int i, j;

    //&在归并完倒数第二对相邻子列后停止
    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge1(A, Temp, i, i + length, i + 2 * length - 1);

    if (i + length < N) //&归并最后一对子列
        Merge1(A, Temp, i, i + length, N - 1);
    else //&只剩下一个子列
        for (j = i; j < N; j++)
            Temp[j] = A[j];
}

void Merge_Sort2(ElemType A[], int N, ElemType text[])
{
    int length, flag;
    ElemType *Temp;

    length = 1;
    Temp = (ElemType *)malloc(N * sizeof(ElemType));
    if (Temp != NULL)
    {
        flag = 0;
        while (length < N)
        {
            Merge_pass(A, Temp, N, length);
            length *= 2;

            if (flag)
                return;
            flag = JudgeArr(A, text, N);
        }
        free(Temp);
    }
    else
        printf("空间不足！");
}
//^归并排序(非递归实现)结束

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
        Merge_Sort2(arrData2, N, text);
        printf("Merge Sort\n");
        PrintResule(arrData2, N);
    }

    return 0;
}
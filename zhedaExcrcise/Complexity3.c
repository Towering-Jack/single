/*
! 本题要求实现二分查找算法。
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;
typedef int Position;

typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last; //& 保存线性表中最后一个元素的位置
};

List ReadInput(); //& 元素从下标1开始存储
Position BinarySearch(List L, ElementType X);

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch(L, X);
    printf("%d\n", P);
    free(L);

    return 0;
}

List ReadInput()
{
    List L;
    Position i;

    L = (List)malloc(sizeof(struct LNode));
    L->Data[0] = 0;

    scanf("%d", &L->Last);
    for (i = 1; i <= L->Last; i++)
        scanf("%d", &L->Data[i]);

    return L;
}

//^ 你的代码将被嵌在这里
Position BinarySearch(List L, ElementType X)
{
    Position mid, small, big;

    if (X < L->Data[1] && X > L->Data[L->Last]) //& 如果X小于第一个元素或者大于最后一个元素
        return NotFound;
    else if (X == L->Data[1]) //& 如果X等于第一个元素
        return 1;
    else if (X == L->Data[L->Last]) //& 如果X等于最后一个元素
        return L->Last;

    mid = (L->Last + 1) / 2;
    small = 1;
    big = L->Last;
    while (big != small + 1)
    {
        if (X == L->Data[mid])
        {
            return mid;
        }
        else if (X < L->Data[mid])
        {
            big = mid;
            mid = small + (big - small) / 2;
        }
        else
        {
            small = mid;
            mid = mid + (big - small) / 2;
        }
    }

    return NotFound;
}
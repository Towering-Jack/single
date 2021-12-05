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
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
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
    L = (List)malloc(sizeof(struct LNode));
    Position i;
    L->Data[0] = 0;
    scanf("%d", &L->Last);
    for (i = 1; i <= L->Last; i++)
    {
        scanf("%d", &L->Data[i]);
    }
    return L;
}

/* 你的代码将被嵌在这里 */
Position BinarySearch(List L, ElementType X)
{
    if (X < L->Data[1] && X > L->Data[L->Last])
        return NotFound;
    else if (X == L->Data[1])
        return 1;
    else if (X == L->Data[L->Last])
        return L->Last;
    Position i = (L->Last + 1) / 2;
    Position small = 1, big = L->Last;
    while (big != small + 1)
    {
        if (X == L->Data[i])
        {
            return i;
        }
        else if (X < L->Data[i])
        {
            big = i;
            i = small + (big - small) / 2;
        }
        else
        {
            small = i;
            i = i + (big - small) / 2;
        }
    }
    return NotFound;
}
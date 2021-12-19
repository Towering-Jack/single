/*
! 本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。
! List Merge( List L1, List L2 );
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();
void Print(List L);
PtrToNode MakeEmpty();
List InsertLast(ElementType X, List PtrL);

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;

    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);

    Print(L);
    Print(L1);
    Print(L2);

    return 0;
}

List Read()
{
    List PtrL;
    ElementType data;
    int i;

    PtrL = MakeEmpty();
    scanf("%d", &PtrL->Data);
    for (i = 1; i <= PtrL->Data; i++)
    {
        scanf("%d", &data);
        PtrL = InsertLast(data, PtrL);
    }

    return PtrL;
}

void Print(List L)
{
    List p;

    p = L;
    if (p->Next == NULL)
    {
        printf("NULL\n");
        return;
    }

    while (p->Next)
    {
        p = p->Next;
        printf("%d ", p->Data);
    }
    printf("\b\n");
}

List MakeEmpty()
{
    PtrToNode Node;

    Node = (List)malloc(sizeof(struct Node));
    Node->Data = 0;
    Node->Next = NULL;
    return Node;
}

List InsertLast(ElementType X, List PtrL)
{
    PtrToNode s;
    List p;

    s = MakeEmpty();
    s->Data = X;
    s->Next = NULL;

    p = PtrL;
    while (p->Next)
        p = p->Next;
    p->Next = s;

    return PtrL;
}

//^ 你的代码将被嵌在这里
List Merge(List L1, List L2)
{
    List p1, p2, PtrL, p;

    p1 = L1->Next;
    p2 = L2->Next;

    PtrL = (List)malloc(sizeof(struct Node));
    PtrL->Data = 0;
    p = PtrL;

    while (p1 && p2)
    {
        if (p1->Data <= p2->Data)
        {
            p->Next = p1;
            p1 = p1->Next;
            L1->Data--;
        }
        else
        {
            p->Next = p2;
            p2 = p2->Next;
            L2->Data--;
        }

        p = p->Next;
        PtrL->Data++;
    }

    if (p1 == NULL)
    {
        p->Next = p2;
        PtrL->Data += L2->Data;
    }
    else
    {
        p->Next = p1;
        PtrL->Data += L1->Data;
    }

    L1->Data = L2->Data = 0;
    L1->Next = L2->Next = NULL;

    return PtrL;
}
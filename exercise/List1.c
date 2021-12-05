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

List Merge(List L1, List L2);

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

PtrToNode MakeEmpty();
List InsertLast(ElementType X, List PtrL);

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

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2)
{
    List p1 = L1->Next;
    List p2 = L2->Next;
    L1->Next = NULL;
    L2->Next = NULL;

    List PtrL;
    PtrL = (List)malloc(sizeof(struct Node));
    List p = PtrL;

    while (p1 && p2)
    {
        if (p1->Data <= p2->Data)
        {
            p->Next = p1;
            p = p->Next;
            p1 = p1->Next;
        }
        else
        {
            p->Next = p2;
            p = p->Next;
            p2 = p2->Next;
        }
    }

    if (p1 == NULL)
        p->Next = p2;
    else
        p->Next = p1;

    return PtrL;
}

List Read()
{
    List PtrL = MakeEmpty();
    scanf("%d", &PtrL->Data);
    for (int i = 1; i <= PtrL->Data; i++)
    {
        ElementType data;
        scanf("%d", &data);
        PtrL = InsertLast(data, PtrL);
    }
    return PtrL;
}

void Print(List L)
{
    List p = L;
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
    return;
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
    PtrToNode s = MakeEmpty();
    s->Data = X;
    List p = PtrL;
    while (p->Next)
        p = p->Next;
    p->Next = s;
    return PtrL;
}
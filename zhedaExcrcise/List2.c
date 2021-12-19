/*
! 设计函数分别求两个一元多项式的乘积与和。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *PtrToLNode;
struct LNode
{
    int coefficient;
    int index;
    PtrToLNode next;
};
typedef struct LNode *List;

PtrToLNode MakeEmpty()
{
    PtrToLNode PtrL;

    PtrL = (PtrToLNode)malloc(sizeof(struct LNode));
    PtrL->coefficient = PtrL->index = 0;
    PtrL->next = NULL;
    return PtrL;
}

//* 释放当前指针指向的结点，并让指针指向下一个结点。
List Free(List PtrL)
{
    PtrToLNode tmp;

    tmp = PtrL;
    PtrL = PtrL->next;
    free(tmp);

    return PtrL;
}

void FreeAll(List PtrL)
{
    while (PtrL)
        PtrL = Free(PtrL);
}

List Init()
{
    List PtrL;
    int i, total;
    List p, s;

    PtrL = MakeEmpty();
    scanf("%d", &total);
    p = PtrL;
    for (i = 0; i < total; i++)
    {
        s = MakeEmpty();
        scanf("%d", &s->coefficient);
        scanf("%d", &s->index);
        p->next = s;
        p = s;
    }

    PtrL = Free(PtrL);
    return PtrL;
}

void Print(List PtrL)
{
    List p;

    p = PtrL;
    if (PtrL == NULL)
    {
        printf("0 0");
        return;
    }

    while (p)
    {
        printf("%d %d", p->coefficient, p->index);
        p = p->next;
        if (p)
            printf(" ");
    }
}

//* 将pn指向的结点挂在ps后面，并让pn和ps指向下一个结点
void CopyAndAdd(List *pn, List *ps)
{
    List s;

    s = MakeEmpty();
    s->coefficient = (*pn)->coefficient;
    s->index = (*pn)->index;

    (*ps)->next = s;
    *ps = s;
    *pn = (*pn)->next;
}

void CopyAndAdd2(List *p1, List *p2, List *pm)
{
    List s;

    s = MakeEmpty();
    s->coefficient = (*p1)->coefficient * (*p2)->coefficient;
    s->index = (*p1)->index + (*p2)->index;

    (*pm)->next = s;
    *pm = s;
    *p2 = (*p2)->next;
}

List Add(List PtrL1, List PtrL2)
{
    List s, LS, ps, p1, p2;

    LS = MakeEmpty();
    ps = LS;
    p1 = PtrL1;
    p2 = PtrL2;

    while (p1 && p2)
    {
        if (p1->index == p2->index)
        {
            s = MakeEmpty();
            s->coefficient = p1->coefficient + p2->coefficient;

            if (s->coefficient)
            {
                s->index = p1->index;
                ps->next = s;
                ps = s;
            }
            else
                free(s);

            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->index > p2->index)
            CopyAndAdd(&p1, &ps);
        else
            CopyAndAdd(&p2, &ps);
    }

    if (p1)
        while (p1)
            CopyAndAdd(&p1, &ps);
    else
        while (p2)
            CopyAndAdd(&p2, &ps);

    LS = Free(LS);
    return LS;
}

List Mul(List PtrL1, List PtrL2)
{
    List LM, pm, p1, p2, LM2;

    LM = MakeEmpty();
    pm = LM;
    p1 = PtrL1;
    p2 = PtrL2;

    if (p1 && p2)
    {
        while (p2)
            CopyAndAdd2(&p1, &p2, &pm);

        p1 = p1->next;
        LM = Free(LM);
    }
    else
        return NULL;

    while (p1)
    {
        LM2 = MakeEmpty();
        pm = LM2;
        p2 = PtrL2;

        while (p2)
            CopyAndAdd2(&p1, &p2, &pm);

        p1 = p1->next;
        LM2 = Free(LM2);

        pm = LM;
        LM = Add(LM, LM2);
        FreeAll(pm);
        FreeAll(LM2);
    }
    return LM;
}

int main()
{
    List L1, L2, LM, LS;

    L1 = Init();
    L2 = Init();

    LM = Mul(L1, L2);
    LS = Add(L1, L2);

    Print(LM);
    printf("\n");
    Print(LS);

    return 0;
}
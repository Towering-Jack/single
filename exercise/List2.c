#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *List;
struct LNode
{
    int coefficient;
    int index;
    List next;
};

List MakeEmpty()
{
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL->next = NULL;
    return PtrL;
}

void Free(List *PtrL, List *p)
{
    *p = *PtrL;
    *PtrL = (*p)->next;
    free(*p);
}

void FreeAll(List *PtrL)
{
    List p;
    while (*PtrL) 
        Free(PtrL,&p);
}

List Init()
{
    List PtrL = MakeEmpty();
    int total;
    scanf("%d", &total);

    List s, p;
    p = PtrL;
    for (int i = 1; i <= total; i++)
    {
        s = MakeEmpty();
        scanf("%d", &s->coefficient);
        scanf("%d", &s->index);
        p->next = s;
        p = s;
    }
    Free(&PtrL, &p);
    return PtrL;
}

void Print(List PtrL)
{
    List p = PtrL;
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

void CopyAndAdd(List *pn, List *ps)
{
    List s = MakeEmpty();
    s->coefficient = (*pn)->coefficient;
    s->index = (*pn)->index;
    (*ps)->next = s;
    (*ps) = s;
    (*pn) = (*pn)->next;
}

void CopyAndAdd2(List *p1, List *p2, List *pm)
{
    List s = MakeEmpty();
    s->coefficient = (*p1)->coefficient * (*p2)->coefficient;
    s->index = (*p1)->index + (*p2)->index;
    (*pm)->next = s;
    (*pm) = s;
    (*p2) = (*p2)->next;
}

List Add(List PtrL1, List PtrL2)
{
    List LS = MakeEmpty();
    List ps = LS;
    List p1 = PtrL1, p2 = PtrL2;
    while (p1 && p2)
    {
        if (p1->index == p2->index)
        {
            List s = MakeEmpty();
            s->coefficient = p1->coefficient + p2->coefficient;
            if (s->coefficient)
            {
                s->index = p1->index;
                ps->next = s;
                ps = s;
            }
            else
            {
                free(s);
            }
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
    Free(&LS, &ps);
    return LS;
}

List Mul(List PtrL1, List PtrL2)
{
    List p1 = PtrL1, p2 = PtrL2;
    List LM = MakeEmpty();
    List pm = LM;
    if (p1 && p2)
    {
        while (p2)
            CopyAndAdd2(&p1, &p2, &pm);
        p1 = p1->next;
        Free(&LM, &pm);
    }
    else
        return NULL;

    while (p1)
    {
        List LM2 = MakeEmpty();
        pm = LM2;
        p2 = PtrL2;
        while (p2)
            CopyAndAdd2(&p1, &p2, &pm);
        p1 = p1->next;
        Free(&LM2, &pm);
        pm = LM;
        LM = Add(LM, LM2);
        FreeAll(&pm);
        FreeAll(&LM2);
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
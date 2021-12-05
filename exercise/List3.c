#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *List;
struct LNode
{
    int curAddress;
    int data;
    int NextAddress;
    List next;
};

List MakeEmpty()
{
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL->next = NULL;
    return PtrL;
}

List Scan()
{
    List PtrL = MakeEmpty();
    scanf("%d", &PtrL->curAddress);
    scanf("%d", &PtrL->data);
    scanf("%d", &PtrL->NextAddress);
    return PtrL;
}

void Print(List PtrL)
{
    List p = PtrL;
    while (p)
    {
        printf("%05d ", p->curAddress);
        printf("%d ", p->data);
        if (p->next)
            printf("%05d\n", p->NextAddress);
        else
        {
            printf("-1");
            return;
        }
        p = p->next;
    }
}

List Add(List PtrL)
{
    List p = PtrL;
    for (int i = 1; i <= PtrL->data; i++)
    {
        List s = Scan();
        p->next = s;
        p = s;
    }
    return PtrL;
}

List Sort(List PtrL)
{
    List p = PtrL;
    while (1)
    {
        if (p->next->curAddress == PtrL->curAddress)
        {
            List pmove = p->next;
            p->next = pmove->next;
            pmove->next = PtrL->next;
            PtrL->next = pmove;
            break;
        }
        p = p->next;
    }

    p = PtrL->next;
    List ptrl = p;
    for (int i = 2; i < PtrL->data; i++)
    {
        while (p->next)
        {
            if (p->next->curAddress == ptrl->NextAddress)
            {
                List pmove = p->next;
                p->next = pmove->next;
                pmove->next = ptrl->next;
                ptrl->next = pmove;
                break;
            }
            p = p->next;
        }
        p = ptrl->next;
        ptrl = p;
    }

    p = PtrL->next;
    while (p->NextAddress != -1)
    {
        p = p->next;
    }
    List temp = p->next;
    p->next = NULL;
    p = temp;
    while (temp)
    {
        p = p->next;
        free(temp);
        temp = p;
    }
    return PtrL;
}

List Reverse(List PtrL)
{
    List nextPtrl = PtrL->next;
    int K = PtrL->NextAddress - 1;
    while (K--)
        nextPtrl = nextPtrl->next;
    List ptrl = nextPtrl;

    nextPtrl = nextPtrl->next;
    List lastPtrl = PtrL->next;
    List movePtrl = ptrl;
    List p2 = ptrl;
    int ini = 1;

    int revTime = PtrL->data / PtrL->NextAddress;
    while (revTime--)
    {
        if (!ini)
        {
            lastPtrl = nextPtrl;
            K = PtrL->NextAddress - 1;
            while (K--)
                nextPtrl = nextPtrl->next;
            movePtrl = nextPtrl;
            p2->NextAddress = movePtrl->curAddress;
            p2->next = movePtrl;
            p2 = movePtrl;
        }
        ini = 0;

        while ((lastPtrl) != p2)
        {
            List p = lastPtrl;
            while (1)
            {
                if (p2->curAddress == p->NextAddress)
                {
                    p2->NextAddress = p->curAddress;
                    p2->next = p;
                    p2 = p;
                    break;
                }
                p = p->next;
            }
        }
    }

    if (PtrL->data % PtrL->NextAddress)
    {
        p2->NextAddress = nextPtrl->curAddress;
        p2->next = nextPtrl;
    }
    else
    {
        p2->next = NULL;
        p2->NextAddress = -1;
    }

    return ptrl;
}

List Init()
{
    List PtrL = Scan();
    PtrL = Add(PtrL);
    PtrL = Sort(PtrL);
    return PtrL;
}

int main()
{
    List L = Init();
    if (L->data != 1 && L->NextAddress != 1)
        L = Reverse(L);
    else
        L = L->next;
    Print(L);
    return 0;
}
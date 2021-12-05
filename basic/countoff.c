#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

void CountOff(int n, int m, int out[]);

int main()
{
    int out[MAXN], n, m;
    int i;

    scanf("%d %d", &n, &m);
    CountOff(n, m, out);
    for (i = 0; i < n; i++)
        printf("%d ", out[i]);
    printf("\n");

    return 0;
}

/* 你的代码将被嵌在这里 */
void CountOff(int n, int m, int out[])
{
    typedef struct LNode *List;
    struct LNode
    {
        int N;
        List next;
    };

    List L = (List)malloc(sizeof(struct LNode));
    L->N = 0;
    L->next = L;
    for (int i = n; i > 0; i--)
    {
        List node = (List)malloc(sizeof(struct LNode));
        node->N = i;
        node->next = L->next;
        L->next = node;
    }
    List temp = L;
    L = L->next;
    List rear = L;
    while (rear->next != temp)
        rear = rear->next;
    rear->next = temp->next;
    free(temp);

    List p = rear;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
            p = p->next;
        temp = p->next;
        p->next = temp->next;
        out[temp->N-1] = i;
        free(temp);
    }
    out[p->N-1] = n;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct SNode *Stack;
struct SNode
{
    int data;
    Stack next;
};

Stack MakeEmpty()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->data = 0;
    S->next = NULL;
    return S;
}

void Push(Stack S, int Item)
{
    struct SNode *n;
    n = (struct SNode *)malloc(sizeof(struct SNode));
    n->data = Item;
    n->next = S->next;
    S->next = n;
    S->data++;
}

void Pop(Stack S)
{
    struct SNode *FirstCell;
    FirstCell = S->next;
    S->next = FirstCell->next;
    free(FirstCell);
    S->data--;
}

void Delete(Stack *S)
{
    while ((*S)->next)
        Pop(*S);
    free(*S);
}

int main()
{
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int arr[N];
    Stack S;
here:
    while (K--)
    {
        S = MakeEmpty();
        for (int i = 0; i < N; i++)
            scanf("%d", &arr[i]);

        int j = 0;
        int num = 1;
        while (num <= N || j < N)
        {
            if (S->next == NULL)
                Push(S, num++);

            if (S->next->data > arr[j] || S->data > M)
            {
                printf("NO");
                if (K)
                    printf("\n");
                Delete(&S);
                goto here;
            }
            else if (S->next->data == arr[j])
            {
                Pop(S);
                j++;
            }
            else
                Push(S, num++);
        }

        printf("YES");
        if (K)
            printf("\n");
        Delete(&S);
    }
    S->next = NULL;
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 5

typedef struct TNode *BinTree;
struct TNode
{
    int data;
    BinTree left;
    BinTree right;
    int flag;
};

typedef struct SNode *Stack;
struct SNode
{
    BinTree data;
    Stack next;
};

void Push(Stack S, BinTree T)
{
    Stack n = (Stack)malloc(sizeof(struct SNode));
    n->data = T;
    n->next = S->next;
    S->next = n;
    S->data++;
}

BinTree Pop(Stack S)
{
    Stack frontCell = S->next;
    BinTree frontElem = frontCell->data;
    S->next = frontCell->next;
    free(frontCell);
    S->data--;
    return frontElem;
}

BinTree MakeEmptyTree()
{
    BinTree T = (BinTree)malloc(sizeof(struct TNode));
    T->data = 0;
    T->left = T->right = NULL;
    T->flag = 0;
    return T;
}

BinTree Init(int N)
{
    BinTree T = MakeEmptyTree();
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->data = 0;
    S->next = NULL;

    int i;
    char operation[STR_LEN];

    BinTree Root;
    for (i = 0; i < 2 * N; i++)
    {
        scanf("%s", operation);
        if (strcmp(operation, "Push") == 0)
        {
            if (i == 0)
            {
                scanf("%d", &T->data);
                Root = T;
                Push(S, T);
            }
            else
            {
                BinTree n = MakeEmptyTree();
                scanf("%d", &n->data);
                if (T->flag)
                {
                    T->right = n;
                    T = T->right;
                    Push(S, T);
                }
                else
                {
                    T->left = n;
                    T = T->left;
                    Push(S, T);
                }
            }
        }
        else
        {
            T = Pop(S);
            T->flag = 1;
        }
    }
    return Root;
}

void PostOrderTraversal(BinTree BT, int *N)
{
    if (BT)
    {
        PostOrderTraversal(BT->left, &(*N));
        PostOrderTraversal(BT->right, &(*N));
        printf("%d", BT->data);
        if (--(*N))
            printf(" ");
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    BinTree T = Init(N);
    PostOrderTraversal(T, &N);
    return 0;
}
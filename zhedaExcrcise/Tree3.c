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
            scanf("%d", &T->data);
            if (i == 0)
                Root = T;
            T->left = MakeEmptyTree();
            T->right = MakeEmptyTree();
            Push(S, T);
            T = T->left;
        }
        else
        {
            T = Pop(S);
            T = T->right;
        }
    }
    return Root;
}

void PostOrderTraversal(BinTree BT, int *N)
{
    if (BT->data)
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
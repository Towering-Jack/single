#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
typedef int ElemType;
typedef int Status;
struct TNode
{
    ElemType data;
    BinTree left;
    BinTree right;
    Status flag;
};

BinTree BuildTree(int N);
void Insert(ElemType data, BinTree T);
void Judge(BinTree T, int N);
void ResetFlag(BinTree T);
Status JudgeNode(BinTree T, ElemType data);

int main()
{
    Status ifFirst = 1;
    while (1)
    {
        int N, L;
        scanf("%d", &N);
        if (!N)
            break;
        if (ifFirst)
            ifFirst = 0;
        else
            printf("\n");
        scanf("%d", &L);

        BinTree T = BuildTree(N);
        for (int i = 0; i < L; i++)
        {
            ResetFlag(T);
            Judge(T, N);
            if (i != L - 1)
                printf("\n");
        }
    }
    return 0;
}

BinTree BuildTree(int N)
{
    BinTree T = NULL;
    for (int i = 0; i < N; i++)
    {
        ElemType n;
        scanf("%d", &n);
        if (T == NULL)
        {
            T = (BinTree)malloc(sizeof(struct TNode));
            T->data = n;
            T->left = T->right = NULL;
            T->flag = 0;
        }
        else
            Insert(n, T);
    }
    return T;
}

void Insert(ElemType data, BinTree T)
{
    if (data < T->data)
    {
        if (T->left)
            Insert(data, T->left);
        else
        {
            T->left = (BinTree)malloc(sizeof(struct TNode));
            T->left->data = data;
            T->left->left = T->left->right = NULL;
            T->flag = 0;
        }
    }
    else
    {
        if (T->right)
            Insert(data, T->right);
        else
        {
            T->right = (BinTree)malloc(sizeof(struct TNode));
            T->right->data = data;
            T->right->left = T->right->right = NULL;
            T->flag = 0;
        }
    }
}

void Judge(BinTree T, int N)
{
    ElemType *node;
    node = (ElemType *)malloc(N * sizeof(ElemType));
    for (int i = 0; i < N; i++)
        scanf("%d", &node[i]);

    Status ok = 1;
    for (int i = 0; i < N && ok; i++)
        ok = JudgeNode(T, node[i]);

    if (ok)
        printf("Yes");
    else
        printf("No");
}

void ResetFlag(BinTree T)
{
    if (T)
    {
        T->flag = 0;
        ResetFlag(T->left);
        ResetFlag(T->right);
    }
}

Status JudgeNode(BinTree T, ElemType data)
{
    if (T->flag == 0)
    {
        if (data == T->data)
        {
            T->flag = 1;
            return 1;
        }
        else
            return 0;
    }
    else if (data < T->data)
        return JudgeNode(T->left, data);
    else
        return JudgeNode(T->right, data);
}
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT);
void InorderTraversal(BinTree BT);

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }

    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");

    MinP = FindMin(BST);
    MaxP = FindMax(BST);

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        Tmp = Find(BST, X);

        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }

    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}

void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void InorderTraversal(BinTree BT)
{
    if (BT)
    {
        InorderTraversal(BT->Left);
        printf("%d ", BT->Data);
        InorderTraversal(BT->Right);
    }
}

//^ 你的代码将被嵌在这里
BinTree Insert(BinTree BST, ElementType X)
{
    if (!BST)
    {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else
    {
        if (X < BST->Data)
            BST->Left = Insert(BST->Left, X);
        else if (X > BST->Data)
            BST->Right = Insert(BST->Right, X);
    }

    return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{
    Position Tmp;

    if (!BST)
        return NULL;
    else
    {
        if (X < BST->Data)
            BST->Left = Delete(BST->Left, X);
        else if (X > BST->Data)
            BST->Right = Delete(BST->Right, X);
        else
        {
            if (BST->Left && BST->Right)
            {
                Tmp = FindMin(BST->Right); //& 在右子树中找到最小的结点替代删除的结点
                BST->Data = Tmp->Data;
                BST->Right = Delete(BST->Right, BST->Data);
            }
            else
            {
                Tmp = BST;

                if (!BST->Left)
                    BST = BST->Right;
                else
                    BST = BST->Left;

                free(Tmp);
            }
        }
    }

    return BST;
}

Position Find(BinTree BST, ElementType X)
{
    if (!BST)
        return NULL;

    if (X == BST->Data)
        return BST;

    if (X < BST->Data)
        return Find(BST->Left, X);
    else
        return Find(BST->Right, X);
}

Position FindMin(BinTree BST)
{
    if (!BST)
        return NULL;

    while (BST->Left)
        BST = BST->Left;

    return BST;
}

Position FindMax(BinTree BST)
{
    if (!BST)
        return NULL;

    while (BST->Right)
        BST = BST->Right;

    return BST;
}
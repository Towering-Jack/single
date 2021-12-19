#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct TNode *BinTree;
struct TNode
{
    ElemType data;
    BinTree left, right;
};

void PreorderTraversal(BinTree BT);
void InorderTraversal(BinTree BT);

BinTree Insert(BinTree BST, ElemType X);
BinTree Delete(BinTree BST, ElemType X);
BinTree Find(BinTree BST, ElemType X);
BinTree FindMin(BinTree BST);
BinTree FindMax(BinTree BST);

//* 先序遍历（递归）
void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d ", BT->data);
        PreorderTraversal(BT->left);
        PreorderTraversal(BT->right);
    }
}

//* 中序遍历（递归）
void InorderTraversal(BinTree BT)
{
    if (BT)
    {
        InorderTraversal(BT->left);
        printf("%d ", BT->data);
        InorderTraversal(BT->right);
    }
}

//* 插入操作
BinTree Insert(BinTree BST, ElemType X)
{
    if (!BST)
    {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->data = X;
        BST->left = BST->right = NULL;
    }
    else
    {
        if (X < BST->data)
            BST->left = Insert(BST->left, X);
        else if (X > BST->data)
            BST->right = Insert(BST->right, X);
    }

    return BST;
}

//* 删除操作
BinTree Delete(BinTree BST, ElemType X)
{
    BinTree Tmp;

    if (!BST)
        return NULL;
    else
    {
        if (X < BST->data)
            BST->left = Delete(BST->left, X);
        else if (X > BST->data)
            BST->right = Delete(BST->right, X);
        else
        {
            if (BST->left && BST->right)
            {
                Tmp = FindMin(BST->right); //& 在右子树中找到最小的结点替代删除的结点
                BST->data = Tmp->data;
                BST->right = Delete(BST->right, BST->data);
            }
            else
            {
                Tmp = BST;

                if (!BST->left)
                    BST = BST->right;
                else
                    BST = BST->left;

                free(Tmp);
            }
        }
    }

    return BST;
}

//* 查找操作
BinTree Find(BinTree BST, ElemType X)
{
    if (!BST)
        return NULL;

    if (X == BST->data)
        return BST;

    if (X < BST->data)
        return Find(BST->left, X);
    else
        return Find(BST->right, X);
}

//* 查找最小的结点
BinTree FindMin(BinTree BST)
{
    if (!BST)
        return NULL;

    while (BST->left)
        BST = BST->left;

    return BST;
}

//* 查找最大的结点
BinTree FindMax(BinTree BST)
{
    if (!BST)
        return NULL;

    while (BST->right)
        BST = BST->right;

    return BST;
}

//* 测试函数
int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElemType X;
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
            printf("%d is found\n", Tmp->data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->data);
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
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct TNode *AVLTree;
struct TNode
{
    ElemType data;
    AVLTree left;
    AVLTree right;
    int height;
};

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLTree T)
{
    if (!T)
        return -1;
    else
        return T->height;
}

AVLTree SingleLeftRotation(AVLTree A)
{
    AVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = Max(GetHeight(B->left), A->height) + 1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = Max(GetHeight(B->left), A->height) + 1;
    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
    A->left = SingleRightRotation(A->left);
    return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
    A->right = SingleLeftRotation(A->right);
    return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, ElemType X)
{
    if (!T)
    {
        T = (AVLTree)malloc(sizeof(struct TNode));
        T->data = X;
        T->height = 0;
        T->left = T->right = NULL;
    }
    else if (X < T->data)
    {
        T->left = Insert(T->left, X);
        if (GetHeight(T->left) - GetHeight(T->right) == 2)
        {
            if (X < T->left->data)
                T = SingleLeftRotation(T);
            else
                T = DoubleLeftRightRotation(T);
        }
    }
    else if (X > T->data)
    {
        T->right = Insert(T->right, X);
        if (GetHeight(T->right) - GetHeight(T->left) == 2)
        {
            if (X > T->right->data)
                T = SingleRightRotation(T);
            else
                T = DoubleRightLeftRotation(T);
        }
    }
    T->height = Max(GetHeight(T->left), GetHeight(T->right)) + 1;
    return T;
}

int main()
{
    int N;
    scanf("%d", &N);
    AVLTree T = NULL;
    for (size_t i = 0; i < N; i++)
    {
        int X;
        scanf("%d", &X);
        T = Insert(T, X);
    }
    printf("%d", T->data);

    return 0;
}
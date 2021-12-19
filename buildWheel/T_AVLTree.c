#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct TNode *AVLTree;
struct TNode
{
    ElemType data;
    AVLTree left, right;
    int height;
};

int Max(int a, int b);
int GetHeight(AVLTree T);
AVLTree FindMin(AVLTree T);
void PreOrderTraversal(AVLTree T);

AVLTree SingleRightRotation(AVLTree A);
AVLTree SingleLeftRotation(AVLTree A);
AVLTree DoubleLeftRightRotation(AVLTree A);
AVLTree DoubleRightLeftRotation(AVLTree A);

AVLTree Insert(AVLTree T, ElemType X);
AVLTree Delete(AVLTree T, ElemType X);
AVLTree AdjustAVL(AVLTree T);

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

AVLTree FindMin(AVLTree T)
{
    if (!T)
        return NULL;

    while (T->left)
        T = T->left;

    return T;
}

void PreOrderTraversal(AVLTree T)
{
    if (T)
    {
        printf("%d ", T->data);
        PreOrderTraversal(T->left);
        PreOrderTraversal(T->right);
    }
}

//* 单右旋(平衡因子>1，左子树的树高大于右子树的树高)
AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B;

    B = A->left;
    A->left = B->right;
    B->right = A;

    A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = Max(GetHeight(B->left), A->height) + 1;

    return B;
}

//* 单左旋(平衡因子<-1，左子树的树高小于右子树的树高)
AVLTree SingleLeftRotation(AVLTree A)
{
    AVLTree B;

    B = A->right;
    A->right = B->left;
    B->left = A;

    A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = Max(GetHeight(B->left), A->height) + 1;

    return B;
}

//* 左右双旋，先将左子树进行左单旋，再将根进行右单旋
AVLTree DoubleLeftRightRotation(AVLTree A)
{
    A->left = SingleLeftRotation(A->left);
    return SingleRightRotation(A);
}

//* 右左双旋，先将右子树进行右单旋，再将根进行左单旋
AVLTree DoubleRightLeftRotation(AVLTree A)
{
    A->right = SingleRightRotation(A->right);
    return SingleLeftRotation(A);
}

//* 插入操作
AVLTree Insert(AVLTree T, ElemType X)
{
    if (!T)
    {
        T = (AVLTree)malloc(sizeof(struct TNode));
        T->data = X;
        T->left = T->right = NULL;
    }
    else if (X < T->data)
    {
        T->left = Insert(T->left, X);
        T = AdjustAVL(T);
    }
    else if (X > T->data)
    {
        T->right = Insert(T->right, X);
        T = AdjustAVL(T);
    }

    T->height = Max(GetHeight(T->left), GetHeight(T->right)) + 1;

    return T;
}

//* 删除操作
AVLTree Delete(AVLTree T, ElemType X)
{
    AVLTree Tmp;

    if (!T)
        return NULL;
    else
    {
        if (X < T->data)
        {
            T->left = Delete(T->left, X);
            T = AdjustAVL(T);
        }
        else if (X > T->data)
        {
            T->right = Delete(T->right, X);
            T = AdjustAVL(T);
        }
        else
        {
            if (T->left && T->right)
            {
                Tmp = FindMin(T->right);
                T->data = Tmp->data;
                T->right = Delete(T->right, T->data);
                T = AdjustAVL(T);
            }
            else if (T->left)
            {
                T->data = T->left->data;
                T->left = Delete(T->left, T->data);
            }
            else if (T->right)
            {
                T->data = T->right->data;
                T->right = Delete(T->left, T->data);
            }
            else
            {
                free(T);
                return NULL;
            }
        }
    }

    T->height = Max(GetHeight(T->left), GetHeight(T->right)) + 1;

    return T;
}

//* 调整AVL树
AVLTree AdjustAVL(AVLTree T)
{
    if (GetHeight(T->left) - GetHeight(T->right) == 2)
    {
        if (GetHeight(T->left->left) > GetHeight(T->left->right))
            T = SingleRightRotation(T);
        else
            T = DoubleLeftRightRotation(T);
    }
    else if (GetHeight(T->right) - GetHeight(T->left) == 2)
    {
        if (GetHeight(T->right->left) < GetHeight(T->right->right))
            T = SingleLeftRotation(T);
        else
            T = DoubleRightLeftRotation(T);
    }
    return T;
}

//* 测试函数
//~ 测试样例: 8 88 70 61 96 120 90 65 130
int main()
{
    int i, N;
    AVLTree T;
    ElemType X, DelNum;

    scanf("%d", &N);
    T = NULL;
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        T = Insert(T, X);
    }

    PreOrderTraversal(T);
    printf("\nPlease Enter a number which you want to delete:");

    scanf("%d", &DelNum);
    T = Delete(T, DelNum);
    PreOrderTraversal(T);
    printf("\n");

    return 0;
}
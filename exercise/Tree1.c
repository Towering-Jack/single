#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10
#define Null -1

typedef int Tree;
typedef char ElemType;

struct TreeNode
{
    ElemType element;
    Tree left;
    Tree right;
} T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode *T)
{
    int total;
    Tree root = Null;
    scanf("%d", &total);

    int check[MaxTree];
    int i;
    char cl, cr;
    if (total)
    {
        for (i = 0; i < total; i++)
            check[i] = 0;

        for (i = 0; i < total; i++)
        {
            scanf("\n%c %c %c", &T[i].element, &cl, &cr);

            if (cl != '-')
            {
                T[i].left = cl - '0';
                check[T[i].left] = 1;
            }
            else
                T[i].left = Null;

            if (cr != '-')
            {
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else
                T[i].right = Null;
        }
        for (i = 0; i < total; i++)
            if (!check[i])
                break;
        root = i;
    }
    return root;
}

int Isomorphic(Tree R1, Tree R2)
{
    if ((R1 == Null) && (R2 == Null))
        return 1;
    if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null)))
        return 0;
    if (T1[R1].element != T2[R2].element)
        return 0;
    if ((T1[R1].left == Null) && (T2[R2].left == Null))
        return Isomorphic(T1[R1].right, T2[R2].right);
    if (((T1[R1].left != Null) && (T2[R2].left != Null)) && ((T1[T1[R1].left].element) == (T2[T2[R2].left].element)))
        return (Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right));
    else
        return (Isomorphic(T1[R1].left, T2[R2].right) && Isomorphic(T1[R1].right, T2[R2].left));
}

int main()
{
    Tree R1, R2;
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    if (Isomorphic(R1, R2))
        printf("Yes");
    else
        printf("No");
    return 0;
}
#include <stdio.h>
#include <math.h>

#define MAXSIZE 1000
typedef int ElementType;

void ShellSort(ElementType a[], int n);
void solve(int aLeft, int aRight, int tRoot, int *tree, int *array);
int CalculateLeftTreeLength(int N);
void LevelSearch(int *CBT, int N);

int main()
{
    int arr[MAXSIZE], CBT[MAXSIZE];
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    ShellSort(arr, N);
    solve(0, N - 1, 0, CBT, arr);
    LevelSearch(CBT, N);
    return 0;
}

void ShellSort(ElementType a[], int n)
{
    int i, j, dk;
    ElementType tmp;
    for (dk = n / 2; dk > 0; dk /= 2)
        for (i = dk; i < n; i++)
        {
            tmp = a[i];
            for (j = i; j >= dk; j -= dk)
                if (tmp < a[j - dk])
                    a[j] = a[j - dk];
                else
                    break;
            a[j] = tmp;
        }
}

int CalculateLeftTreeLength(int N)
{
    int height, res, x;
    height = log2(N + 1);
    x = N + 1 - pow(2, height);
    if (x > pow(2, height - 1))
    {
        x = pow(2, height - 1);
    }
    res = pow(2, height - 1) - 1 + x;
    return res;
}

void LevelSearch(int *CBT, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d", CBT[i]);
        if (i != N - 1)
            printf(" ");
    }
}

void solve(int aLeft, int aRight, int tRoot, int *tree, int *array)
/*
    * A function to put the input array elements to complete the initialized condition 
    * is (0,n-1,0,tree[],array[]) binary search tree
    * @param aLeft The complete binary search tree data start index in input array
    * @param aLeft The complete binary search tree data end index in input array
    * @param tRoot The index of the complete binary search tree root
    * @param tree A array to store complete binary search tree.
    * @param array A array store the input data and has been sorted ascending
    
    * n:the total nodes of the tree
    * letfLength:the nodes of the sub left nodes
    * leftRoot:the index of the sub left root in the tree
    * rightRoot:the index of the sub right root in the tree
*/
{
    int n, leftLength, leftRoot, rightRoot;
    n = aRight - aLeft + 1;
    if (n == 0)
        return;
    leftLength = CalculateLeftTreeLength(n);
    tree[tRoot] = array[aLeft + leftLength];
    leftRoot = tRoot * 2 + 1;
    rightRoot = leftRoot + 1;
    solve(aLeft, aLeft + leftLength - 1, leftRoot, tree, array);
    solve(aLeft + leftLength + 1, aRight, rightRoot, tree, array);
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MINDATA -10001
#define ERROR -1

typedef int ElemType;
typedef struct HNode *Heap;
struct HNode
{
    ElemType *data;
    int size;
    int capacity;
};
typedef Heap MinHeap;

MinHeap CreateHeap(int MaxSize);
bool IsFull(MinHeap H);
bool IsEmpty(MinHeap H);
bool Insert(MinHeap H, ElemType X);
ElemType DeleteMax(MinHeap H);
void PercDown(MinHeap H, int p);
void BulidHeap(MinHeap H);

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    MinHeap H = CreateHeap(N);
    for (int i = 1; i <= N; i++)
    {
        int X;
        scanf("%d", &X);
        Insert(H, X);
    }
    BulidHeap(H);

    int index;
    while (M--)
    {
        scanf("%d", &index);
        for (int i = index; i > 0; i/=2)
        {
            printf("%d", H->data[i]);
            if (i != 1)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}

MinHeap CreateHeap(int MaxSize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->data = (ElemType *)malloc((MaxSize + 1) * sizeof(ElemType));
    H->data[0] = MINDATA;
    H->size = 0;
    H->capacity = MaxSize;
    return H;
}

bool IsFull(MinHeap H)
{
    return (H->size == H->capacity);
}

bool IsEmpty(MinHeap H)
{
    return (H->size == 0);
}

bool Insert(MinHeap H, ElemType X)
{
    int i;
    if (IsFull(H))
        return false;

    for (i = ++H->size; H->data[i / 2] > X; i /= 2)
        H->data[i] = H->data[i / 2];
    H->data[i] = X;
    return true;
}

ElemType DeleteMax(MinHeap H)
{
    int parent, child;
    ElemType MinItem, X;
    if (IsEmpty(H))
        return ERROR;

    MinItem = H->data[1];
    X = H->data[H->size--];
    for (parent = 1; parent * 2 <= H->size; parent = child) //&判断是否有左儿子
    {
        child = parent * 2;
        if ((child != H->size) && (H->data[child] > H->data[child + 1]))
            child++;
        if (X <= H->data[child])
            break;
        else
            H->data[parent] = H->data[child];
    }
    H->data[parent] = X;
    return MinItem;
}

//^将H中以H->data[p]为根的子堆调整为最小堆
void PercDown(MinHeap H, int p)
{
    int parent, child;
    ElemType X;
    X = H->data[p];
    for (parent = p; parent * 2 <= H->size; parent = child)
    {
        child = parent * 2;
        if ((child != H->size) && (H->data[child] > H->data[child + 1]))
            child++;
        if (X <= H->data[child])
            break;
        else
            H->data[parent] = H->data[child];
    }
    H->data[parent] = X;
}

//^建造最小堆
void BulidHeap(MinHeap H)
{
    int i;
    for (i = H->size / 2; i > 0; i--) //&从最后一个结点的父节点开始
        PercDown(H, i);
}
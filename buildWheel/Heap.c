#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef struct HNode *Heap;
struct HNode
{
    ElemType *data;
    int size;
    int capacity; //&堆的最大容量
};
typedef Heap MaxHeap;

#define MAXDATA 2021 //&定义哨兵
#define ERROR -1

MaxHeap CreateHeap(int MaxSize)
{
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->data = (ElemType *)malloc((MaxSize + 1) * sizeof(ElemType));
    H->data[0] = MaxSize;
    H->size = 0;
    H->capacity = MAXDATA;
    return H;
}

bool IsFull(MaxHeap H)
{
    return (H->size == H->capacity);
}

bool IsEmpty(MaxHeap H)
{
    return (H->size == 0);
}

bool Insert(MaxHeap H, ElemType X)
{
    int i;
    if (IsFull(H))
        return false;

    for (i = ++H->size; H->data[i / 2] < X; i /= 2)
        H->data[i] = H->data[i / 2];
    H->data[i] = X;
    return true;
}

ElemType DeleteMax(MaxHeap H)
{
    int parent, child;
    ElemType MaxItem, X;
    if (IsEmpty(H))
        return ERROR;

    MaxItem = H->data[1];
    X = H->data[H->size--];
    for (parent = 1; parent * 2 <= H->size; parent = child) //&判断是否有左儿子
    {
        child = parent * 2;
        if ((child != H->size) && (H->data[child] < H->data[child + 1]))
            child++;
        if (X >= H->data[child])
            break;
        else
            H->data[parent] = H->data[child];
    }
    H->data[parent] = X;
    return MaxItem;
}

//^将H中以H->data[p]为根的子堆调整为最大堆
void PercDown(MaxHeap H, int p)
{
    int parent, child;
    ElemType X;
    X = H->data[p];
    for (parent = p; parent * 2 <= H->size; parent = child)
    {
        child = parent * 2;
        if ((child != H->size) && (H->data[child] < H->data[child + 1]))
            child++;
        if (X >= H->data[child])
            break;
        else
            H->data[parent] = H->data[child];
    }
    H->data[parent] = X;
}

//^建造最大堆
void BulidHeap(MaxHeap H)
{
    int i;
    for (i = H->size / 2; i > 0; i--) //&从最后一个结点的父节点开始
        PercDown(H, i);
}
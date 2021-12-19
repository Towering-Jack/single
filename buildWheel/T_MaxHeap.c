#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXDATA 65535 //& 定义哨兵
#define ERROR -65536
typedef int ElemType;

struct HNode
{
    ElemType *data;
    int size;
    int capacity; //& 堆的最大容量
};
typedef struct HNode *Heap;
typedef Heap MaxHeap;

MaxHeap CreateHeap(int MaxSize);
void BulidHeap(MaxHeap H);
bool Insert(MaxHeap H, ElemType X);
bool DeleteMax(MaxHeap H, ElemType *DelNum);
void PercDown(MaxHeap H, int p);
void PrintHeap(MaxHeap H);

//* 创建空堆
MaxHeap CreateHeap(int MaxSize)
{
    MaxHeap H;

    H = (MaxHeap)malloc(sizeof(struct HNode));
    H->data = (ElemType *)malloc((MaxSize + 1) * sizeof(ElemType));
    H->data[0] = MAXDATA;
    H->size = 0;
    H->capacity = MaxSize;

    return H;
}

//* 建造最大堆
void BulidHeap(MaxHeap H)
{
    int i;

    for (i = H->size / 2; i > 0; i--) //& 从最后一个结点的父节点开始
        PercDown(H, i);
}

//* 插入操作
bool Insert(MaxHeap H, ElemType X)
{
    int i;

    if (H->size == H->capacity)
        return false;

    for (i = ++H->size; H->data[i / 2] < X; i /= 2)
        H->data[i] = H->data[i / 2];

    H->data[i] = X;
    return true;
}

//* 删除操作
bool DeleteMax(MaxHeap H, ElemType *DelNum)
{
    if (H->size == 0)
        return false;

    *DelNum = H->data[1];
    H->data[1] = H->data[H->size--];
    PercDown(H, 1);
    return true;
}

//* 将H中以H->data[p]为根的子堆调整为最大堆
void PercDown(MaxHeap H, int p)
{
    int parent, child;
    ElemType X;

    X = H->data[p];
    for (parent = p; parent * 2 <= H->size; parent = child) //& 判断是否有左儿子
    {
        child = parent * 2;
        if ((child != H->size) && (H->data[child] < H->data[child + 1]))
            child++;
        if (X >= H->data[child])
            break;
        else
            H->data[parent] = H->data[child]; //& 下滤
    }
    H->data[parent] = X;
}

//* 打印堆
void PrintHeap(MaxHeap H)
{
    int i;

    for (i = 1; i <= H->size; i++)
        printf("%d ", H->data[i]);

    printf("\b\n");
}

//* 测试函数
//~ 测试样例: 8 88 70 61 96 120 90 65 130
int main()
{
    int N, i;
    MaxHeap H;
    ElemType InsNum, MaxNum;

    scanf("%d", &N);
    H = CreateHeap(10);
    for (i = 1; i <= N; i++)
    {
        scanf("%d", &H->data[i]);
        H->size++;
    }
    BulidHeap(H);
    PrintHeap(H);

    printf("Please Enter a number which you want to insert:");
    scanf("%d", &InsNum);
    Insert(H, InsNum);
    PrintHeap(H);

    DeleteMax(H, &MaxNum);
    printf("Now we delete the largest number: %d\n", MaxNum);
    PrintHeap(H);

    return 0;
}
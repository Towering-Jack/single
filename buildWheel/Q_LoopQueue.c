#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10000
typedef int ElemTypeQ;
typedef int Position;

typedef struct QNode *Queue;
struct QNode
{
    ElemTypeQ data[MAXSIZE];
    Position front, rear;
};

Queue CreateQueue();
int QueueLength(Queue PtrQ);
bool AddQ(Queue PtrQ, ElemTypeQ X);
bool DeleteQ(Queue PtrQ, ElemTypeQ *frontElem);

//* 创建空的循环队列
Queue CreateQueue()
{
    Queue PtrQ;

    PtrQ->front = PtrQ->rear = 0;
    return PtrQ;
}

//* 计算队列的长度
int QueueLength(Queue PtrQ)
{
    return (PtrQ->rear - PtrQ->front + MAXSIZE) % MAXSIZE;
}

//* 入队
bool AddQ(Queue PtrQ, ElemTypeQ X)
{
    if ((PtrQ->rear + 1) % MAXSIZE == PtrQ->front)
        return false;

    PtrQ->data[PtrQ->rear] = X;
    PtrQ->rear = (PtrQ->rear + 1) % MAXSIZE;
    return true;
}

//* 出队
bool DeleteQ(Queue PtrQ, ElemTypeQ *frontElem)
{
    if (PtrQ->front == PtrQ->rear)
        return false;

    *frontElem = PtrQ->data[PtrQ->front];
    PtrQ->front = (PtrQ->front + 1) % MAXSIZE;
    return true;
}
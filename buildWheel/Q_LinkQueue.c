#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemTypeQ;

//^ 队列中的结点
typedef struct QNode *PtrToQNode;
struct QNode
{
    ElemTypeQ data;
    PtrToQNode next;
};

//^ 队列
typedef PtrToQNode Position;
typedef struct Queue
{
    Position front, rear; //& 队列的头、尾指针
    int length;
} * Queue;

Queue CreateQueue();
void AddQ(Queue PtrQ, ElemTypeQ X);
bool DeleteQ(Queue PtrQ, ElemTypeQ *frontElem);

//* 创建空的链队列
Queue CreateQueue()
{
    Queue PtrQ;

    PtrQ = (Queue)malloc(sizeof(struct Queue));
    PtrQ->front = PtrQ->rear = NULL;
    PtrQ->length = 0;
    return PtrQ;
}

//* 入队
void AddQ(Queue PtrQ, ElemTypeQ X)
{
    PtrToQNode newNode;

    newNode = (PtrToQNode)malloc(sizeof(struct QNode));
    newNode->data = X;
    newNode->next = NULL;
    if (PtrQ->front == NULL)
        PtrQ->front = PtrQ->rear = newNode;
    else
    {
        PtrQ->rear->next = newNode;
        PtrQ->rear = newNode;
    }
    PtrQ->length++;
}

//* 出队
bool DeleteQ(Queue PtrQ, ElemTypeQ *frontElem)
{
    Position frontCell;

    if (PtrQ->length == 0)
        return false;

    frontCell = PtrQ->front;
    *frontElem = frontCell->data;
    PtrQ->front = frontCell->next;
    free(frontCell);
    PtrQ->length--;
    return true;
}
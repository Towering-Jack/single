#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10000
typedef int ElemTypeS;
typedef int Position;

typedef struct SNode *DoubleStack;
struct SNode
{
    ElemTypeS data[MAXSIZE];
    Position top1;
    Position top2;
};

DoubleStack CreateDoubleStack();
bool Push(DoubleStack PtrS, ElemTypeS Item, int StackNum);
bool Pop(DoubleStack PtrS, ElemTypeS *frontElem, int StackNum);

//* 创建空的两栈共享空间
DoubleStack CreateDoubleStack()
{
    DoubleStack PtrS;

    PtrS = (DoubleStack)malloc(sizeof(struct SNode));
    PtrS->top1 = -1;
    PtrS->top2 = MAXSIZE;
    return PtrS;
}

//* 入栈
bool Push(DoubleStack PtrS, ElemTypeS X, int StackNum)
{
    if (PtrS->top1 + 1 == PtrS->top2)
        return false;

    if (StackNum == 1)
        PtrS->data[++PtrS->top1] = X;
    else if (StackNum == 2)
        PtrS->data[--PtrS->top2] = X;
    else
        return false;

    return true;
}

//* 出栈
bool Pop(DoubleStack PtrS, ElemTypeS *frontElem, int StackNum)
{
    if (StackNum == 1)
    {
        if (PtrS->top1 == -1)
            return false;
        
        *frontElem = PtrS->data[PtrS->top1--];
    }
    else if (StackNum == 2)
    {
        if (PtrS->top2 == MAXSIZE)
            return false;

        *frontElem = PtrS->data[PtrS->top2++];
    }
    else
        return false;

    return true;
}
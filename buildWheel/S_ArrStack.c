#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10000
typedef int ElemTypeS;
typedef int Position;

typedef struct SNode *Stack;
struct SNode
{
    ElemTypeS data[MAXSIZE];
    Position top;
};

Stack CreateStack();
bool Push(Stack PtrS, ElemTypeS Item);
bool Pop(Stack PtrS, ElemTypeS *frontElem);

//* 创建空数组栈
Stack CreateStack()
{
    Stack PtrS;

    PtrS = (Stack)malloc(sizeof(struct SNode));
    PtrS->top = -1;
    return PtrS;
}

//* 入栈
bool Push(Stack PtrS, ElemTypeS X)
{
    if (PtrS->top == MAXSIZE - 1)
        return false;

    PtrS->top++;
    PtrS->data[PtrS->top] = X;
    return true;
}

//* 出栈
bool Pop(Stack PtrS, ElemTypeS *frontElem)
{
    if (PtrS->top == -1)
        return false;

    *frontElem = PtrS->data[PtrS->top];
    PtrS->top--;
    return true;
}
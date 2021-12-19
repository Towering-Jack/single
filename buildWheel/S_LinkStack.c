#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemTypeS;

typedef struct SNode *PtrToSNode;
struct SNode
{
    ElemTypeS data;
    PtrToSNode next;
};
typedef PtrToSNode Stack;

Stack CreateStack();
void Push(Stack PtrS, ElemTypeS Item);
bool Pop(Stack PtrS, ElemTypeS *frontElem);

//* 创建空链栈（有头结点）
Stack CreateStack()
{
    Stack PtrS;
    
    PtrS = (Stack)malloc(sizeof(struct SNode));
    PtrS->data = 0; //& 栈中元素的个数
    PtrS->next = NULL;
    return PtrS;
}

//* 入栈（插入链头）
void Push(Stack PtrS, ElemTypeS X)
{
    PtrToSNode n;

    n = (PtrToSNode)malloc(sizeof(struct SNode));
    n->data = X;
    n->next = PtrS->next;
    PtrS->next = n;
    PtrS->data++;
}

//* 出栈（从链头删除）
bool Pop(Stack PtrS, ElemTypeS *frontElem)
{
    Stack frontCell;

    if (PtrS->data == 0)
        return false;

    frontCell = PtrS->next;
    *frontElem = frontCell->data;
    PtrS->next = frontCell->next;
    free(frontCell);
    PtrS->data--;
    return true;
}
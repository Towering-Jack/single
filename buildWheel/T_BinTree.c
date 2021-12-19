#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^ ---------------声明二叉树--------------- ^//
typedef int ElemType;
typedef struct TNode *BinTree;
struct TNode
{
    ElemType data;
    BinTree left, right;
};
//? 二叉树声明结束

//^ ---------------声明链栈--------------- ^//
typedef BinTree ElemTypeS;
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
//? 链栈声明结束

//^ ---------------声明链队列--------------- ^//
typedef BinTree ElemTypeQ;
typedef struct QNode *PtrToQNode;
struct QNode
{
    ElemTypeQ data;
    PtrToQNode next;
};
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
//? 链队列声明结束

BinTree CreateTree();

void PreOrderTraversal(BinTree BT);
void PreOrderTraversal2(BinTree BT);

void InOrderTraversal(BinTree BT);
void InOrderTraversal2(BinTree BT);

void PostOrderTraversal(BinTree BT);
void PostOrderTraversal2(BinTree BT);

void LevelOrderTraversal(BinTree BT);

void PreOrderPrintLeaves(BinTree BT);
int PostOrderGetHeight(BinTree BT);

//* 创建空树（按照先序遍历输入，若输入^表示不存在）
BinTree CreateTree()
{
    BinTree BT;
    char ch;

    scanf("%c", &ch);
    getchar();

    if (ch == '^')
        BT = NULL;
    else
    {
        BT = (BinTree)malloc(sizeof(struct TNode));
        BT->data = ch - '0';
        BT->left = CreateTree();
        BT->right = CreateTree();
    }

    return BT;
}

//* 先序遍历（递归）
void PreOrderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d ", BT->data);
        PreOrderTraversal(BT->left);
        PreOrderTraversal(BT->right);
    }
}

//* 先序遍历（非递归）
void PreOrderTraversal2(BinTree BT)
{
    BinTree T;
    Stack S;

    T = BT;
    S = CreateStack();
    while (T || S->data)
    {
        while (T)
        {
            printf("%d ", T->data);
            Push(S, T);
            T = T->left;
        }
        if (S->data)
        {
            Pop(S, &T);
            T = T->right;
        }
    }
}

//* 中序遍历（递归）
void InOrderTraversal(BinTree BT)
{
    if (BT)
    {
        InOrderTraversal(BT->left);
        printf("%d ", BT->data);
        InOrderTraversal(BT->right);
    }
}

//* 中序遍历（非递归）
void InOrderTraversal2(BinTree BT)
{
    BinTree T;
    Stack S;

    T = BT;
    S = CreateStack();
    while (T || S->data)
    {
        while (T)
        {
            Push(S, T);
            T = T->left;
        }
        if (S->data)
        {
            Pop(S, &T);
            printf("%d ", T->data);
            T = T->right;
        }
    }
}

//* 后序遍历（递归）
void PostOrderTraversal(BinTree BT)
{
    if (BT)
    {
        PostOrderTraversal(BT->left);
        PostOrderTraversal(BT->right);
        printf("%d ", BT->data);
    }
}

//* 后序遍历（非递归），先序遍历从右向左，逆序输出
void PostOrderTraversal2(BinTree BT)
{
    BinTree T;
    Stack S1, S2;

    T = BT;
    S1 = CreateStack();
    S2 = CreateStack(); //& 用于逆序输出
    while (T || S1->data)
    {
        while (T)
        {
            Push(S2, T);
            Push(S1, T);
            T = T->right;
        }
        if (S1->data)
        {
            Pop(S1, &T);
            T = T->left;
        }
    }

    while (S2->data)
    {
        Pop(S2, &T);
        printf("%d ", T->data);
    }
}

//* 层序遍历
void LevelOrderTraversal(BinTree BT)
{
    Queue Q;
    BinTree T;

    if (!BT)
        return;

    Q = CreateQueue();
    AddQ(Q, BT);
    while (Q->length)
    {
        DeleteQ(Q, &T);
        printf("%d ", T->data);

        if (T->left)
            AddQ(Q, T->left);
        if (T->right)
            AddQ(Q, T->right);
    }
}

//* 先序遍历输出叶子节点
void PreOrderPrintLeaves(BinTree BT)
{
    if (BT)
    {
        if (!BT->left && !BT->right)
            printf("%d ", BT->data);

        PreOrderPrintLeaves(BT->left);
        PreOrderPrintLeaves(BT->right);
    }
}

//* 求树的高度
int PostOrderGetHeight(BinTree BT)
{
    int HL, HR, MaxH;

    if (BT)
    {
        HL = PostOrderGetHeight(BT->left);
        HR = PostOrderGetHeight(BT->right);
        MaxH = (HL > HR) ? HL : HR;
        return (MaxH + 1);
    }
    else
        return 0;
}

//* 测试函数
//~ 测试样例: 1 2 4 ^ ^ 5 7 ^ ^ ^ 3 6 8 ^ ^ 9 ^ ^ ^
int main()
{
    BinTree T = CreateTree();

    PreOrderTraversal(T);
    printf("\n");

    PreOrderTraversal2(T);
    printf("\n");

    InOrderTraversal(T);
    printf("\n");

    InOrderTraversal2(T);
    printf("\n");

    PostOrderTraversal(T);
    printf("\n");

    PostOrderTraversal2(T);
    printf("\n");

    LevelOrderTraversal(T);
    printf("\n");

    PreOrderPrintLeaves(T);
    printf("\n");

    printf("%d", PostOrderGetHeight(T));

    return 0;
}
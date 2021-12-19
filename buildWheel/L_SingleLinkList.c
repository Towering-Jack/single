#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef int Position;

typedef struct LNode *PtrToLNode;
struct LNode
{
    ElemType data;
    PtrToLNode next;
};
typedef PtrToLNode List;

List CreateList();
List InitList();
List FindKth(Position K, List PtrL);
List Find(ElemType X, List PtrL);
void InsertToHead(ElemType X, List PtrL);
void InsertToTail(ElemType X, List PtrL);
bool InsertPos(ElemType X, Position i, List PtrL);
bool DeletePos(Position i, List PtrL);
void Print(List PtrL);

//* 创建带头结点的空单链表
List CreateList()
{
    List PtrL;
    
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL->data = 0;
    PtrL->next = NULL;
    return PtrL;
}

//* 初始化单链表
List InitList()
{
    List PtrL;
    int N;
    Position i;
    ElemType X;

    PtrL = CreateList();

    printf("请输入你要存入的数据个数:");
    scanf("%d", &N);
    printf("请输入数据:");
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        // InsertToHead(X, PtrL);
        InsertToTail(X, PtrL);
    }

    printf("输入完成。\n");
    return PtrL;
}

//* 按序号查找，返回查找的结点指针，失败则返回NULL
List FindKth(Position K, List PtrL)
{
    List p;
    Position i;

    if (K > PtrL->data)
        return NULL;

    p = PtrL->next;
    i = 1;
    while (p != NULL && i < K)
    {
        p = p->next;
        i++;
    }

    if (i == K)
        return p;
    else
        return NULL;
}

//* 按值查找，返回查找的结点指针，失败则返回NULL
List Find(ElemType X, List PtrL)
{
    List p;

    p = PtrL->next;
    while (p != NULL && p->data != X)
        p = p->next;

    return p;
}

//* 头插法
void InsertToHead(ElemType X, List PtrL)
{
    PtrToLNode newNode;

    newNode = (PtrToLNode)malloc(sizeof(struct LNode));
    newNode->data = X;
    newNode->next = PtrL->next;
    PtrL->next = newNode;
    PtrL->data++;
}

//* 尾插法
void InsertToTail(ElemType X, List PtrL)
{
    PtrToLNode newNode, p;

    p = PtrL;
    while (p->next)
        p = p->next;

    newNode = (PtrToLNode)malloc(sizeof(struct LNode));
    newNode->data = X;
    newNode->next = NULL;
    p->next = newNode;
    PtrL->data++;
}

//* 将元素插入到第i个位置
bool InsertPos(ElemType X, Position i, List PtrL)
{
    PtrToLNode p, newNode;

    if (i != 1)
        p = FindKth(i - 1, PtrL);
    else
        p = PtrL;

    if (p == NULL)
    {
        printf("第%d个位置不合法。\n", i);
        return false;
    }
    else
    {
        newNode = (List)malloc(sizeof(struct LNode));
        newNode->data = X;
        newNode->next = p->next;
        p->next = newNode;
        PtrL->data++;
        return true;
    }
}

//* 删除第i个位置的结点
bool DeletePos(Position i, List PtrL)
{
    PtrToLNode p, tmp;

    if (i != 1)
        p = FindKth(i - 1, PtrL);
    else
        p = PtrL;

    if (p == NULL)
    {
        printf("第%d个结点不存在。\n", i - 1);
        return false;
    }
    else if (p->next == NULL)
    {
        printf("第%d个结点不存在。\n", i);
        return false;
    }
    else
    {
        tmp = p->next;
        p->next = tmp->next;
        free(tmp);
        PtrL->data--;
        return true;
    }
}

//* 打印整个链表，第一个是链表元素的个数
void Print(List PtrL)
{
    List p;
    
    p = PtrL;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\b\n");
}

//* 测试函数
int main()
{
    List L;
    PtrToLNode p;
    ElemType AddNum, FindNum;
    Position AddPos, FindPos, DelPos;

    L = InitList();

    printf("请输入你要插入的数据和所在的位置:");
    scanf("%d %d", &AddNum, &AddPos);
    if (InsertPos(AddNum, AddPos, L))
        printf("插入完成。\n");
    else
        printf("插入失败，第%d个位置不合法。\n", AddPos);
    Print(L);

    printf("请输入你要查找的数据:");
    scanf("%d", &FindNum);
    p = Find(FindNum, L);
    if (p)
        printf("数据\"%d\"存在。\n", p->data);
    else
        printf("该线性表中没有数据\"%d\"。\n", FindNum);

    printf("请输入你要查找的数据所在的位置:");
    scanf("%d", &FindPos);
    p = FindKth(FindPos, L);
    if (p)
        printf("第%d个位置是\"%d\"。\n", FindPos, p->data);
    else
        printf("第%d个位置不合法。\n", FindPos);

    printf("请输入你要删除的数据所在的位置:");
    scanf("%d", &DelPos);
    if (DeletePos(DelPos, L))
        printf("删除成功。\n");
    else
        printf("删除失败，第%d个位置不合法。\n", DelPos);
    Print(L);

    return 0;
}
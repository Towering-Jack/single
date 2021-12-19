#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;
typedef int Position;

typedef struct LNode *List;
struct LNode
{
    ElemType data[MAXSIZE];
    int length;
};

List InitList();
Position FindLNode(ElemType X, List PtrL);
void InsertLNode(ElemType X, Position i, List PtrL);
void DeleteLNode(Position i, List PtrL);
void PrintList(List PtrL);

//* 初始化空线性表
List InitList()
{
    List PtrL;
    Position i;

    PtrL = (List)malloc(sizeof(struct LNode));

    printf("请输入你要存入的数据个数:");
    scanf("%d", &PtrL->length);
    printf("请输入数据:");
    for (i = 0; i < PtrL->length; i++)
        scanf("%d", &PtrL->data[i]);

    printf("输入完成。\n");
    return PtrL;
}

//* 查找元素的位置，输入数据返回所在位置，失败则返回0。(第一个元素从1开始)
Position FindLNode(ElemType X, List PtrL)
{
    Position i;

    for (i = 0; i < PtrL->length; i++)
        if (PtrL->data[i] == X)
            break;

    if (i == PtrL->length)
        return 0;
    else
        return ++i;
}

//* 将元素插入到第i个位置
void InsertLNode(ElemType X, Position i, List PtrL)
{
    Position j;

    if (PtrL->length == MAXSIZE)
    {
        printf("此表已满。\n");
        return;
    }
    if (i < 1 || i > PtrL->length + 1)
    {
        printf("第%d个位置不合法。\n", i);
        return;
    }

    for (j = PtrL->length - 1; j >= i - 1; j--)
        PtrL->data[j + 1] = PtrL->data[j];
    PtrL->data[i - 1] = X;
    PtrL->length++;

    printf("插入完成。\n");
}

//* 删除第i个元素
void DeleteLNode(Position i, List PtrL)
{
    Position j;

    if (i < 1 || i > PtrL->length + 1)
    {
        printf("不存在第%d个元素。\n", i);
        return;
    }

    for (j = i; j <= PtrL->length; j++)
        PtrL->data[j - 1] = PtrL->data[j];
    PtrL->length--;

    printf("删除完成。\n");
}

//* 打印线性表中的所有元素
void PrintList(List PtrL)
{
    Position i;

    printf("这个线性表有%d个元素。\n", PtrL->length);
    for (i = 0; i < PtrL->length; i++)
        printf("%d ", PtrL->data[i]);

    printf("\b\n");
}

//* 测试函数
int main()
{
    List L;
    ElemType AddNum, FindNum, DelNum;
    Position AddPos, FindPos, DelPos;

    L = InitList();

    printf("请输入你要插入的数据和所在的位置:");
    scanf("%d %d", &AddNum, &AddPos);
    InsertLNode(AddNum, AddPos, L);
    PrintList(L);

    printf("请输入你要查找的数据:");
    scanf("%d", &FindNum);
    FindPos = FindLNode(FindNum, L);
    if (FindPos)
        printf("数据\"%d\"在第%d个位置。\n", FindNum, FindPos);
    else
        printf("该线性表中没有数据\"%d\"。\n", FindNum);

    printf("请输入你要删除数据所在的位置:");
    scanf("%d", &DelPos);
    DeleteLNode(DelPos, L);
    PrintList(L);

    printf("请输入你要删除的数据:");
    scanf("%d", &DelNum);
    DelPos = FindLNode(DelNum, L);
    if (DelPos)
    {
        DeleteLNode(DelPos, L);
        PrintList(L);
    }
    else
        printf("该线性表中没有数据\"%d\"。\n", FindNum);

    return 0;
}
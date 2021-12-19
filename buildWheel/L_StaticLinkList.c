#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10000
typedef int ElemType;
typedef int Position;

typedef struct
{
    ElemType data;
    Position next;
} List[MAXSIZE]; //& 下标为0的data存放链表长度，next存放备用链表的第一个结点的下标
                 //& 下标为MAXSIZE-1的元素的next存放第一个有数值的元素的下标
                 //& 最后一个元素的next用0表示

void Init(List PtrL);
Position FindKth(Position K, List PtrL);
Position Find(ElemType X, List PtrL);
Position MallocSLL(List PtrL);
bool InsertPos(ElemType X, Position i, List PtrL);
void FreeSLL(Position i, List PtrL);
bool DeletePos(Position i, List PtrL);
void Print(List PtrL);

//* 初始化
void Init(List PtrL)
{
    Position i;
    int N;
    ElemType X;

    PtrL[0].data = 0;
    PtrL[MAXSIZE - 1].next = 0;
    for (i = 0; i < MAXSIZE - 1; i++)
        PtrL[i].next = i + 1;

    printf("请输入你要存入的数据个数:");
    scanf("%d", &N);
    printf("请输入数据:");
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        InsertPos(X, i + 1, PtrL);
    }

    printf("输入完成。\n");
}

//* 按序号查找，返回查找的结点下标
Position FindKth(Position K, List PtrL)
{
    Position i, j;

    if (K < 1 || K > PtrL[0].data)
        return false;

    j = PtrL[MAXSIZE - 1].next;
    for (i = 1; i < K; i++)
        j = PtrL[j].next;
    return j;
}

//* 按值查找，返回查找的结点位置
Position Find(ElemType X, List PtrL)
{
    Position i, cnt;

    i = PtrL[MAXSIZE - 1].next;
    cnt = 1;
    while (i != 0)
        if (PtrL[i].data == X)
            break;
        else
        {
            i = PtrL[i].next;
            cnt++;
        }

    if (i == 0)
        return false;
    else
        return cnt;
}

//* 若备用空间链表非空，返回分配的结点下标，否则返回0
Position MallocSLL(List PtrL)
{
    Position i;

    i = PtrL[0].next;
    if (PtrL[0].next)
        PtrL[0].next = PtrL[i].next;

    return i;
}

//* 将元素插入到第i个位置
bool InsertPos(ElemType X, Position i, List PtrL)
{
    Position j, k, l;

    if (i < 1 || i > PtrL[0].data + 1)
        return false;

    j = MallocSLL(PtrL);
    k = MAXSIZE - 1;
    if (j)
    {
        PtrL[j].data = X;
        for (l = 1; l < i; l++)
            k = PtrL[k].next;

        PtrL[j].next = PtrL[k].next;
        PtrL[k].next = j;
        PtrL[0].data++;
        return true;
    }
    return false;
}

//* 将下标为i的空闲结点回收到备用链表
void FreeSLL(Position i, List PtrL)
{
    PtrL[i].next = PtrL[0].next;
    PtrL[0].next = i;
}

//* 删除第i个位置的结点
bool DeletePos(Position i, List PtrL)
{
    Position j, k;

    if (i < 1 || i > PtrL[0].data)
        return false;

    k = MAXSIZE - 1;
    for (j = 1; j < i; j++)
        k = PtrL[k].next;

    j = PtrL[k].next;            //& j为要删除的结点的下标
    PtrL[k].next = PtrL[j].next; //& k之后的元素不是j，而是j的下一个元素
                                 //& 相当于删除了j
    FreeSLL(j, PtrL);
    PtrL[0].data--;
    return true;
}

//* 打印整个链表
void Print(List PtrL)
{
    Position i;

    printf("%d  ", PtrL[0].data);
    i = PtrL[MAXSIZE - 1].next;
    while (i != 0)
    {
        printf("%d ", PtrL[i].data);
        i = PtrL[i].next;
    }

    printf("\b\n");
}

//* 测试函数
int main()
{
    List L;
    ElemType AddNum, FindNum;
    Position AddPos, FindPos, DelPos;

    Init(L);
    Print(L);

    printf("请输入你要插入的数据和所在的位置:");
    scanf("%d %d", &AddNum, &AddPos);
    if (InsertPos(AddNum, AddPos, L))
        printf("插入完成。\n");
    else
        printf("插入失败，第%d个位置不合法或者静态链表已满。\n", AddPos);
    Print(L);

    printf("请输入你要查找的数据:");
    scanf("%d", &FindNum);
    FindPos = Find(FindNum, L);
    if (FindPos)
        printf("数据\"%d\"在第%d个位置。\n", FindNum, FindPos);
    else
        printf("该线性表中没有数据\"%d\"。\n", FindNum);

    printf("请输入你要查找的数据所在的位置:");
    scanf("%d", &FindPos);
    FindNum = L[FindKth(FindPos, L)].data;
    if (FindKth(FindPos, L))
        printf("第%d个位置是\"%d\"。\n", FindPos, FindNum);
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
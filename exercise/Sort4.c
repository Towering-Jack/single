#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 114514
typedef int ElemType;

//^---------------桶排序---------------^//(稳定)
//&桶元素结点
typedef struct BNode *PtrToBNode;
struct BNode
{
    int key;
    PtrToBNode next;
};

//&桶头结点
struct HeadBNode
{
    PtrToBNode head, tail;
};
typedef struct HeadBNode *Bucket;

void Bucket_Sort(ElemType A[], int N)
{
    Bucket B;
    PtrToBNode temp, p;
    int i;
    ElemType max, min, CountNum;

    //&寻找最大值和最小值
    min = A[0];
    max = A[0];
    for (i = 0; i < N; i++)
    {
        if (A[i] < min)
            min = A[i];
        if (A[i] > max)
            max = A[i];
    }
    CountNum = max - min + 1;

    B = (Bucket)malloc(CountNum * sizeof(struct HeadBNode));
    for (i = 0; i < CountNum; i++)
        B[i].head = B[i].tail = NULL;

    for (i = 0; i < N; i++)
    {
        temp = (PtrToBNode)malloc(sizeof(struct BNode));
        temp->key = i; //&存入数组信息，此处存入数组下标
        temp->next = B[A[i] - min].head;
        B[A[i] - min].head = temp;
    }

    //&函数内打印信息
    int cnt;
    for (i = 0; i < CountNum; i++)
    {
        cnt = 0;
        if (B[i].head)
        {
            p = B[i].head;
            while (p)
            {
                cnt++;
                temp = p;
                p = p->next;
                free(temp);
            }
        }
        if (cnt)
        {
            printf("%d:%d", i, cnt);
            if (i != CountNum - 1)
                printf("\n");
        }
    }
}
//~桶排序结束

int main()
{
    int i, N;
    ElemType arrData[MAXSIZE];

    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &arrData[i]);

    Bucket_Sort(arrData, N);

    return 0;
}
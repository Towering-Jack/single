#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//^ ---------------HashTable的定义--------------- ^//
#define KEYLENGTH 11 //& 关键字长度
typedef char ElemType[KEYLENGTH + 1];
typedef int Index; //& 散列地址类型

typedef struct LNode *PtrToLNode;
struct LNode
{
    ElemType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

struct TblNode
{
    int TableSize;
    List Heads;
};
typedef struct TblNode *HashTable;
//? HashTable定义结束

#define MAXTABLESIZE 1000000
//* 返回大于N且不超过MAXTABLESZIZE的最小素数
int NextPrime(int N)
{
    int i, p;

    p = (N % 2) ? (N + 2) : (N + 1); //&从大于N的下一个奇数开始
    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break;

        if (i == 2)
            break;
        else
            p += 2;
    }
    return p;
}

//* 创建大小为TableSize的散列表
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));

    for (i = 0; i < H->TableSize; i++)
    {
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Next = NULL;
        H->Heads[i].Count = 0;
    }
    return H;
}

//* 散列函数：除留余数法
int Hash(int Key, int P)
{
    return Key % P;
}

//* 查找
#define MAXD 5
Position Find(HashTable H, ElemType Key)
{
    Position P;
    Index Pos;

    Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize);
    P = H->Heads[Pos].Next;
    while (P && strcmp(P->Data, Key))
        P = P->Next;

    return P;
}

//* 插入
void Insert(HashTable H, ElemType Key)
{
    Position P, NewCell;
    Index Pos;

    P = Find(H, Key);
    if (!P)
    {
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;

        Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize);
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
    }
    else
        P->Count++;
}

//* 扫描并输出
void ScanAndOutput(HashTable H)
{
    int i, MaxCnt, PCnt;
    ElemType MinPhone;
    List Ptr;

    MaxCnt = PCnt = 0;
    MinPhone[0] = '\0';
    for (i = 0; i < H->TableSize; i++)
    {
        Ptr = H->Heads[i].Next;
        while (Ptr)
        {
            if (Ptr->Count > MaxCnt)
            {
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data);
                PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt)
            {
                PCnt++;
                if (strcmp(MinPhone, Ptr->Data) > 0)
                    strcpy(MinPhone, Ptr->Data);
            }
            Ptr = Ptr->Next;
        }
    }

    printf("%s %d", MinPhone, MaxCnt);
    if (PCnt > 1)
        printf(" %d", PCnt);
}

//* 测试函数
/*
~ 测试数据:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
*/
int main()
{
    int N, i;
    ElemType Key;
    HashTable H;

    scanf("%d", &N);
    H = CreateTable(N * 2);
    for (i = 0; i < 2 * N; i++)
    {
        scanf("%s", Key);
        Insert(H, Key);
    }
    ScanAndOutput(H);
    // DestroyTable(H);

    return 0;
}
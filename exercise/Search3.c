#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//^---------------HashTable的定义---------------^//
#define ACCOUNTLENGTH 10
#define PASSWDLENGTH 16
typedef char AccountType[ACCOUNTLENGTH + 1];
typedef char PasswdType[PASSWDLENGTH + 1];
typedef int Index; //&散列地址类型

typedef struct LNode *PtrToLNode;
struct LNode
{
    AccountType Account;
    PasswdType Passwd;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;
struct TblNode
{
    int TableSize;
    List Heads;
};
//?HashTable定义结束

#define MAXTABLESIZE 1000000
//*返回大于N且不超过MAXTABLESZIZE的最小素数
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

HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));

    for (i = 0; i < H->TableSize; i++)
    {
        H->Heads[i].Account[0] = '\0';
        H->Heads[i].Passwd[0] = '\0';
        H->Heads[i].Next = NULL;
    }
    return H;
}

int Hash(int Account, int P)
{
    return Account % P;
}

Position Find(HashTable H, AccountType Account)
{
    Position P;
    Index Pos;

    Pos = Hash(atoi(Account), H->TableSize);
    P = H->Heads[Pos].Next;
    while (P && strcmp(P->Account, Account))
        P = P->Next;

    return P;
}

bool Insert(HashTable H, AccountType Account, PasswdType Passwd)
{
    Position P, NewCell;
    Index Pos;

    P = Find(H, Account);
    if (!P)
    {
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Account, Account);
        strcpy(NewCell->Passwd, Passwd);
        Pos = Hash(atoi(Account), H->TableSize);
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else
        return false;
}

void CheckLogin(HashTable H, AccountType Account, PasswdType Passwd)
{
    Position P;

    P = Find(H, Account);
    if (P)
    {
        if (!strcmp(P->Passwd, Passwd))
            printf("Login: OK\n");
        else
            printf("ERROR: Wrong PW\n");
    }
    else
        printf("ERROR: Not Exist\n");
}

int main()
{
    int N, i;
    char C;
    AccountType Account;
    PasswdType Passwd;
    HashTable H;

    scanf("%d\n", &N);
    H = CreateTable(N * 2);
    for (i = 0; i < N; i++)
    {
        scanf("%c ", &C);
        scanf("%s", Account);
        getchar();
        scanf("%s", Passwd);
        getchar();
        if (C == 'L')
            CheckLogin(H, Account, Passwd);
        else if (C == 'N')
        {
            if (Insert(H, Account, Passwd))
                printf("New: OK\n");
            else
                printf("ERROR: Exist\n");
        }
    }
    // DestroyTable(H);

    return 0;
}
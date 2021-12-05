#include <stdio.h>

#define MaxSize 10001

typedef int ElemType;
typedef int SetName;
typedef ElemType SetType[MaxSize];

void Init(SetType S, int n);
void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S, int n);
SetName Find(SetType S, ElemType X);
void Union(SetType S, SetName Root1, SetName Root2);

int main()
{
    SetType S;
    int n;
    char in;
    scanf("%d", &n);
    Init(S, n);
    do
    {
        scanf("%c", &in);
        switch (in)
        {
        case 'I':
            Input_connection(S);
            break;
        case 'C':
            Check_connection(S);
            break;
        case 'S':
            Check_network(S, n);
            break;
        }
    } while (in != 'S');
    return 0;
}

void Init(SetType S, int n)
{
    for (int i = 0; i < n; i++)
        S[i] = -1;
}

void Input_connection(SetType S)
{
    ElemType u, v;
    SetName Root1, Root2;
    scanf("%d %d\n", &u, &v);
    Root1 = Find(S, u - 1);
    Root2 = Find(S, v - 1);
    if (Root1 != Root2)
        Union(S, Root1, Root2);
}

void Check_connection(SetType S)
{
    ElemType u, v;
    SetName Root1, Root2;
    scanf("%d %d\n", &u, &v);
    Root1 = Find(S, u - 1);
    Root2 = Find(S, v - 1);
    if (Root1 == Root2)
        printf("yes\n");
    else
        printf("no\n");
}

void Check_network(SetType S, int n)
{
    int i, counter = 0;
    for (i = 0; i < n; i++)
    {
        if (S[i] < 0)
            counter++;
    }
    if (counter == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", counter);
}

SetName Find(SetType S, ElemType X)
{
    if (S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]);
}

void Union(SetType S, SetName Root1, SetName Root2)
{
    if (S[Root2] < S[Root1])
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
    else
    {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}
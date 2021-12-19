#include <stdio.h>
#include <stdbool.h>

#define MaxSize 10000

typedef int ElemType;
typedef int SetName;
typedef ElemType SetType[MaxSize];

//* 初始化并查集
void InitVSet(SetType S, int N)
{
    ElemType X;

    for (X = 0; X < N; X++)
        S[X] = -1;
}

//* 小集合并入大集合，默认Root1和Root2是不同集合的根节点（按秩归并）
void Union(SetType S, SetName Root1, SetName Root2)
{
    if (S[Root2] < S[Root1]) //&如果集合2比较大
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

//* 寻找顶点的根（路径压缩）
SetName FindRoot(SetType S, ElemType X)
{
    if (S[X] < 0)
        return X;
    else
        return S[X] = FindRoot(S, S[X]); //&路径压缩
}

//* 检查连接V1和V2的边是否在现有的最小生成树子集中构成回路
bool CheckCycle(SetType Vset, ElemType V1, ElemType V2)
{
    SetName Root1, Root2;

    Root1 = FindRoot(Vset, V1);
    Root2 = FindRoot(Vset, V2);

    if (Root1 == Root2)
        return false;
    else
    {
        Union(Vset, Root1, Root2);
        return true;
    }
}
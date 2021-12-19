#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^ ---------------声明邻接表--------------- ^//
#define MaxVertexNum 100
#define ERROR -1
typedef int Vertex;
typedef int WeightType;
typedef int DataType;

//~ 边的定义
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

//~ 邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

//~ 顶点表头结点的定义
typedef struct VNode
{
    // DataType Data; //&可以省略
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

//~ 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int NumV;
    int NumE;
    AdjList G;
};
typedef PtrToGNode LGraph; //&以邻接表方式存储的图类型

LGraph CreateGraph(int VertexNum);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildGraph();

//* 初始化一个有VertexNum个顶点但没有边的图
LGraph CreateGraph(int VertexNum)
{
    LGraph Graph;
    Vertex V;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->NumV = VertexNum;
    Graph->NumE = 0;

    for (V = 0; V < Graph->NumV; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

//* 添加一条边（按照从小到大的顺序插入）
void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode, priorBigIndexNode;

    //&插入边<V1, V2>
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;

    priorBigIndexNode = Graph->G[E->V1].FirstEdge;
    if (!priorBigIndexNode || NewNode->AdjV < priorBigIndexNode->AdjV)
    {
        NewNode->Next = priorBigIndexNode;
        Graph->G[E->V1].FirstEdge = NewNode;
    }
    else
    {
        while (priorBigIndexNode->Next)
        {
            if (NewNode->AdjV < priorBigIndexNode->Next->AdjV)
                break;
            priorBigIndexNode = priorBigIndexNode->Next;
        }
        NewNode->Next = priorBigIndexNode->Next;
        priorBigIndexNode->Next = NewNode;
    }

    //&若是无向图，还要插入边<V2,V1>
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;

    priorBigIndexNode = Graph->G[E->V2].FirstEdge;
    if (!priorBigIndexNode || NewNode->AdjV < priorBigIndexNode->AdjV)
    {
        NewNode->Next = priorBigIndexNode;
        Graph->G[E->V2].FirstEdge = NewNode;
    }
    else
    {
        while (priorBigIndexNode->Next)
        {
            if (NewNode->AdjV < priorBigIndexNode->Next->AdjV)
                break;
            priorBigIndexNode = priorBigIndexNode->Next;
        }
        NewNode->Next = priorBigIndexNode->Next;
        priorBigIndexNode->Next = NewNode;
    }
}

//* 创建一个邻接图
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    int NumV, i;

    scanf("%d", &NumV);
    Graph = CreateGraph(NumV);

    scanf("%d", &(Graph->NumE));
    if (Graph->NumE != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        //&读入边，格式为“起点 终点 权值”，插入邻接表
        for (i = 0; i < Graph->NumE; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}
//? 邻接表声明结束

//^ ---------------顶点并查集定义--------------- ^//
typedef Vertex ElemType;
typedef Vertex SetName;
typedef ElemType SetType[MaxVertexNum];

void InitVSet(SetType S, int N);
void Union(SetType S, SetName Root1, SetName Root2);
SetName FindRoot(SetType S, ElemType X);
bool CheckCycle(SetType Vset, Vertex V1, Vertex V2);

//* 初始化并查集
void InitVSet(SetType S, int N)
{
    ElemType X;

    for (X = 0; X < N; X++)
        S[X] = -1;
}

//* 小集合并入大集合，默认Root1和Root2是不同集合的根节点
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

//* 寻找顶点的根
SetName FindRoot(SetType S, ElemType X)
{
    if (S[X] < 0)
        return X;
    else
        return S[X] = FindRoot(S, S[X]); //&路径压缩
}

//* 检查连接V1和V2的边是否在现有的最小生成树子集中构成回路
bool CheckCycle(SetType Vset, Vertex V1, Vertex V2)
{
    Vertex Root1, Root2;

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
//? 并查集定义结束

//^ ---------------边的最小堆定义--------------- ^//
void PercDown(Edge ESet, Vertex p, int N);
void InitESet(LGraph Graph, Edge ESet);
int GetEdge(Edge ESet, int CurrentSize);

//* 将N个元素的边数组中以ESet[p]为根的子堆调整为关于Weight的最小堆
void PercDown(Edge ESet, Vertex p, int N)
{
    Vertex parent, child;
    struct ENode X;

    X = ESet[p];
    for (parent = p; (parent * 2 + 1) < N; parent = child) //& 没有哨兵
    {
        child = parent * 2 + 1;
        if ((child != N - 1) && (ESet[child].Weight > ESet[child + 1].Weight))
            child++;
        if (X.Weight <= ESet[child].Weight)
            break;
        else
            ESet[parent] = ESet[child];
    }
    ESet[parent] = X;
}

//* 将图的边存入数组ESet，并且初始化为最小堆
void InitESet(LGraph Graph, Edge ESet)
{
    Vertex V;
    PtrToAdjVNode W;
    int ECount;

    ECount = 0;
    for (V = 0; V < Graph->NumV; V++)
    {
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (V < W->AdjV) //& 避免重复录入无向图的边，只收V1<V2的边
            {
                ESet[ECount].V1 = V;
                ESet[ECount].V2 = W->AdjV;
                ESet[ECount++].Weight = W->Weight;
            }
        }
    }

    //& 初始化最小堆
    for (ECount = Graph->NumE / 2; ECount >= 0; ECount--)
        PercDown(ESet, ECount, Graph->NumE);
}

//* 给定当前堆的大小CurrentSize，将当前最小边位置弹出并调整堆
int GetEdge(Edge ESet, int CurrentSize)
{
    struct ENode temp;

    if (CurrentSize == 0)
        return ERROR;

    temp = ESet[0];
    ESet[0] = ESet[CurrentSize - 1];
    ESet[CurrentSize - 1] = temp; //& 将最小边与当前堆的最后一个位置的边交换

    PercDown(ESet, 0, CurrentSize - 1);
    return CurrentSize - 1; //& 返回最小边所在位置
}
//? 最小堆定义结束

//* Kruskal算法，返回最小权重和
WeightType Kruskal(LGraph Graph, LGraph MST)
{
    WeightType totalWeight;
    int ECount, NextEdge;
    SetType VSet; //& 顶点数组
    Edge ESet;    //& 边数组

    InitVSet(VSet, Graph->NumV);
    ESet = (Edge)malloc(sizeof(struct ENode) * Graph->NumE);
    InitESet(Graph, ESet);
    totalWeight = 0;
    ECount = 0;

    NextEdge = Graph->NumE;
    while (ECount < Graph->NumV - 1)
    {
        NextEdge = GetEdge(ESet, NextEdge); //& 从边集中得到最小边的位置
        if (NextEdge < 0)
            break;

        if (CheckCycle(VSet, ESet[NextEdge].V1, ESet[NextEdge].V2))
        {
            InsertEdge(MST, ESet + NextEdge);
            totalWeight += ESet[NextEdge].Weight;
            ECount++;
        }
    }

    if (ECount != Graph->NumV - 1)
        return ERROR;
    else
        return totalWeight;
}

//* 测试函数
/*
~ 测试数据:
6 15
0 1 5
0 2 3
0 3 7
0 4 4
0 5 2
1 2 4
1 3 6
1 4 2
1 5 6
2 3 6
2 4 1
2 5 1
3 4 10
3 5 8
4 5 3
*/
int main()
{
    LGraph G, MST;

    G = BuildGraph();
    MST = CreateGraph(G->NumV);

    printf("%d", Kruskal(G, MST));
    return 0;
}
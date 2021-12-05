#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^声明邻接矩阵
#define MaxVertexNum 1005
#define INFINITY 65535
#define ERROR -1
typedef int Vertex;
typedef int WeightType;
typedef int DataType;

//*边的定义
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

//*图结点的定义
typedef struct MGNode *PtrToMGNode;
struct MGNode
{
    int NumV;
    int NumE;
    WeightType G[MaxVertexNum][MaxVertexNum]; //&邻接矩阵
};
typedef PtrToMGNode MGraph; //&以邻接矩阵方式存储的图类型

//^声明邻接表
//*邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

//*顶点表头结点的定义
typedef struct VNode
{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

//*图结点的定义
typedef struct LGNode *PtrToLGNode;
struct LGNode
{
    int NumV;
    int NumE;
    AdjList G;
};
typedef PtrToLGNode LGraph; //&以邻接表方式存储的图类型

//^邻接矩阵方法
//*初始化一个有VertexNum个顶点但没有边的图
MGraph CreateMGraph(int VertexNum)
{
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct MGNode));
    Graph->NumV = VertexNum;
    Graph->NumE = 0;

    for (V = 0; V < Graph->NumV; V++)
        for (W = 0; W < Graph->NumV; W++)
            Graph->G[V][W] = INFINITY;

    return Graph;
}

//*添加一条邻接矩阵的边
void InsertMGraphEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight; //&插入边<V1,V2>
    Graph->G[E->V2][E->V1] = E->Weight; //&若是无向图，还要插入边<V2,V1>
}

//*创建一个邻接矩阵
MGraph BuildMGraph()
{
    MGraph Graph;
    Edge E;
    int NumV, i;

    scanf("%d", &NumV);
    Graph = CreateMGraph(NumV);

    scanf("%d", &(Graph->NumE));
    if (Graph->NumE != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        //&读入边，格式为“起点 终点 权值”，插入邻接矩阵
        for (i = 0; i < Graph->NumE; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            E->V1--;
            E->V2--;
            InsertMGraphEdge(Graph, E);
        }
    }

    return Graph;
}

//^邻接表方法
//*初始化一个有VertexNum个顶点但没有边的图
LGraph CreateLGraph(int VertexNum)
{
    LGraph Graph;
    Vertex V;

    Graph = (LGraph)malloc(sizeof(struct LGNode));
    Graph->NumV = VertexNum;
    Graph->NumE = 0;

    for (V = 0; V < Graph->NumV; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

//*添加一条邻接表的边（按照从小到大的顺序插入）
void InsertLGraphEdge(LGraph Graph, Edge E)
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

//^题目方法
//*返回未被收录顶点中dist最小者
Vertex FindMinDist(MGraph Graph, WeightType dist[])
{
    Vertex MinV, V;
    WeightType MinDist;

    MinDist = INFINITY;
    for (V = 0; V < Graph->NumV; V++)
    {
        if (dist[V] != 0 && dist[V] < MinDist)
        {
            MinDist = dist[V];
            MinV = V;
        }
    }

    if (MinDist < INFINITY)
        return MinV;
    else
        return ERROR;
}

//*Prim算法，返回最小权重和
WeightType Prim(MGraph Graph, LGraph MST)
{
    WeightType dist[MaxVertexNum], totalWeight;
    Vertex parent[MaxVertexNum], V, W;
    int VCount;
    Edge E;

    for (V = 0; V < Graph->NumV; V++)
    {
        dist[V] = Graph->G[0][V];
        parent[V] = 0;
    }
    totalWeight = 0;
    VCount = 0;

    E = (Edge)malloc(sizeof(struct ENode));

    dist[0] = 0;
    VCount++;
    parent[0] = -1;

    while (true)
    {
        V = FindMinDist(Graph, dist);
        if (V == ERROR)
            break;

        E->V1 = parent[V];
        E->V2 = V;
        E->Weight = dist[V];
        InsertLGraphEdge(MST, E);

        totalWeight += dist[V];
        dist[V] = 0;
        VCount++;

        for (W = 0; W < Graph->NumV; W++)
        {
            if (dist[W] != 0 && Graph->G[V][W] < INFINITY)
            {
                if (Graph->G[V][W] < dist[W])
                {
                    dist[W] = Graph->G[V][W];
                    parent[W] = V;
                }
            }
        }
    }

    if (VCount < Graph->NumV)
        return ERROR;
    else
        return totalWeight;
}

int main()
{
    MGraph G = BuildMGraph();
    LGraph MST = CreateLGraph(G->NumV);
    printf("%d", Prim(G, MST));
    return 0;
}
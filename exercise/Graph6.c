#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^声明邻接矩阵
#define MaxVertexNum 505
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
    WeightType Weight1;
    WeightType Weight2;
};
typedef PtrToENode Edge;

//*图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int NumV;
    int NumE;
    Vertex Source;
    Vertex Destination;
    WeightType G1[MaxVertexNum][MaxVertexNum];
    WeightType G2[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph; //&以邻接矩阵方式存储的图类型

//^邻接矩阵方法
//*初始化一个有VertexNum个顶点但没有边的图
MGraph CreateGraph(int VertexNum)
{
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->NumV = VertexNum;
    Graph->NumE = 0;

    for (V = 0; V < Graph->NumV; V++)
        for (W = 0; W < Graph->NumV; W++)
        {
            Graph->G1[V][W] = INFINITY;
            Graph->G2[V][W] = INFINITY;
        }

    return Graph;
}

//*添加一条边
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G1[E->V1][E->V2] = E->Weight1;
    Graph->G1[E->V2][E->V1] = E->Weight1;
    Graph->G2[E->V1][E->V2] = E->Weight2;
    Graph->G2[E->V2][E->V1] = E->Weight2;
}

//*创建一个邻接矩阵
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int NumV, i;

    scanf("%d", &NumV);
    Graph = CreateGraph(NumV);

    scanf("%d %d %d", &(Graph->NumE), &(Graph->Source), &(Graph->Destination));
    if (Graph->NumE != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        //&读入边，格式为“起点 终点 权值1(长度) 权值2(费用)”，插入邻接矩阵
        for (i = 0; i < Graph->NumE; i++)
        {
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->Weight1, &E->Weight2);
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}

//*返回未被收录顶点中dist最小者
Vertex FindMinDist(MGraph Graph, WeightType dist[], Vertex collected[])
{
    Vertex MinV, V;
    WeightType MinDist;

    MinDist = INFINITY;
    for (V = 0; V < Graph->NumV; V++)
    {
        if (collected[V] == false && dist[V] < MinDist)
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

//*计算源点到temp1的花费，经过temp2
WeightType CalCost(MGraph Graph, Vertex path[], Vertex temp1, Vertex temp2)
{
    WeightType totalCost = 0;
    do
    {
        totalCost += Graph->G2[temp1][temp2];
        temp1 = temp2;
        temp2 = path[temp2];
    } while (temp1 != Graph->Source);
    return totalCost;
}

void Dijkstra(MGraph Graph, WeightType dist[], Vertex path[], WeightType cost[])
{
    Vertex collected[MaxVertexNum];
    Vertex V, W;

    //&初始化
    for (V = 0; V < Graph->NumV; V++)
    {
        collected[V] = false;
        dist[V] = Graph->G1[Graph->Source][V];
        cost[V] = Graph->G2[Graph->Source][V];
        if (dist[V] < INFINITY)
            path[V] = Graph->Source;
        else
            path[V] = -1;
    }
    dist[Graph->Source] = 0;
    collected[Graph->Source] = true;

    while (true)
    {
        V = FindMinDist(Graph, dist, collected);
        if (V == ERROR)
            break;
        collected[V] = true;
        for (W = 0; W < Graph->NumV; W++)
        {
            if (Graph->G1[V][W] < INFINITY && collected[W] == false)
            {
                if (dist[V] + Graph->G1[V][W] < dist[W])
                {
                    dist[W] = dist[V] + Graph->G1[V][W];
                    cost[W] = CalCost(Graph, path, W, V);
                    path[W] = V;
                }
                //&最短路径相同时，计算花费最少的路径
                else if (dist[V] + Graph->G1[V][W] == dist[W])
                {
                    WeightType totalCost1, totalCost2;
                    totalCost1 = CalCost(Graph, path, W, path[W]);
                    totalCost2 = CalCost(Graph, path, W, V);
                    if (totalCost2 < totalCost1)
                    {
                        path[W] = V;
                        cost[W] = totalCost2;
                    }
                }
            }
        }
    }
}

int main()
{
    Vertex path[MaxVertexNum];
    WeightType dist[MaxVertexNum], cost[MaxVertexNum];
    MGraph G = BuildGraph();
    Dijkstra(G, dist, path, cost);
    printf("%d %d", dist[G->Destination], cost[G->Destination]);
    return 0;
}
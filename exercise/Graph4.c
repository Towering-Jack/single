#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^声明邻接矩阵
#define MaxVertexNum 100
#define INFINITY 65535
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
typedef struct GNode *PtrToGNode;
struct GNode
{
    int NumV;
    int NumE;
    WeightType G[MaxVertexNum][MaxVertexNum]; //&邻接矩阵
};
typedef PtrToGNode MGraph; //&以邻接矩阵方式存储的图类型

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
            Graph->G[V][W] = INFINITY;

    return Graph;
}

//*添加一条边
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight; //&插入边<V1,V2>
    Graph->G[E->V2][E->V1] = E->Weight; //&若是无向图，还要插入边<V2,V1>
}

//*创建一个邻接矩阵
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int NumV, i;

    scanf("%d", &NumV);
    Graph = CreateGraph(NumV);

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
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}

void Floyd(MGraph Graph, WeightType D[][MaxVertexNum])
{
    Vertex i, j, k;

    //&初始化为邻接矩阵
    for (i = 0; i < Graph->NumV; i++)
        for (j = 0; j < Graph->NumV; j++)
            D[i][j] = Graph->G[i][j];

    for (k = 0; k < Graph->NumV; k++)
        for (i = 0; i < Graph->NumV; i++)
            for (j = 0; j < Graph->NumV; j++)
                if (D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
}

WeightType FindMaxDist(WeightType D[][MaxVertexNum], Vertex i, int NumV)
{
    WeightType MaxDist;
    Vertex j;

    MaxDist = 0;
    for (j = 0; j < NumV; j++)
        if (i != j && D[i][j] > MaxDist)
            MaxDist = D[i][j];

    return MaxDist;
}

void FindAnimal(MGraph Graph)
{
    WeightType D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
    Vertex Animal, i;

    Floyd(Graph, D);

    MinDist = INFINITY;
    for (i = 0; i < Graph->NumV; i++)
    {
        MaxDist = FindMaxDist(D, i, Graph->NumV);
        if (MaxDist == INFINITY)
        {
            printf("0");
            return;
        }
        if (MinDist > MaxDist)
        {
            MinDist = MaxDist;
            Animal = i + 1;
        }
    }
    printf("%d %d", Animal, MinDist);
}

int main()
{
    MGraph G = BuildGraph();
    FindAnimal(G);
    return 0;
}
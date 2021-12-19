#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^ ---------------声明邻接矩阵--------------- ^//
#define MaxVertexNum 100
#define INFINITY 65535
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

//~ 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int NumV;
    int NumE;
    WeightType G[MaxVertexNum][MaxVertexNum]; //&邻接矩阵
    // DataType Data[MaxVertexNum];           //&存顶点的数据，可省略
};
typedef PtrToGNode MGraph; //&以邻接矩阵方式存储的图类型
//? 邻接矩阵声明结束

//^ ---------------声明链队列--------------- ^//
typedef Vertex ElemTypeQ;
typedef struct QNode *PtrToQNode;
struct QNode
{
    ElemTypeQ data;
    PtrToQNode next;
};
typedef PtrToQNode Position;
typedef struct Queue
{
    Position front, rear; //& 队列的头、尾指针
    int length;
} * Queue;

Queue CreateQueue();
void AddQ(Queue PtrQ, ElemTypeQ X);
bool DeleteQ(Queue PtrQ, ElemTypeQ *frontElem);

//* 创建空的链队列
Queue CreateQueue()
{
    Queue PtrQ;

    PtrQ = (Queue)malloc(sizeof(struct Queue));
    PtrQ->front = PtrQ->rear = NULL;
    PtrQ->length = 0;
    return PtrQ;
}

//* 入队
void AddQ(Queue PtrQ, ElemTypeQ X)
{
    PtrToQNode newNode;

    newNode = (PtrToQNode)malloc(sizeof(struct QNode));
    newNode->data = X;
    newNode->next = NULL;
    if (PtrQ->front == NULL)
        PtrQ->front = PtrQ->rear = newNode;
    else
    {
        PtrQ->rear->next = newNode;
        PtrQ->rear = newNode;
    }
    PtrQ->length++;
}

//* 出队
bool DeleteQ(Queue PtrQ, ElemTypeQ *frontElem)
{
    Position frontCell;

    if (PtrQ->length == 0)
        return false;

    frontCell = PtrQ->front;
    *frontElem = frontCell->data;
    PtrQ->front = frontCell->next;
    free(frontCell);
    PtrQ->length--;
    return true;
}
//? 链队列声明结束

MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildGraph();

void DFS(MGraph Graph, Vertex V, bool visited[]);
void DFSTraverse(MGraph Graph);
void BFSTraverse(MGraph Graph);

Vertex FindMinDist(MGraph Graph, WeightType dist[], bool collected[]);
bool Dijkstra(MGraph Graph, WeightType dist[], Vertex path[], Vertex S);
bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum]);

//* 初始化一个有VertexNum个顶点但没有边的图
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

//* 添加一条边
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight; //&插入边<V1,V2>
    Graph->G[E->V2][E->V1] = E->Weight; //&若是无向图，还要插入边<V2,V1>
}

//* 创建一个邻接矩阵
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int NumV;
    Vertex i;

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
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}

//* DFS核心递归函数
void DFS(MGraph Graph, Vertex V, bool visited[])
{
    Vertex W;

    visited[V] = true;
    printf("%d ", V);

    for (W = 0; W < Graph->NumV; W++)
        if (Graph->G[V][W] < INFINITY && !visited[W])
            DFS(Graph, W, visited);
}

//* DFS算法
void DFSTraverse(MGraph Graph)
{
    Vertex V;
    bool visited[MaxVertexNum]; //&访问数组

    for (V = 0; V < Graph->NumV; V++)
        visited[V] = false;

    for (V = 0; V < Graph->NumV; V++)
        if (!visited[V])
            DFS(Graph, V, visited);

    printf("\n");
}

//* BFS算法
void BFSTraverse(MGraph Graph)
{
    Vertex V, W, i;
    Queue Q;
    bool visited[MaxVertexNum];

    Q = CreateQueue();
    for (V = 0; V < Graph->NumV; V++)
        visited[V] = false;

    for (i = 0; i < Graph->NumV; i++)
    {
        V = i;
        if (!visited[V])
        {
            visited[V] = true;
            printf("%d ", V);
            AddQ(Q, V);

            while (Q->length) //&队列不空
            {
                DeleteQ(Q, &V);
                for (W = 0; W < Graph->NumV; W++)
                {
                    if (Graph->G[V][W] < INFINITY && !visited[W])
                    {
                        visited[W] = true;
                        printf("%d ", W);
                        AddQ(Q, W);
                    }
                }
            }
        }
    }
    printf("\n");
}

//* 返回未被收录顶点中dist最小者
Vertex FindMinDist(MGraph Graph, WeightType dist[], bool collected[])
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

//* 单源最短路径Dijkstra算法
bool Dijkstra(MGraph Graph, WeightType dist[], Vertex path[], Vertex S)
{
    bool collected[MaxVertexNum];
    Vertex V, W;

    for (V = 0; V < Graph->NumV; V++)
    {
        collected[V] = false;
        dist[V] = Graph->G[S][V];
        if (dist[V] < INFINITY)
            path[V] = S;
        else
            path[V] = -1;
    }

    dist[S] = 0;
    collected[S] = true;
    while (true)
    {
        V = FindMinDist(Graph, dist, collected);
        if (V == ERROR)
            break;

        collected[V] = true;
        for (W = 0; W < Graph->NumV; W++)
        {
            if (collected[W] == false && Graph->G[V][W] < INFINITY)
            {
                if (Graph->G[V][W] < 0) //& 若有负边
                    return false;       //& 不能正确解决，返回错误标记

                if (dist[V] + Graph->G[V][W] < dist[W]) //& 若收录V使得dist[W]变小
                {
                    dist[W] = dist[V] + Graph->G[V][W];
                    path[W] = V;
                }
            }
        }
    }

    return true;
}

//* 多源最短路径Floyd算法
bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
    Vertex i, j, k;

    for (i = 0; i < Graph->NumV; i++)
        for (j = 0; j < Graph->NumV; j++)
        {
            D[i][j] = Graph->G[i][j];
            path[i][j] = -1;
        }

    for (k = 0; k < Graph->NumV; k++)
        for (i = 0; i < Graph->NumV; i++)
            for (j = 0; j < Graph->NumV; j++)
                if (D[i][k] + D[k][j] < D[i][j] && i != j)
                {
                    D[i][j] = D[i][k] + D[k][j];

                    if (i == j && D[i][j] < 0) //& 若发现负值圈
                        return false;          //& 不能正确解决，返回错误标记

                    path[i][j] = k;
                }

    return true;
}

/*
~ 测试数据:
5 6
0 1 1
1 3 2
0 3 4
0 2 2
2 3 1
2 4 1
*/
//* 测试函数
int main()
{

    MGraph G;
    Vertex path[MaxVertexNum], path2[MaxVertexNum][MaxVertexNum], i, j;
    WeightType dist[MaxVertexNum], D[MaxVertexNum][MaxVertexNum];

    G = BuildGraph();
    printf("\n");

    DFSTraverse(G);
    BFSTraverse(G);
    printf("\n");

    Dijkstra(G, dist, path, 1);
    for (i = 0; i < G->NumV; i++)
        printf("%d\t%5d %5d\n", i, dist[i], path[i]);
    printf("\n");

    Floyd(G, D, path2);
    for (i = 0; i < G->NumV; i++)
    {
        printf("%d\t", i);
        for (j = 0; j < G->NumV; j++)
            printf("%5d %5d  ", D[i][j], path2[i][j]);

        printf("\b\n");
    }

    return 0;
}
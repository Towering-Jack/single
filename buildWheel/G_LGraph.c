#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^ ---------------声明邻接表--------------- ^//
#define MaxVertexNum 100
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
//? 邻接表声明结束

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

LGraph CreateGraph(int VertexNum);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildGraph();

void DFS(LGraph Graph, Vertex V, bool *visited);
void DFSTraverse(LGraph Graph);
void BFSTraverse(LGraph Graph);

void Unweighted(LGraph Graph, WeightType dist[], Vertex path[], Vertex S);

bool TopSort(LGraph Graph, Vertex TopOrder[], WeightType MaxWeight[]);

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

//* DFS核心递归函数
void DFS(LGraph Graph, Vertex V, bool *visited)
{
    PtrToAdjVNode N;

    visited[V] = true;
    printf("%d ", V);

    N = Graph->G[V].FirstEdge;
    while (N)
    {
        if (!visited[N->AdjV])
            DFS(Graph, N->AdjV, visited);

        N = N->Next;
    }
}

//* DFS算法
void DFSTraverse(LGraph Graph)
{
    Vertex V;
    bool visited[MaxVertexNum];

    for (V = 0; V < Graph->NumV; V++)
        visited[V] = false;

    for (V = 0; V < Graph->NumV; V++)
        if (!visited[V])
            DFS(Graph, V, visited);

    printf("\n");
}

//* BFS算法
void BFSTraverse(LGraph Graph)
{
    int V, W;
    PtrToAdjVNode N;
    Queue Q;
    bool visited[MaxVertexNum];

    for (V = 0; V < Graph->NumV; V++)
        visited[V] = false;
    Q = CreateQueue();

    for (V = 0; V < Graph->NumV; V++)
    {
        W = V;
        if (!visited[W])
        {
            visited[W] = true;
            printf("%d ", W);
            AddQ(Q, W);

            while (Q->length) //&队列不空
            {
                DeleteQ(Q, &W);
                N = Graph->G[W].FirstEdge;
                while (N)
                {
                    if (!visited[N->AdjV])
                    {
                        visited[N->AdjV] = true;
                        printf("%d ", N->AdjV);
                        AddQ(Q, N->AdjV);
                    }
                    N = N->Next;
                }
            }
        }
    }
    printf("\n");
}

//* 无权图的单源最短路算法
void Unweighted(LGraph Graph, WeightType dist[], Vertex path[], Vertex S)
{
    Queue Q;
    Vertex V;
    PtrToAdjVNode W;

    Q = CreateQueue();
    for (V = 0; V < Graph->NumV; V++)
    {
        dist[V] = -1;
        path[V] = -1;
    }

    dist[S] = 0;
    AddQ(Q, S);
    while (Q->length)
    {
        DeleteQ(Q, &V);
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (dist[W->AdjV] == -1) //& 若W->AdjV未被访问过
            {
                dist[W->AdjV] = dist[V] + 1; //& W->AdjV到S的距离更新
                path[W->AdjV] = V;           //& 将V记录在S到W->AdjV的路径上
                AddQ(Q, W->AdjV);
            }
        }
    }
}

//* 拓扑排序（有向图，需注释掉插入第二条边的代码）
bool TopSort(LGraph Graph, Vertex TopOrder[], WeightType MaxWeight[])
{
    int InDegree[MaxVertexNum], cnt;
    Vertex V;
    PtrToAdjVNode W;
    Queue Q;

    Q = CreateQueue();
    for (V = 0; V < Graph->NumV; V++)
    {
        InDegree[V] = 0;
        MaxWeight[V] = 0;
    }

    //& 遍历图，得到Indegree[]
    for (V = 0; V < Graph->NumV; V++)
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            InDegree[W->AdjV]++;

    //& 将所有入度为0的顶点入列
    for (V = 0; V < Graph->NumV; V++)
        if (InDegree[V] == 0)
            AddQ(Q, V);

    cnt = 0;
    while (DeleteQ(Q, &V))
    {
        TopOrder[cnt++] = V; //& 将弹出的顶点存入结果序列

        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (--InDegree[W->AdjV] == 0)
                AddQ(Q, W->AdjV);

            if (MaxWeight[W->AdjV] < MaxWeight[V] + W->Weight)
                MaxWeight[W->AdjV] = MaxWeight[V] + W->Weight;
        }
    }

    if (cnt != Graph->NumV)
        return false;
    else
        return true;
}

/*
~ 测试数据:
9 12
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
5 4 0
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
*/
//* 测试函数
int main()
{
    LGraph G;
    Vertex V, TopOrder[MaxVertexNum];
    WeightType MaxWeight[MaxVertexNum];

    G = BuildGraph();
    printf("\n");

    DFSTraverse(G);
    BFSTraverse(G);

    if (TopSort(G, TopOrder, MaxWeight))
        for (V = 0; V < G->NumV; V++)
            printf("%d %d\n", TopOrder[V], MaxWeight[V]);
    else
        printf("Impossible");

    return 0;
}
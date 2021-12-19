#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^ ---------------定义邻接表--------------- ^//
#define MaxVertexNum 105
#define MaxTime 65535
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
void BuildGraph(LGraph Graph1, LGraph Graph2);

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

//* 添加一条边
void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    //&插入边<V1, V2>
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;

    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
}

//* 创建两个邻接图
void BuildGraph(LGraph Graph1, LGraph Graph2)
{
    Edge E;
    WeightType temp;
    int i;

    scanf("%d", &(Graph1->NumE));
    if (Graph1->NumE != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        //&读入边，格式为“起点 终点 权值”，插入邻接表
        for (i = 0; i < Graph1->NumE; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(Graph1, E);

            temp = E->V1;
            E->V1 = E->V2;
            E->V2 = temp;
            InsertEdge(Graph2, E);
        }
    }
}
//? 邻接表定义结束

//^ ---------------定义链队列--------------- ^//
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
//? 链队列定义结束

//^ ---------------声明关键路径--------------- ^//
typedef struct VertexTime
{
    WeightType EarlyTime, LastTime;
} VertexTime;

//* 拓扑排序，用于关键路径
bool TopSort_CriticalPath(LGraph Graph1, LGraph Graph2, Vertex TopOrder[], VertexTime VTime[])
{
    int InDegree[MaxVertexNum], OutDegree[MaxVertexNum], cnt, totalWeight;
    Vertex V, LastV;
    PtrToAdjVNode W1, W2;
    Queue Q1, Q2;

    Q1 = CreateQueue();
    Q2 = CreateQueue();
    for (V = 0; V < Graph1->NumV; V++)
    {
        InDegree[V] = 0;
        OutDegree[V] = 0;
        VTime[V].EarlyTime = 0;
        VTime[V].LastTime = MaxTime;
    }

    //& 遍历图，得到InDegree[]和OutDegree[]
    for (V = 0; V < Graph1->NumV; V++)
    {
        for (W1 = Graph1->G[V].FirstEdge; W1; W1 = W1->Next)
            InDegree[W1->AdjV]++;
        for (W2 = Graph2->G[V].FirstEdge; W2; W2 = W2->Next)
            OutDegree[W2->AdjV]++;
    }

    //& 将所有入度和出度为0的顶点入列
    for (V = 0; V < Graph1->NumV; V++)
    {
        if (InDegree[V] == 0)
            AddQ(Q1, V);
        if (OutDegree[V] == 0)
            AddQ(Q2, V);
    }

    cnt = 0;
    while (DeleteQ(Q1, &V))
    {
        TopOrder[cnt++] = V; //& 将弹出的顶点存入结果序列

        for (W1 = Graph1->G[V].FirstEdge; W1; W1 = W1->Next)
        {
            if (--InDegree[W1->AdjV] == 0)
                AddQ(Q1, W1->AdjV);
            if (VTime[W1->AdjV].EarlyTime < VTime[V].EarlyTime + W1->Weight)
                VTime[W1->AdjV].EarlyTime = VTime[V].EarlyTime + W1->Weight;
        }
    }
    if (cnt != Graph1->NumV)
        return false;

    //& 下面进行倒推求出LastTime
    totalWeight = 0;
    for (V = 0; V < Graph1->NumV; V++)
        if (VTime[V].EarlyTime > totalWeight)
        {
            totalWeight = VTime[V].EarlyTime;
            LastV = V;
        }
    printf("%d", totalWeight);

    VTime[LastV].LastTime = totalWeight;
    while (DeleteQ(Q2, &V))
    {
        for (W2 = Graph2->G[V].FirstEdge; W2; W2 = W2->Next)
        {
            if (--OutDegree[W2->AdjV] == 0)
                AddQ(Q2, W2->AdjV);
            if (VTime[W2->AdjV].LastTime > VTime[V].LastTime - W2->Weight)
                VTime[W2->AdjV].LastTime = VTime[V].LastTime - W2->Weight;
        }
    }
    return true;
}

//* 测试函数
/*
~ 测试数据:
7 8
0 1 4
0 2 3
1 3 5
2 3 3
3 4 1
3 5 6
4 6 5
5 6 2
*/
int main()
{
    LGraph G1, G2;
    Vertex V, TopOrder[MaxVertexNum];
    VertexTime VTime[MaxVertexNum];
    PtrToAdjVNode W;
    int NumV;

    scanf("%d", &NumV);
    G1 = CreateGraph(NumV);
    G2 = CreateGraph(NumV);
    BuildGraph(G1, G2);

    if (TopSort_CriticalPath(G1, G2, TopOrder, VTime))
    {
        for (V = 0; V < G1->NumV; V++)
            for (W = G1->G[V].FirstEdge; W; W = W->Next)
                if (VTime[W->AdjV].LastTime - VTime[V].EarlyTime == W->Weight)
                    printf("\n%d->%d", V + 1, W->AdjV + 1);
    }
    else
        printf("0");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^----------邻接表定义----------^//
#define MaxVertexNum 105
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
typedef struct GNode *PtrToGNode;
struct GNode
{
    int NumV;
    int NumE;
    AdjList G;
};
typedef PtrToGNode LGraph; //&以邻接表方式存储的图类型

//*初始化一个有VertexNum个顶点但没有边的图
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

//*添加一条边（按照从小到大的顺序插入）
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
}

//*创建一个邻接图
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
//^----------邻接表定义结束----------^//

//^----------链队列定义----------^//
typedef Vertex ElemTypeQ;

//*队列中的结点
typedef struct QNode *QNode;
struct QNode
{
    ElemTypeQ data;
    QNode next;
};

//*队列主体（含头节点）
typedef QNode Position;
typedef struct Queue
{
    Position front, rear; //~队列的头、尾指针
} * Queue;

//*创建空队列
Queue CreateQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct Queue));
    QNode headNode = (QNode)malloc(sizeof(struct QNode));
    Q->front = Q->rear = headNode;
    headNode->data = 0; //~队列中元素的个数
    return Q;
}

//*入队
void AddQ(Queue Q, ElemTypeQ X)
{
    QNode s = (QNode)malloc(sizeof(struct QNode));
    s->data = X;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    Q->front->data++;
}

//*出队
bool DeleteQ(Queue Q, ElemTypeQ *frontElem)
{
    if (Q->front->data == 0)
        return false;
    Position frontCell = Q->front->next;
    *frontElem = frontCell->data;
    Q->front->next = frontCell->next;
    if (Q->rear == frontCell)
        Q->rear = Q->front;
    free(frontCell);
    Q->front->data--;
    return true;
}
//^----------链队列声明结束----------^//

//^----------题目方法----------^//
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

int main()
{
    LGraph G = BuildGraph();
    Vertex TopOrder[MaxVertexNum];
    WeightType MaxWeight[MaxVertexNum];
    WeightType w;

    w = 0;
    if (TopSort(G, TopOrder, MaxWeight))
    {
        for (int i = 0; i < G->NumV; i++)
        {
            if (MaxWeight[i] > w)
                w = MaxWeight[i];
        }
        printf("%d", w);
    }
    else
        printf("Impossible");
        
    return 0;
}
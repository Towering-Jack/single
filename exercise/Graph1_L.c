#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//^声明邻接表
#define MaxVertexNum 100
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
    DataType Data; //&可以省略
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

//^声明链队列
typedef int ElemTypeQ;
typedef int Status;
#define OK ((int)1)
#define ERROR ((int)0)

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

//^链队列方法
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
Status DeleteQ(Queue Q, ElemTypeQ *frontElem)
{
    if (Q->front->data == 0)
        return ERROR;
    Position frontCell = Q->front->next;
    *frontElem = frontCell->data;
    Q->front->next = frontCell->next;
    if (Q->rear == frontCell)
        Q->rear = Q->front;
    free(frontCell);
    Q->front->data--;
    return OK;
}

//^邻接表方法
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

//*创建一个邻接图
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    Vertex V;
    int NumV, i;

    scanf("%d", &NumV);
    Graph = CreateGraph(NumV);

    scanf("%d", &(Graph->NumE));
    if (Graph->NumE != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        //&读入边，格式为“起点 终点”，插入邻接表
        for (i = 0; i < Graph->NumE; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            E->Weight = 1; //&无向图权值设为1
            InsertEdge(Graph, E);
        }
    }

    //&如果顶点有数据的话，读入数据
    for (V = 0; V < Graph->NumV; V++)
        Graph->G[V].Data = V; //&无数据，直接初始化为数组下标

    return Graph;
}

//*DFS
void DFS(LGraph Graph, Vertex V, bool *visited)
{
    visited[V] = true;
    printf("%d ", Graph->G[V].Data);

    PtrToAdjVNode N;
    N = Graph->G[V].FirstEdge;
    while (N)
    {
        if (!visited[N->AdjV])
            DFS(Graph, N->AdjV, visited);
        N = N->Next;
    }
}

void DFSTraverse(LGraph Graph)
{
    Vertex V;
    bool visited[MaxVertexNum]; //&访问数组
    bool firstPrint = true;

    for (V = 0; V < Graph->NumV; V++)
        visited[V] = false;

    for (V = 0; V < Graph->NumV; V++)
        if (!visited[V])
        {
            if (firstPrint)
            {
                printf("{ ");
                firstPrint = false;
            }
            else
                printf("\n{ ");

            DFS(Graph, V, visited);
            printf("}");
        }
}

//*BFS
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
            printf("\n{ ");
            visited[W] = true;
            printf("%d ", Graph->G[W].Data);
            AddQ(Q, W);

            while (Q->front->data) //&队列不空
            {
                DeleteQ(Q, &W);
                N = Graph->G[W].FirstEdge;
                while (N)
                {
                    if (!visited[N->AdjV])
                    {
                        visited[N->AdjV] = true;
                        printf("%d ", Graph->G[N->AdjV].Data);
                        AddQ(Q, N->AdjV);
                    }
                    N = N->Next;
                }
            }
            printf("}");
        }
    }
}

int main()
{
    LGraph G = BuildGraph();
    DFSTraverse(G);
    BFSTraverse(G);
    return 0;
}
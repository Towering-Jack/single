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
    DataType Data[MaxVertexNum];              //&存顶点的数据，可省略
};
typedef PtrToGNode MGraph; //&以邻接矩阵方式存储的图类型

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
    Vertex V;
    int NumV, i;

    scanf("%d", &NumV);
    Graph = CreateGraph(NumV);

    scanf("%d", &(Graph->NumE));
    if (Graph->NumE != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        //&读入边，格式为“起点 终点”，插入邻接矩阵
        for (i = 0; i < Graph->NumE; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            E->Weight = 1; //&无向图权值设为1
            InsertEdge(Graph, E);
        }
    }

    //&如果顶点有数据的话，读入数据
    for (V = 0; V < Graph->NumV; V++)
        Graph->Data[V] = V;

    return Graph;
}

//*DFS
void DFS(MGraph Graph, Vertex V, bool *visited)
{
    visited[V] = true;
    printf("%d ", Graph->Data[V]);

    Vertex W;
    for (W = 0; W < Graph->NumV; W++)
        if (Graph->G[V][W] == 1 && !visited[W])
            DFS(Graph, W, visited);
}

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

//*BFS
void BFSTraverse(MGraph Graph)
{
    Vertex V, W;
    Queue Q;
    bool visited[MaxVertexNum];

    for (V = 0; V < Graph->NumV; V++)
        visited[V] = false;
    Q = CreateQueue();

    for (int i = 0; i < Graph->NumV; i++)
    {
        V = i;
        if (!visited[V])
        {
            visited[V] = true;
            printf("%d ", Graph->Data[V]);
            AddQ(Q, V);

            while (Q->front->data) //&队列不空
            {
                DeleteQ(Q, &V);
                for (W = 0; W < Graph->NumV; W++)
                {
                    if (Graph->G[V][W] == 1 && !visited[W])
                    {
                        visited[W] = true;
                        printf("%d ", Graph->Data[W]);
                        AddQ(Q, W);
                    }
                }
            }
        }
    }
    printf("\n");
}

int main()
{
    MGraph G = BuildGraph();
    DFSTraverse(G);
    BFSTraverse(G);
    return 0;
}
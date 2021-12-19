#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXSIZE 105
#define infinity 65535
typedef int Status;
#define OK ((int)1)
#define ERROR ((int)0)

//^声明MyGraph
typedef struct
{
    int abscissa;
    int ordinate;
} coordinate;

typedef struct
{
    int croNum, jumpDist;
    coordinate Data[MAXSIZE];
} MyGraph;
typedef MyGraph *Graph;

//^声明链栈
typedef int ElemTypeS;
typedef struct SNode *Stack;
struct SNode
{
    ElemTypeS data;
    Stack next;
};

//^声明链队列
typedef int ElemTypeQ;
//&队列中的结点
typedef struct QNode *QNode;
struct QNode
{
    ElemTypeQ data;
    QNode next;
};
//&队列(含头结点)
typedef QNode Position;
typedef struct Queue
{
    Position front, rear; //~队列的头、尾指针
} * Queue;

//^链栈方法
//*创建空链栈（创建头结点）
Stack CreateStack()
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->data = 0; //~栈中元素的个数
    S->next = NULL;
    return S;
}

//*入栈（插入链头）
void Push(Stack S, ElemTypeS X)
{
    Stack n = (Stack)malloc(sizeof(struct SNode));
    n->data = X;
    n->next = S->next;
    S->next = n;
    S->data++;
}

//*出栈（从链头删除）
Status Pop(Stack S, ElemTypeS *frontElem)
{
    if (S->data == 0)
        return ERROR;
    Stack frontCell = S->next;
    *frontElem = frontCell->data;
    S->next = frontCell->next;
    free(frontCell);
    S->data--;
    return OK;
}

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

//^本题方法
bool IfJump(Graph G, coordinate James, int index)
{
    int abscissa, ordinate;
    double dismeter;

    abscissa = abs(James.abscissa - G->Data[index].abscissa);
    ordinate = abs(James.ordinate - G->Data[index].ordinate);
    dismeter = sqrt(pow(abscissa, 2) + pow(ordinate, 2));

    if (James.abscissa == 0 && James.ordinate == 0)
        return ((double)G->jumpDist + 7.5) >= dismeter ? true : false;
    else
        return G->jumpDist >= dismeter ? true : false;
}

bool IfFirstEscape(double jumpMeter)
{
    return jumpMeter >= 42.5 ? true : false;
}

bool IfEscape(coordinate James, int jumpMeter)
{
    return ((50 - abs(James.abscissa) <= jumpMeter) ||
            (50 - abs(James.ordinate) <= jumpMeter));
}

void FindMinDist(Graph G, int dist[], int path[], int S)
{
    Queue Q;
    int i, V;
    coordinate James;

    Q = CreateQueue();
    James = G->Data[0];
    dist[S] = 0;
    AddQ(Q, S);

    while (Q->front->data)
    {
        DeleteQ(Q, &V);
        James = G->Data[V];
        for (i = 1; i <= G->croNum; i++)
        {
            if (IfJump(G, James, i) && dist[i] == -1)
            {
                dist[i] = dist[V] + 1;
                path[i] = V;
                AddQ(Q, i);
            }
        }
    }
}

double JumpDist(coordinate data)
{
    return sqrt(pow(data.abscissa, 2) + pow(data.ordinate, 2));
}

int JudgeFirstMinDist(Graph G, int minDist, int dist[], int path[])
{
    int i, j, V;
    double firstJumpDist;

    firstJumpDist = (double)infinity;
    for (i = 1; i <= G->croNum; i++)
    {
        if (dist[i] == minDist && IfEscape(G->Data[i], G->jumpDist))
        {
            for (j = i; dist[j] != 1; j = path[j])
                continue;
            if (JumpDist(G->Data[j]) < firstJumpDist)
            {
                V = i;
                firstJumpDist = JumpDist(G->Data[j]);
            }
        }
    }
    return V;
}

int main()
{
    int i, V, minDist, dist[MAXSIZE], path[MAXSIZE];
    Graph G;

    G = (Graph)malloc(sizeof(MyGraph));
    G->Data[0].abscissa = 0;
    G->Data[0].ordinate = 0;
    dist[0] = -1;
    path[0] = -1;

    scanf("%d %d", &G->croNum, &G->jumpDist);
    for (i = 1; i <= G->croNum; i++)
    {
        scanf("%d %d", &G->Data[i].abscissa, &G->Data[i].ordinate);
        dist[i] = -1;
        path[i] = -1;
    }

    if (IfFirstEscape((double)G->jumpDist))
    {
        printf("1");
        return 0;
    }

    FindMinDist(G, dist, path, 0);
    minDist = infinity;
    for (i = 1; i <= G->croNum; i++)
        if (path[i] != -1 && dist[i] < minDist && IfEscape(G->Data[i], G->jumpDist))
            minDist = dist[i];

    V = JudgeFirstMinDist(G, minDist, dist, path);

    if (minDist == infinity)
    {
        printf("0");
        return 0;
    }

    printf("%d", minDist + 1);
    Stack S;
    S = CreateStack();
    for (i = V; dist[i] != 0; i = path[i])
        Push(S, i);
    while (S->data)
    {
        Pop(S, &i);
        printf("\n%d %d", G->Data[i].abscissa, G->Data[i].ordinate);
    }

    return 0;
}
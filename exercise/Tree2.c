#include <stdio.h>
#include <stdlib.h>

typedef int Tree;
struct TNode
{
    Tree left;
    Tree right;
} tree[10];

//^声明链队列
typedef int Status;
#define OK ((int)1)
#define ERROR ((int)0)

typedef Tree ElemTypeQ;
//?队列中的结点
typedef struct QNode *QNode;
struct QNode
{
    ElemTypeQ data;
    QNode next;
};
//?队列头结点
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

//*层序遍历
void LevelOrderTraversal(Tree T, int leavesN)
{
    Queue Q;
    if (T == -1)
        return;
    Q = CreateQueue();
    AddQ(Q, T);
    while (Q->front->data)
    {
        DeleteQ(Q, &T);
        if (tree[T].left == -1 && tree[T].right == -1)
        {
            printf("%d", T);
            if (leavesN--)
                printf(" ");
        }
        if (tree[T].left != -1)
            AddQ(Q, tree[T].left);
        if (tree[T].right != -1)
            AddQ(Q, tree[T].right);
    }
}

int main()
{
    int N, i;
    scanf("%d", &N);
    int checkRoot[N], checkLeaves[N];
    for (i = 0; i < N; i++)
    {
        checkRoot[i] = 0;
        checkLeaves[i] = 0;
    }
    char cl, cr;
    for (i = 0; i < N; i++)
    {
        scanf("\n%c %c", &cl, &cr);
        if (cl != '-')
        {
            tree[i].left = cl - '0';
            checkRoot[tree[i].left] = 1;
        }
        else
            tree[i].left = -1;
        if (cr != '-')
        {
            tree[i].right = cr - '0';
            checkRoot[tree[i].right] = 1;
        }
        else
            tree[i].right = -1;
        if (cl == '-' && cr == '-')
            checkLeaves[i] = 1;
    }
    for (i = 0; i < N; i++)
        if (!checkRoot[i])
            break;
    Tree Root = i;
    int leavesN = 0;
    for (i = 0; i < N; i++)
        if (checkLeaves[i])
            leavesN++;
    LevelOrderTraversal(Root, leavesN-1);
    return 0;
}
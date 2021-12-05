#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXK 5
#define MAXM 100000

//*得分结点
typedef struct ScoreNode *PtrToScoreNode;
struct ScoreNode
{
    int ProblemID;
    int Score;
    PtrToScoreNode next;
};

//*每个人的得分情况
typedef struct VNode
{
    int valid;
    int TotalScore;
    int perfectlyN;
    PtrToScoreNode FirstScore;
} ScoreList[MAXN];

//^---------------桶排序---------------^//(稳定)
//&桶元素结点
typedef struct BNode *PtrToBNode;
struct BNode
{
    int key;
    PtrToBNode next;
};

//&桶头结点
struct HeadBNode
{
    PtrToBNode head, tail;
};
typedef struct HeadBNode *Bucket;

//*对perfectlyN进行排序
void Bucket_Sort1(ScoreList A, int N, int Table[])
{
    Bucket B;
    PtrToBNode temp, p;
    int i;
    int max, min, CountNum;

    //&寻找最大值和最小值
    min = A[0].perfectlyN;
    max = A[0].perfectlyN;
    for (i = 0; i < N; i++)
    {
        if (A[i].perfectlyN < min)
            min = A[i].perfectlyN;
        if (A[i].perfectlyN > max)
            max = A[i].perfectlyN;
    }
    CountNum = max - min + 1;

    B = (Bucket)malloc(CountNum * sizeof(struct HeadBNode));
    for (i = 0; i < CountNum; i++)
        B[i].head = B[i].tail = NULL;

    for (i = 0; i < N; i++)
    {
        temp = (PtrToBNode)malloc(sizeof(struct BNode));
        temp->key = i; //&存入数组信息，此处存入数组下标
        temp->next = NULL;
        if (!B[A[i].perfectlyN - min].head)
        {
            B[A[i].perfectlyN - min].head = temp;
            B[A[i].perfectlyN - min].tail = temp;
        }
        else
        {
            B[A[i].perfectlyN - min].tail->next = temp;
            B[A[i].perfectlyN - min].tail = temp;
        }
    }

    int j;
    for (i = CountNum - 1, j = 0; i >= 0; i--)
    {
        if (B[i].head)
        {
            p = B[i].head;
            while (p)
            {
                Table[j++] = p->key;
                temp = p;
                p = p->next;
                free(temp);
            }
        }
    }
}

//*对totalScore进行排序
void Bucket_Sort2(ScoreList A, int N, int Table[])
{
    Bucket B;
    PtrToBNode temp, p;
    int i;
    int max, min, CountNum;

    //&寻找最大值和最小值
    min = A[0].TotalScore;
    max = A[0].TotalScore;
    for (i = 0; i < N; i++)
    {
        if (A[i].TotalScore < min)
            min = A[i].TotalScore;
        if (A[i].TotalScore > max)
            max = A[i].TotalScore;
    }
    CountNum = max - min + 1;

    B = (Bucket)malloc(CountNum * sizeof(struct HeadBNode));
    for (i = 0; i < CountNum; i++)
        B[i].head = B[i].tail = NULL;

    for (i = 0; i < N; i++)
    {
        temp = (PtrToBNode)malloc(sizeof(struct BNode));
        temp->key = Table[i]; //&存入数组信息，此处存入数组下标
        temp->next = NULL;
        if (!B[A[Table[i]].TotalScore - min].head)
        {
            B[A[Table[i]].TotalScore - min].head = temp;
            B[A[Table[i]].TotalScore - min].tail = temp;
        }
        else
        {
            B[A[Table[i]].TotalScore - min].tail->next = temp;
            B[A[Table[i]].TotalScore - min].tail = temp;
        }
    }

    int j;
    for (i = CountNum - 1, j = 0; i >= 0; i--)
    {
        if (B[i].head)
        {
            p = B[i].head;
            while (p)
            {
                Table[j++] = p->key;
                temp = p;
                p = p->next;
                free(temp);
            }
        }
    }
}
//~桶排序结束

/*
 *按照题号顺序插入得分信息
 *若得分为-1,将会转化为0插入
 *重复提交，将会取得分高的一次
 */
void InsertScore(ScoreList Data, int userID, PtrToScoreNode NewNode, int FullMark[])
{
    PtrToScoreNode p;

    userID--;
    p = Data[userID].FirstScore;

    //&判断提交是否有效（用户是否能打印）
    if (NewNode->Score == -1)
        NewNode->Score = 0; //&将得分转化为0插入
    else
        Data[userID].valid = 1;

    //&进行插入操作
    if (!p || NewNode->ProblemID < p->ProblemID)
    {
        //&插入表头
        NewNode->next = p;
        Data[userID].FirstScore = NewNode;
        Data[userID].TotalScore += NewNode->Score;
        //&判断是否为最佳答案
        if (NewNode->Score == FullMark[NewNode->ProblemID - 1])
            Data[userID].perfectlyN++;
    }
    else if (NewNode->ProblemID == p->ProblemID)
    {
        if (NewNode->Score > p->Score)
        {
            //&进行合并
            Data[userID].TotalScore += (NewNode->Score - p->Score);
            p->Score = NewNode->Score;
            //&判断是否为最佳答案
            if (NewNode->Score == FullMark[NewNode->ProblemID - 1])
                Data[userID].perfectlyN++;
        }

        free(NewNode);
        return;
    }
    else
    {
        while (p->next)
        {
            if (NewNode->ProblemID == p->next->ProblemID)
            {
                if (NewNode->Score > p->Score)
                {
                    //&进行合并
                    p->Score = NewNode->Score;
                    Data[userID].TotalScore += (NewNode->Score - p->Score);
                    //&判断是否为最佳答案
                    if (NewNode->Score == FullMark[NewNode->ProblemID - 1])
                        Data[userID].perfectlyN++;
                }

                free(NewNode);
                return;
            }

            if (NewNode->ProblemID < p->next->ProblemID)
                break; //&找到合适位置插入
            p = p->next;
        }
        NewNode->next = p->next;
        p->next = NewNode;
        Data[userID].TotalScore += NewNode->Score;
        //&判断是否为最佳答案
        if (NewNode->Score == FullMark[NewNode->ProblemID - 1])
            Data[userID].perfectlyN++;
    }
}

int main()
{
    int i, userID, rank, currentScore, currentProblem;
    int N, K, M;
    int FullMark[MAXK];
    ScoreList Data;
    PtrToScoreNode NewNode, p;
    int Table[MAXN];

    scanf("%d %d %d", &N, &K, &M);
    currentScore = 1;
    for (i = 0; i < K; i++)
    {
        scanf("%d", &FullMark[i]);
        currentScore += FullMark[i];
    }

    for (i = 0; i < N; i++)
    {
        Data[i].valid = 0;
        Data[i].TotalScore = 0;
        Data[i].perfectlyN = 0;
        Data[i].FirstScore = NULL;
        Table[i] = i;
    }

    for (i = 0; i < M; i++)
    {
        NewNode = (PtrToScoreNode)malloc(sizeof(struct ScoreNode));
        scanf("%d %d %d", &userID, &NewNode->ProblemID, &NewNode->Score);
        NewNode->next = NULL;
        InsertScore(Data, userID, NewNode, FullMark);
    }

    Bucket_Sort1(Data, N, Table);
    Bucket_Sort2(Data, N, Table);

    rank = 0;
    int cnt = 1;
    for (i = 0; i < N; i++)
    {
        if (Data[Table[i]].valid)
        {
            if (Data[Table[i]].TotalScore < currentScore)
            {
                rank += cnt;
                cnt = 1;
                currentScore = Data[Table[i]].TotalScore;
            }
            else
                cnt++;
            
            printf("%d %05d %d", rank, Table[i] + 1, Data[Table[i]].TotalScore);
            p = Data[Table[i]].FirstScore;
            currentProblem = 1;
            while (currentProblem <= K)
            {
                if (p)
                {
                    if (p->ProblemID == currentProblem)
                    {
                        printf(" %d", p->Score);
                        p = p->next;
                    }
                    else
                        printf(" -");
                    currentProblem++;
                }
                else
                {
                    printf(" -");
                    currentProblem++;
                }
            }
            printf("\n");
        }
    }

    return 0;
}
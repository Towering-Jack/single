#include <stdio.h>

#define MAXSIZE 100000

int N;
int A[MAXSIZE];

int Check(int Pos)
{
    int i;
    for (i = Pos; i < N; i++)
        if (A[i] != i)
            break;

    return i; //&未排好序,返回第一个排错位置的数组下标
              //&已排好序，返回N
}

int Find(int Num)
{
    for (int i = 0; i < N; i++)
        if (A[i] == Num)
            return i; //&返回Num所在的数组下标

    return -1; //&未找到
}

int Cycle(int Pos)
{
    int lastPos, cycleNum, nextPos;

    lastPos = Pos;
    cycleNum = 0;
    do
    {
        cycleNum++;
        nextPos = A[Pos];
        A[Pos] = Pos;
        Pos = nextPos;
    } while (Pos != lastPos);
    A[Pos] = Pos;

    return cycleNum;
}

int SwapSort()
{
    int times;
    int PosZero, PosI;

    times = 0;
    if ((PosZero = Find(0)) != 0)
    {
        times--;
        times += Cycle(PosZero);
    }
        
    PosI = 0;
    while ((PosI = Check(PosI)) < N)
    {
        times++;
        times += Cycle(PosI);
    }

    return times;
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    printf("%d", SwapSort());

    return 0;
    printf("\n");
    //213213
}
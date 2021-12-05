#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 114514
typedef long ElemType;

void Swap(ElemType *A, ElemType *B)
{
    ElemType temp;
    temp = *A;
    *A = *B;
    *B = temp;
}

//^---------------冒泡排序---------------^//(稳定)
void Bubble_Sort(ElemType A[], int N)
{
    int P, flag, i;
    for (P = N - 1; P > 0; P--)
    {
        flag = 0;
        for (i = 0; i < P; i++)
        {
            if (A[i] > A[i + 1])
            {
                Swap(&A[i], &A[i + 1]);
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}
//~冒泡排序结束

//^---------------插入排序---------------^//(稳定)
void Insertion_Sort(ElemType A[], int N)
{
    int P, i;
    ElemType temp;

    for (P = 1; P < N; P++)
    {
        temp = A[P];
        for (i = P; i > 0 && A[i - 1] > temp; i--)
            A[i] = A[i - 1];
        A[i] = temp;
    }
}
//~插入排序结束

//^---------------希尔排序---------------^//(不稳定)
void Shell_Sort(ElemType A[], int N)
{
    int Si, D, P, i;
    ElemType temp;

    int Sedgewick[] = {146305, 64769, 36289, 16001, 8929, 3905,
                       2161, 929, 505, 209, 109, 41, 19, 5, 1, 0};

    for (Si = 0; Sedgewick[Si] >= N; Si++)
        continue; //&初始的增量Sedgewick[Si]不能超过待排序列长度

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
    {
        for (P = D; P < N; P++) //&插入排序
        {
            temp = A[P];
            for (i = P; i >= D && A[i - D] > temp; i -= D)
                A[i] = A[i - D];
            A[i] = temp;
        }
    }
}
//~希尔排序结束

//^---------------选择排序---------------^//(不稳定)
void Selection_Sort(ElemType A[], int N)
{
    int i, j, minPosition;
    for (i = 0; i < N; i++)
    {
        for (j = i, minPosition = i; j < N; j++)
            if (A[j] < A[minPosition])
                minPosition = j;

        Swap(&A[i], &A[minPosition]);
    }
}
//~选择排序结束

//^---------------堆排序---------------^//(不稳定)
//*将N个元素的数组中以A[p]为根的子堆调整为最大堆
void PercDown(ElemType A[], int p, int N)
{
    int parent, child;
    ElemType X;

    X = A[p];
    for (parent = p; (parent * 2 + 1) < N; parent = child)
    {
        child = parent * 2 + 1;
        if ((child != N - 1) && (A[child] < A[child + 1]))
            child++;
        if (X >= A[child])
            break;
        else
            A[parent] = A[child];
    }
    A[parent] = X;
}

void Heap_Sort(ElemType A[], int N)
{
    int i;

    for (i = N / 2 - 1; i >= 0; i--) //&建立最大堆
        PercDown(A, i, N);

    for (i = N - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
    }
}
//~堆排序结束

//^---------------归并排序(递归实现)---------------^//(稳定)
//*将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
void Merge(ElemType A[], ElemType TempA[], int L, int R, int RightEnd)
{
    //&L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置
    int LeftEnd, NumElements, temp, i;

    LeftEnd = R - 1;
    temp = L;
    NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            TempA[temp++] = A[L++];
        else
            TempA[temp++] = A[R++];
    }

    //&直接复制剩下的
    while (L <= LeftEnd)
        TempA[temp++] = A[L++];
    while (R <= RightEnd)
        TempA[temp++] = A[R++];

    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TempA[RightEnd]; //&将有序的TempA[]复制回A[]
}

//*核心递归排序函数
void Msort(ElemType A[], ElemType Temp[], int L, int RightEnd)
{
    int Center;

    if (L < RightEnd)
    {
        Center = (L + RightEnd) / 2;
        Msort(A, Temp, L, Center);               //&递归解决左边
        Msort(A, Temp, Center + 1, RightEnd);    //&递归解决右边
        Merge(A, Temp, L, Center + 1, RightEnd); //&合并两段有序序列
    }
}

void Merge_Sort1(ElemType A[], int N)
{
    ElemType *Temp;

    Temp = (ElemType *)malloc(N * sizeof(ElemType));
    if (Temp != NULL)
    {
        Msort(A, Temp, 0, N - 1);
        free(Temp);
    }
    else
        printf("空间不足！");
}
//~归并排序(递归实现)结束

//^---------------归并排序(非递归实现)---------------^//(稳定)
//*结果不复制回Temp[]数组中
void Merge1(ElemType A[], ElemType TempA[], int L, int R, int RightEnd)
{
    //&L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置
    int LeftEnd, temp;

    LeftEnd = R - 1;
    temp = L;

    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            TempA[temp++] = A[L++];
        else
            TempA[temp++] = A[R++];
    }

    //&直接复制剩下的
    while (L <= LeftEnd)
        TempA[temp++] = A[L++];
    while (R <= RightEnd)
        TempA[temp++] = A[R++];
}

//*两两归并相邻有序子列, lenght为当前有序子列长度
void Merge_pass(ElemType A[], ElemType Temp[], int N, int length)
{
    int i, j;

    //&在归并完倒数第二对相邻子列后停止
    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge1(A, Temp, i, i + length, i + 2 * length - 1);

    if (i + length < N) //&归并最后一对子列
        Merge1(A, Temp, i, i + length, N - 1);
    else //&只剩下一个子列
        for (j = i; j < N; j++)
            Temp[j] = A[j];
}

void Merge_Sort2(ElemType A[], int N)
{
    int length;
    ElemType *Temp;

    length = 1;
    Temp = (ElemType *)malloc(N * sizeof(ElemType));
    if (Temp != NULL)
    {
        while (length < N)
        {
            Merge_pass(A, Temp, N, length);
            length *= 2;
            Merge_pass(Temp, A, N, length);
            length *= 2;
        }
        free(Temp);
    }
    else
        printf("空间不足！");
}
//~归并排序(非递归实现)结束

//^---------------C库qsort()---------------^//(不稳定)
int cmpfunc(const void *a, const void *b)
{
    return (*(ElemType *)a - *(ElemType *)b);
}
//~C库qsort()结束

//^---------------快速排序---------------^//(不稳定)
//*选主元， 取头、中、尾的中位数
ElemType Median3(ElemType A[], int Left, int Right)
{
    int Center;

    Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);
    Swap(&A[Center], &A[Right - 1]); //&将主元Pivot藏到右边

    return A[Right - 1];
}

//*核心递归函数
void Qsort(ElemType A[], int Left, int Right)
{
    int Pivot, Cutoff, Low, High;

    Cutoff = 100;
    if (Cutoff <= Right - Left + 1)
    {
        Pivot = Median3(A, Left, Right);
        Low = Left;
        High = Right - 1;
        while (1)
        {
            while (A[++Low] < Pivot)
                continue;
            while (A[--High] > Pivot)
                continue;
            if (Low < High)
                Swap(&A[Low], &A[High]);
            else
                break;
        }
        Swap(&A[Low], &A[Right - 1]);
        Qsort(A, Left, Low - 1);
        Qsort(A, Low + 1, Right);
    }
    else
        Insertion_Sort(A + Left, Right - Left + 1);
}

void Quick_Sort(ElemType A[], int N)
{
    Qsort(A, 0, N - 1);
}
//~快速排序结束

//^---------------表排序---------------^//(根据使用的排序决定)
//*通过表排序得到的Table数组进行物理排序
void PhysicsSort(ElemType A[], int N, ElemType Table[])
{
    ElemType tempElem;
    int i, nextP, temp;

    for (i = 0; i < N; i++)
    {
        if (Table[i] != i)
        {
            tempElem = A[i];

            for (temp = i; Table[temp] != i; temp = nextP)
            {
                A[temp] = A[Table[temp]]; //&将数据移动到合适位置
                nextP = Table[temp];      //&nextP为下一个将要移动的位置
                Table[temp] = temp;       //&将已排序的Table下标设置为原始数组下标
            }

            A[temp] = tempElem;
            Table[temp] = temp;
        }
    }
}

void Table_Sort(ElemType A[], int N)
{
    int i, j, temp;
    ElemType *Table;

    Table = (ElemType *)malloc(N * sizeof(ElemType));
    for (i = 0; i < N; i++)
        Table[i] = i;

    //*此处用插入排序实现
    for (i = 1; i < N; i++)
    {
        temp = Table[i];
        for (j = i; j > 0 && A[Table[j - 1]] > A[temp]; j--)
            Table[j] = Table[j - 1];

        Table[j] = temp;
    }
    //*插入排序结束

    PhysicsSort(A, N, Table);

    free(Table);
}
//~表排序结束

//^---------------计数排序---------------^//(稳定)
void Count_Sort(ElemType A[], int N)
{
    ElemType *Count;
    ElemType min, max, CountNum;
    int i;

    //&寻找最大值和最小值
    min = A[0];
    max = A[0];
    for (i = 0; i < N; i++)
    {
        if (A[i] < min)
            min = A[i];
        if (A[i] > max)
            max = A[i];
    }
    CountNum = max - min + 1;

    Count = (ElemType *)malloc(CountNum * sizeof(ElemType));
    memset(Count, 0, CountNum * sizeof(ElemType)); //&初始化

    //&开始计数
    for (i = 0; i < N; i++)
        Count[A[i] - min]++;

    //&函数内打印信息
    // int printN = 0;
    // for (i = 0; i < CountNum; i++)
    // {
    //     while (Count[i]--)
    //     {
    //         printN++;
    //         printf("%ld", i + min);
    //         if (printN != N)
    //             printf(" ");
    //     }
    // }

    //*方法一,根据Count给源数组重新赋值
    // int j;
    // for (i = 0, j = 0; i < CountNum; i++)
    //     while (Count[i]--)
    //         A[j++] = min + i;

    // free(Count);

    //*方法二,计算各个数之前元素的总和
    int j;
    ElemType *B = (ElemType *)malloc(N * sizeof(ElemType));

    for (i = 1; i < CountNum; i++)
        Count[i] += Count[i - 1];

    for (j = N - 1; j >= 0; j--)
    {
        Count[A[j] - min]--;
        B[Count[A[j] - min]] = A[j];
    }

    memcpy(A, B, N * sizeof(ElemType));
    free(B);
    free(Count);
}
//~计数排序结束

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

void Bucket_Sort(ElemType A[], int N)
{
    Bucket B;
    PtrToBNode temp, p;
    int i;
    ElemType max, min, CountNum;

    //&寻找最大值和最小值
    min = A[0];
    max = A[0];
    for (i = 0; i < N; i++)
    {
        if (A[i] < min)
            min = A[i];
        if (A[i] > max)
            max = A[i];
    }
    CountNum = max - min + 1;

    B = (Bucket)malloc(CountNum * sizeof(struct HeadBNode));
    for (i = 0; i < CountNum; i++)
        B[i].head = B[i].tail = NULL;

    for (i = 0; i < N; i++)
    {
        temp = (PtrToBNode)malloc(sizeof(struct BNode));
        temp->key = i; //&存入数组信息，此处存入数组下标
        temp->next = B[A[i] - min].head;
        B[A[i] - min].head = temp;
    }

    //&函数内打印信息
    // for (i = 0; i < CountNum; i++)
    // {
    //     if (B[i].head)
    //     {
    //         p = B[i].head;
    //         while (p)
    //         {
    //             printf("%ld", A[p->key]);
    //             if (p->next != NULL || i != CountNum - 1)
    //                 printf(" ");
    //
    //             temp = p;
    //             p = p->next;
    //             free(temp);
    //         }
    //     }
    // }

    int j;
    for (i = 0, j = 0; i < CountNum; i++)
    {
        if (B[i].head)
        {
            p = B[i].head;
            while (p)
            {
                A[j++] = i + min;
                temp = p;
                p = p->next;
                free(temp);
            }
        }
    }
}
//~桶排序结束

//^---------------基数排序---------------^//(稳定)
#define Radix 10 //&基数
//&桶元素结点定义和桶头结点定义详见桶排序
//*获取某位上的数字
int GetDigit(int X, int D)
{
    int res, i;

    for (i = 1; i <= D; i++)
    {
        res = X % Radix;
        X /= Radix;
    }

    return res;
}

//*返回数组A[]中的最小值
ElemType Get_Min(ElemType A[], int N)
{
    int i, min;

    min = A[0];
    for (i = 1; i < N; i++)
        if (A[i] < min)
            min = A[i];

    return min;
}

//*返回数组A[]中最大整数的位数
int Get_max_digit(ElemType A[], int N)
{
    int i, digit, max;

    digit = 1;
    max = A[0];
    for (i = 1; i < N; i++)
        if (A[i] > max)
            max = A[i];

    while (max >= Radix)
    {
        max /= Radix;
        digit++;
    }

    return digit;
}

//*基数排序-次位优先
void LSDRadix_Sort(ElemType A[], int N)
{
    int D, Di, i, MaxDigit;
    ElemType min;
    Bucket B;
    PtrToBNode temp, p, List;

    //&初始化每个桶为空链表
    B = (Bucket)malloc(Radix * sizeof(struct HeadBNode));
    for (i = 0; i < Radix; i++)
        B[i].head = B[i].tail = NULL;

    //&如果存在负数,将数组中所有元素加上最小负数的绝对值
    min = 0;
    if (Get_Min(A, N) < 0)
        min = Get_Min(A, N);

    //&将原始序列逆序存入初始链表List
    List = NULL;
    for (i = 0; i < N; i++)
    {
        temp = (PtrToBNode)malloc(sizeof(struct BNode));
        temp->key = A[i] - min;
        temp->next = List;
        List = temp;
    }

    //&对数据的每一位循环处理
    MaxDigit = Get_max_digit(A, N);
    for (D = 1; D <= MaxDigit; D++)
    {
        //&下面是分配的过程
        p = List;
        while (p)
        {
            Di = GetDigit(p->key, D); //&获得当前元素的当前位数字

            temp = p;
            p = p->next; //&从List中删除

            //&插入B[Di]号桶尾
            temp->next = NULL;
            if (B[Di].head == NULL)
                B[Di].head = B[Di].tail = temp;
            else
            {
                B[Di].tail->next = temp;
                B[Di].tail = temp;
            }
        }

        //&下面是收集的过程
        List = NULL;
        for (Di = Radix - 1; Di >= 0; Di--)
        {
            //&如果桶不为空，整桶插入List表头
            if (B[Di].head)
            {
                B[Di].tail->next = List;
                List = B[Di].head;
                B[Di].head = B[Di].tail = NULL; //&清空桶
            }
        }
    }

    //&将List倒入A[]并释放空间
    for (i = 0; i < N; i++)
    {
        A[i] = List->key + min;
        temp = List;
        List = List->next;
        free(temp);
    }
}

//*主位优先核心递归函数:对A[L]...A[R]的第D位数进行排序
void MSD(ElemType A[], int L, int R, int D)
{
    int Di, i, j;
    Bucket B;
    PtrToBNode temp, p, List;
    ElemType min;

    if (D == 0)
        return;

    //&初始化每个桶为空链表
    B = (Bucket)malloc(Radix * sizeof(struct HeadBNode));
    for (i = 0; i < Radix; i++)
        B[i].head = B[i].tail = NULL;

    //&如果存在负数,将数组中所有元素加上最小负数的绝对值
    min = 0;
    if (Get_Min(A, R - L + 1) < 0)
        min = Get_Min(A, R - L + 1);

    //&将原始序列逆序存入初始链表List
    List = NULL;
    for (i = L; i <= R; i++)
    {
        temp = (PtrToBNode)malloc(sizeof(struct BNode));
        temp->key = A[i] - min;
        temp->next = List;
        List = temp;
    }

    //&下面是分配的过程
    p = List;
    while (p)
    {
        Di = GetDigit(p->key, D); //&获得当前元素的当前位数字

        temp = p;
        p = p->next; //&从List中删除

        if (B[Di].head == NULL)
            B[Di].tail = temp;
        temp->next = B[Di].head;
        B[Di].head = temp;
    }

    //&下面是收集的过程
    i = j = L; //&i, j记录当前要处理的A[]的左右端下标
    for (Di = 0; Di < Radix; Di++)
    {
        if (B[Di].head) //&将非空的桶整桶倒入A[], 递归排序
        {
            p = B[Di].head;
            while (p)
            {
                A[j++] = p->key + min;
                temp = p;
                p = p->next;
                free(temp);
            }

            MSD(A, i, j - 1, D - 1); //&递归对该桶数据排序, 位数减1
            i = j;                   //&下一个桶对应的A[]左端
        }
    }
}

//*基数排序-主位优先
void MSDRadix_Sort(ElemType A[], int N)
{
    MSD(A, 0, N - 1, Get_max_digit(A, N));
}
//~基数排序结束

//^---------------测试函数---------------^//
//*输入第一行给出正整数N（≤100 000）,
//*随后一行给出N个（长整型范围内的）整数，其间以空格分隔。
int main()
{
    int i, N;
    ElemType arrData[MAXSIZE];

    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%ld", &arrData[i]);

    // Bubble_Sort(arrData, N);

    // Insertion_Sort(arrData, N);
    // Shell_Sort(arrData, N);

    // Selection_Sort(arrData, N);
    // Heap_Sort(arrData, N);

    // Merge_Sort1(arrData, N);
    // Merge_Sort2(arrData, N);

    // qsort(arrData, N, sizeof(long), cmpfunc);
    Quick_Sort(arrData, N);

    // Table_Sort(arrData, N);

    // Count_Sort(arrData, N);
    // Bucket_Sort(arrData, N);

    // LSDRadix_Sort(arrData, N);
    // MSDRadix_Sort(arrData, N);

    for (i = 0; i < N; i++)
    {
        printf("%ld", arrData[i]);
        if (i != N - 1)
            printf(" ");
    }

    return 0;
}
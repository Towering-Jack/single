#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXSIZE 105

typedef struct
{
    int abscissa;
    int ordinate;
} coordinate;

bool IfFirstJump(coordinate James, coordinate *cro, int index);
bool IfJump(coordinate James, coordinate *cro, int index);
bool IfFirstEscape(double jumpMeter);
bool IfEscape(coordinate James, int jumpMeter);
bool JumpDFS(coordinate *cro);
bool DFS(coordinate *cro, int index, bool *visited, coordinate *James);

int main()
{
    int i;
    coordinate cro[MAXSIZE];

    scanf("%d %d", &cro[0].abscissa, &cro[0].ordinate);
    for (i = 1; i <= cro[0].abscissa; i++)
        scanf("%d %d", &cro[i].abscissa, &cro[i].ordinate);

    if (JumpDFS(cro))
        printf("Yes");
    else
        printf("No");

    return 0;
}

bool IfFirstJump(coordinate James, coordinate *cro, int index)
{
    int abscissa, ordinate;
    double dismeter;

    abscissa = abs(James.abscissa - cro[index].abscissa);
    ordinate = abs(James.ordinate - cro[index].ordinate);
    dismeter = sqrt(pow(abscissa, 2) + pow(ordinate, 2));

    return cro[0].ordinate + 7.5 >= dismeter ? true : false;
}

bool IfJump(coordinate James, coordinate *cro, int index)
{
    int abscissa, ordinate;
    double dismeter;

    abscissa = abs(James.abscissa - cro[index].abscissa);
    ordinate = abs(James.ordinate - cro[index].ordinate);
    dismeter = sqrt(pow(abscissa, 2) + pow(ordinate, 2));

    return cro[0].ordinate >= dismeter ? true : false;
}

bool IfFirstEscape(double jumpMeter)
{
    return jumpMeter >= 42.5 ? true : false;
}

bool IfEscape(coordinate James, int jumpMeter)
{
    if ((50 - abs(James.abscissa) <= jumpMeter) || (50 - abs(James.ordinate) <= jumpMeter))
        return true;
    return false;
}

bool JumpDFS(coordinate *cro)
{
    int i;
    bool ifEscape;
    coordinate James;
    bool visited[MAXSIZE];

    for (i = 1; i <= cro[0].abscissa; i++)
        visited[i] = false;

    ifEscape = IfFirstEscape((double)cro[0].ordinate);

    for (i = 1; i <= cro[0].abscissa && !ifEscape; i++)
    {
        James.abscissa = 0;
        James.ordinate = 0;
        if (!visited[i] && IfFirstJump(James, cro, i))
            ifEscape = DFS(cro, i, visited, &James);
    }
    return ifEscape;
}

bool DFS(coordinate *cro, int index, bool *visited, coordinate *James)
{
    int i;
    bool ifEscape;
    coordinate cur;

    visited[index] = true;
    ifEscape = false;
    cur = (*James);
    (*James) = cro[index];

    if (IfEscape(*James, cro[0].ordinate))
        return true;

    for (i = 1; i <= cro[0].abscissa && !ifEscape; i++)
        if (!visited[i] && IfJump(*James, cro, i))
            ifEscape = DFS(cro, i, visited, James);

    (*James) = cur;
    return ifEscape;
}
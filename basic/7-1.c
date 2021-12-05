#include <stdio.h>

int main()
{
    int cm;
    scanf("%d", &cm);
    double m = (double)cm / 100;
    double Foot = m / 0.3048;
    int foot = (int)Foot;
    int inch = (int)((Foot - foot) * 12);
    printf("%d %d", foot, inch);
    return 0;
}
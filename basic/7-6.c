#include <stdio.h>

int main()
{
    double num1;
    int num2;
    char num3;
    double num4;
    scanf("%lf %d %c %lf", &num1, &num2, &num3, &num4);
    printf("%c %d %.2lf %.2lf", num3, num2, num1, num4);
    return 0;
}
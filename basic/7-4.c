#include <stdio.h>

int main()
{
    int num;
    scanf("%d",&num);
    int shi, ge;
    shi = num / 16 * 10;
    ge = num % 16;
    printf("%d",shi+ge);
    return 0;
}
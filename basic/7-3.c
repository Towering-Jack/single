#include <stdio.h>

int main()
{
    int bai, shi, ge;
    int num;
    scanf("%d", &num);
    bai = num / 100;
    shi = num / 10 % 10;
    ge = num % 10;
    if (ge == 0)
        if (shi == 0)
            printf("%d", bai);
        else
            printf("%d%d", shi, bai);
    else
        printf("%d%d%d", ge, shi, bai);
    return 0;
}
#include <stdio.h>

int main()
{
    int nowTime, passTime;
    scanf("%d %d", &nowTime, &passTime);
    int hour = nowTime / 100;
    int minute = nowTime % 100;
    if (passTime == 0)
        printf("%d", nowTime);
    else if (passTime > 0)
    {
        while (passTime >= 60)
        {
            hour++;
            passTime -= 60;
        }
        minute += passTime;
        if (minute >= 60)
        {
            hour++;
            minute -= 60;
        }
        if (minute == 0)
        {
            printf("%d00", hour);
        }
        else
            printf("%d%d", hour, minute);
    }
    else
    {
        passTime = -passTime;
        while (passTime >= 60)
        {
            hour--;
            passTime -= 60;
        }
        minute -= passTime;
        if (minute < 0)
        {
            hour--;
            minute += 60;
        }
        if (minute == 0)
        {
            printf("%d00", hour);
        }
        else
            printf("%d%d", hour, minute);
    }
    return 0;
}
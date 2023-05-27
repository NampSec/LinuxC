#include "queue.h"
#include <stdio.h>
int static __abs(int x)
{
    return x > -x ? x : -x;
}
int main(void)
{
    int x, y;
    int x2, y2;
    int px, py;
    x = 0 ,y = 10;
    x2 = 0, y2 = 0;
    int max_delta = __abs(x2 - x) > __abs(y2 - y) ? __abs(x2 - x)  : __abs(y2 - y);
    // max_delta = max_delta > -max_delta ? max_delta : -max_delta;
    printf("max_delta = %d\n", max_delta);
    for(int i = 0;i <= max_delta; i++)
    {
        px = x + (double)i / (double)max_delta *(x2 - x);
        py = y + (double)i / (double)max_delta *(y2 - y);

        printf("%d %d\n", px, py);
    }
    return 0;
}
#include <stdio.h>
#include "api.h"
#include "game.h"
#define COLOR (0xffffff)
// WHITE : 0 0 0 BALCK 225 225 225 RGB
int main() {
    int ch;
    
    while (1)
    {
        ch = getchar();
        printf("%d\n", ch);
        if(ch == ' ')
            printf("input the space\n");
    }
    
    return 0;
}
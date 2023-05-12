// VT控制码的参考：https://www2.ccs.neu.edu/research/gpc/VonaUtils/vona/terminal/vtansi.htm#erase
#include "game.h"
#include <stdio.h>
// 当前窗口的宽度和高度
int width, height;
/*
*@ Description: 清屏，对应的VT控制码：<ESC>[2J
* @return: void
*/
static void clearup_screen(void)
{
    printf("\033[2J");
}
static void draw_game_frame(void)
{

}
static void draw_score_frame(void)
{

}
static void draw_nextblock_frame(void)
{

}
/*
*@ Description: 游戏初始化，包括1.使用VT控制清幕 2.关闭回显示 3.画出游戏框 分数 和下一个这三个东西
* @return: void
*/
void game_initialized(int *fd)
{
    clearup_screen();
    set_echo_off();
    get_terminal_size(&width, &height);
    


}
void update_screen()
{

}

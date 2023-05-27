// VT控制码的参考：https://www2.ccs.neu.edu/research/gpc/VonaUtils/vona/terminal/vtansi.htm#erase
#include "game.h"
#include "api.h"
#include <stdio.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "queue.h"
#include <stdlib.h>

#define GAME_X_RES (240)
#define GAME_Y_RES (320)

#define NEXTBLOCK_X_RES (100)
#define NEXTBLOCK_Y_RES (200)

#define SCORE_X_RES (100)
#define SCORE_Y_RES (120)
// SCORE_Y_RES + NEXTBLOCK_Y_RES = GAME_Y_RES

// 最小方块的大小，需要为GAME_X_RES 和 GAME_Y_RES 的公因数
#define BLOCK_RES_SIZE (4)

// 俄罗斯方块有四种方块，最大即4x4
#define DIAMOND_MATRIX_SIZE (4)

static void get_screen_resolution(unsigned int *x_res, unsigned int *y_res);
void draw_sequence_line(point *qu); // 画出一系列的线;
static void init_frame_info(void);

static void init_frame_info(void)
{
    extern unsigned int x_res, y_res;
    extern point game_frame;
    extern point nextblock_frame;
    extern point score_frame;
    get_screen_resolution(&x_res, &y_res);
    game_frame.next = NULL;
    nextblock_frame.next = NULL;
    score_frame.next = NULL;
    game_frame.x = (x_res - GAME_X_RES - 
        (SCORE_X_RES > NEXTBLOCK_X_RES ? SCORE_X_RES : NEXTBLOCK_X_RES)) / 2;
    game_frame.y = (y_res - GAME_Y_RES) / 2;
    nextblock_frame.x = game_frame.x + GAME_X_RES;
    nextblock_frame.y = game_frame.y;
    score_frame.x = game_frame.x + GAME_X_RES;
    score_frame.y = game_frame.y + NEXTBLOCK_Y_RES;
}


// 将block map的坐标转化为实际屏幕的坐标
static void convert_blockpoint_respoint(point const * const block_point, point * res_point)
{
    extern point game_frame;
    res_point->x = game_frame.x + block_point->x * BLOCK_RES_SIZE;
    res_point->y = game_frame.y + GAME_Y_RES - block_point->y * BLOCK_RES_SIZE;
}

// 将实际屏幕坐标转化为block map的坐标
static void convert_respoint_blockpoint(point const * const res_point, point * block_point)
{
    extern point game_frame;
    block_point->x = (res_point->x - game_frame.x ) / BLOCK_RES_SIZE;
    block_point->y = (game_frame.y + GAME_Y_RES - res_point->y) / BLOCK_RES_SIZE;
}

static void get_screen_resolution(unsigned int *x_res, unsigned int *y_res)
{
    int fb;
    open_framebuffer(&fb);
    // Get the variable screen information
    struct fb_var_screeninfo var_info;

    if (ioctl(fb, FBIOGET_VSCREENINFO, &var_info) == -1)
    {
        close(fb);
        return;
    }
    *x_res = var_info.xres;
    *y_res = var_info.yres;
    close_framebuffer(&fb);
}

/*
 *@ Description: 初始化屏幕背景
 * @return: void
 */
static void init_background(void)
{
    int fb;
    int width, height;
    get_terminal_size(&width, &height);
    printf("\033[2J");                    // 清屏
    printf("\033[?25l");                  // 禁止光标闪烁
    printf("\033[%d;%dH", height, width); // 将光标移动到最右下角
    fflush(stdout);
    open_framebuffer(&fb);
    clear_screen(&fb, 255, 255, 255); // 将屏幕全部刷新为白色
    close_framebuffer(&fb);
}
void draw_sequence_line(point *qu) // 画出一系列的线
{
    point *cur = qu, *next;
    int fb;
    int x1, y1, x2, y2;
    if (cur == NULL || cur->next == NULL)
        return; // queue中至少有两个点
    open_framebuffer(&fb);
    while (cur->next != NULL) // 由于queue
    {
        x1 = cur->x;
        y1 = cur->y;
        next = cur->next;
        x2 = next->x;
        y2 = next->y;
        draw_line(&fb, x1, y1, x2, y2, 0, 0, 0);
        // printf("x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);
        cur = next;
    }
    draw_line(&fb, x1, y1, x2, y2, 0, 0, 0);
    // printf("x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);
    close_framebuffer(&fb);
}


static void draw_square_frame(point const * const p, int width, int height)
{
    point *queue = NULL;
    int x, y;
    x = p->x;
    y = p->y;
    add_point(&queue, x, y);
    x = x + width;
    add_point(&queue, x, y);
    y = y + height;
    add_point(&queue, x, y);
    x = x - width;
    add_point(&queue, x, y);
    y = y - height;
    add_point(&queue, x, y);
    draw_sequence_line(queue);
    destroy_queue(queue);
}
// 计算出游戏的框架图，使用链表，表示点与点之间连接
static void draw_frame()
{
    extern point game_frame;
    extern point nextblock_frame;
    extern point score_frame;
    draw_square_frame(&game_frame, GAME_X_RES, GAME_Y_RES);
    draw_square_frame(&nextblock_frame, NEXTBLOCK_X_RES, NEXTBLOCK_Y_RES);
    draw_square_frame(&score_frame, SCORE_X_RES, SCORE_Y_RES);
}

// 旋转后的图形应该需要贴紧最低
static unsigned int matrix_turn_left(unsigned int diamond)
{
    switch (diamond)
    {
    case 0xf:
        return 0x1111;
    case 0x1111:
        return 0xf;
    //
    case 0x233:
        return 0x74;
    case 0x74:
        return 0x311;
    case 0x311:
        return 0x17;
    case 0x17:
        return 0x233;
    //
    case 0x232:
        return 0x72;
    case 0x72:
        return 0x131;
    case 0x131:
        return 0x27;
    case 0x27:
        return 0x232;
    //
    case 0x33:
        return 0x33;
    default:
        break;
    }
}
static unsigned int matrix_turn_right(unsigned int diamond)
{
    switch (diamond)
    {
    case 0xf:
        return 0x1111;
    case 0x1111:
        return 0xf;
    //
    case 0x17:
        return 0x311;
    case 0x311:
        return 0x74;
    case 0x74:
        return 0x233;
    case 0x233:
        return 0x17;
    //
    case 0x27:
        return 0x131;
    case 0x131:
        return 0x72;
    case 0x72:
        return 0x232;
    case 0x232:
        return 0x27;
    //
    case 0x33:
        return 0x33;
    default:
        break;
    }
}

static unsigned int generate_next_block()
{
    // 所有方块都向左下角靠,矩阵从左下角开始编号
    // 使用int 的低16位代表一个方块, 前16位代表颜色吧
    unsigned int x[] = {0xf, 0x17, 0x27, 0x33};
    unsigned int i = rand() % (sizeof(x) / sizeof(x[0]));
    return x[i];
}

/*
 *@ Description: 游戏初始化，包括1.使用VT控制清幕 2.关闭回显示 3.画出游戏框 分数 和下一个这三个东西
 * @return: void
 */

void game_initialized(void)
{
    init_frame_info(); // 初始化分辨率和各个框的信息
    init_background();
    draw_frame();
}

static void earase(int x, int y)
{
    int x1, y1;
    int x2, y2;
    int fb;
    x1 = x;
    y1 = y - BLOCK_RES_SIZE * DIAMOND_MATRIX_SIZE;
    x2 = x1 + BLOCK_RES_SIZE * DIAMOND_MATRIX_SIZE;
    y2 = y1 + BLOCK_RES_SIZE * DIAMOND_MATRIX_SIZE;
    open_framebuffer(&fb);
    draw_rect(&fb, x1, y1, x2, y2, 255, 255, 255);
    close_framebuffer(&fb);
}

// 在指定的x,y画出最小分辨率的方块
static void draw_block_res(int x, int y)
{
    int x1, y1;
    int x2, y2;
    int fb;
    x1 = x;
    y1 = y - BLOCK_RES_SIZE;
    x2 = x1 + BLOCK_RES_SIZE;
    y2 = y1 + BLOCK_RES_SIZE;
    open_framebuffer(&fb);
    draw_rect(&fb, x1, y1, x2, y2, 0, 0, 0);
    close_framebuffer(&fb);
}

static void draw_diamond(int x, int y, unsigned int diamond)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (diamond & (0x1 << ((i * 4) + j)))
            {
                draw_block_res(x + j * BLOCK_RES_SIZE, y - i * BLOCK_RES_SIZE); // 方块由左向右，由下向上
            }
        }
    }
}
// 判断落下会不会碰到下面的东西
static int diamond_reach_bottom(char block_map[][GAME_X_RES / BLOCK_RES_SIZE], unsigned int diamond, unsigned int x, unsigned int y)
{
    if (y == 0) return 1; // 已经触底
    for (int i = 0; i < 4; i++)
    {
        if(diamond & (1 << i))
        {
            if(block_map[y - 1][ x + i] == 1) // diamond 下面那一层有方块
                return 1;
        }
    }
    return 0;
}



static int update_block_map(char block_map[][GAME_X_RES / BLOCK_RES_SIZE], unsigned int diamond, unsigned int x, unsigned int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (diamond & (0x1 << ((i * 4) + j)))
            {
                block_map[y + i][x + j] = 1;
            }
        }
    }

}



void update_screen()
{
    static char block_map[GAME_Y_RES / BLOCK_RES_SIZE][GAME_X_RES / BLOCK_RES_SIZE] = {0};

    extern unsigned int x_res, y_res;
    static point cur_diamond_pos = {0, 0, NULL}; // x,y 都是block map的坐标，指向正在活动的那个物理块的左下角
    static int flag = 0;     // 如果flag = 1, 代表还在下落中，暂时不需要刷出新方块
    static unsigned int new_diamond;
    if (flag == 0)
    {
        flag = 1;
        new_diamond = generate_next_block();
        cur_diamond_pos.x = GAME_X_RES / BLOCK_RES_SIZE / 2;
        cur_diamond_pos.y = GAME_Y_RES / BLOCK_RES_SIZE;
    }
    else
    {
        if (diamond_reach_bottom(block_map, new_diamond, cur_diamond_pos.x, cur_diamond_pos.y))
        {
            flag = 0;
            update_block_map(block_map, new_diamond, cur_diamond_pos.x, cur_diamond_pos.y);
        }
        else
        {
            point temp = {0, 0, NULL};
            convert_blockpoint_respoint(&cur_diamond_pos, &temp);
            earase(temp.x, temp.y); // 擦除原处的痕迹
            cur_diamond_pos.y -= 1;
            // x = x +/- 1; 根据输入将方块左移或者右移
            draw_diamond(temp.x, temp.y + BLOCK_RES_SIZE, new_diamond);
        }
    }
    return;
}

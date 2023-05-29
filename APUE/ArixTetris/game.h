/*    GAME    */
#ifndef __GAME_h__
#define __GAME_h__
#include "queue.h"
#define GAME_X_RES (240)
#define GAME_Y_RES (320)

#define NEXTBLOCK_X_RES (100)
#define NEXTBLOCK_Y_RES (200)

#define SCORE_X_RES (100)
#define SCORE_Y_RES (120)
// SCORE_Y_RES + NEXTBLOCK_Y_RES = GAME_Y_RES

// 最小方块的大小，需要为GAME_X_RES 和 GAME_Y_RES 的公因数
#define BLOCK_RES_SIZE (8)

// 俄罗斯方块有四种方块，最大即4x4
#define DIAMOND_MATRIX_SIZE (4)
#define FRAME_COLOR (0)
#define BACKGROUND_COLOR (0xffffff)
#define NEXT_BLOCK_COLOR (0)

int update_screen();
void update_nextblock();
void game_initialized(void);
unsigned int matrix_turn_left(unsigned int diamond);
unsigned int matrix_turn_right(unsigned int diamond);
void refresh_diamond(int x, int y, unsigned int old_diamond, unsigned int new_diamond, int x_offset, int y_offset, unsigned int color);
void convert_blockpoint_respoint(point const * const block_point, point * res_point);

#endif


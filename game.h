#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>

//#define paddleWidth 40
#define paddleHeight 10
#define paddleYposition 110
#define ROWS_OF_BLOCKS 7
#define COLUMNS_OF_BLOCKS 12
#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 8
#define BLOCK_PADDING 2
#define BLOCK_OFFSET 10

extern int score;

extern void initializeBlocks(void);
extern void normalizeDirection(void);
extern void handleBlockCollision(Block_t *block);
extern void normalizeDirection(void);


#endif

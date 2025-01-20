#ifndef __GAME_H__
#define __GAME_H__

//#define paddleWidth 40
#define paddleHeight 10
#define paddleYposition 110

extern void reset_game(void);
extern void initializeBlocks(void);
extern void normalizeDirection(void);
extern void handleBlockCollision(Block_t *block);
extern void normalizeDirection(void);


#endif

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <stdbool.h>

typedef struct Ball_t{
  float XPos;   // Initial X position of the ball (center of screen)
  float YPos;   // Initial Y position of the ball, just below blocks
  float XDir;   // X direction: 1 for right, -1 for left
  float YDir;   // Y direction: 1 for down, -1 for up
  float Speed;   // Ball speed in pixels
  float Radius;
  bool Collision;
} Ball_t;

typedef struct Paddle_t {
  float XPos;
  float Direction;
  float Speed;
} Paddle_t;

typedef struct Block_t {
  bool active;
  int xMin;
  int xMax;
  int yMin;
  int yMax;
  int id;
}Block_t;

typedef struct Game_t {
   Ball_t balls[5];
   Paddle_t paddles[2];
   Block_t blocks[7][12];
   uint32_t score;
} Game_t;



extern Ball_t balls[5];
extern Paddle_t paddles[2];
extern Block_t blocks[7][12];



















#endif




































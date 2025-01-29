#ifndef __MAIN_H__
#define __MAIN_H__

/***************************************************************************//**
 * Update the ball position and handle collisions.
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

#define HIGH true
#define LOW false
/*Defintions*/

typedef struct Button_t {
  uint8_t id;
  bool state;
  bool triggered;
}Button_t;

typedef struct Ball_t{
  float XPos;   // Initial X position of the ball (center of screen)
  float YPos;   // Initial Y position of the ball, just below blocks
  float XDir;   // X direction: 1 for right, -1 for left
  float YDir;   // Y direction: 1 for down, -1 for up
  float Speed;   // Ball speed in pixels
  float Radius;
  bool Collision;
  bool InPlay;
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

typedef struct Settings_t {
    int number_of_balls;
    int ball_speed;
    int ball_size;
    int paddle_width;
    int paddle_speed;
} Settings_t;

typedef struct Leaderboard_t{
  int row;
  int score;
  int leaders[5];
}Leaderboard_t;

typedef struct Game_t {
   Ball_t balls[5];
   Paddle_t paddles[2];
   Block_t blocks[7][12];
   uint32_t score;
   Settings_t settings;
} Game_t;

extern Game_t game;
extern Button_t buttons[2];
extern Leaderboard_t leader;

#if 0
extern Ball_t balls[5];
extern Paddle_t paddles[2];
extern Block_t blocks[7][12];
extern Button_t buttons[2];

#endif


#endif

























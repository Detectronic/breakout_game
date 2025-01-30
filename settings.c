
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "settings.h"

int number_of_balls_out_game;
bool atLeastOneBallActive;
int position = 0;

void reset_game(void){


  atLeastOneBallActive = true;
  number_of_balls_out_game = 0;

  game.settings.paddle_width = 60;
  game.settings.number_of_balls = 3;
  game.settings.ball_size = 4;
  game.settings.ball_speed = 2.0f ;
  game.settings.paddle_speed = 2;

  game.balls[1].XPos = 30.0f;
  game.balls[1].YPos = 64.0f;
  game.balls[1].XDir = 1.1f;
  game.balls[1].YDir = -1.0f;
  game.balls[1].Speed = 1.0f;
  game.balls[1].Collision = false;
  game.balls[1].Radius = game.settings.ball_size;
  game.balls[1].InPlay = true;

  game.balls[0].XPos = 64.0f;
  game.balls[0].YPos = 64.0f;
  game.balls[0].XDir = 0.1f;
  game.balls[0].YDir = -1.0f;
  game.balls[0].Speed = game.settings.ball_speed;
  game.balls[0].Collision = false;
  game.balls[0].Radius = game.settings.ball_size;
  game.balls[0].InPlay = true;

  game.balls[2].XPos = 64.0f;
  game.balls[2].YPos = 64.0f;
  game.balls[2].XDir = 0.1f;
  game.balls[2].YDir = -1.0f;
  game.balls[2].Speed = game.settings.ball_speed;
  game.balls[2].Collision = false;
  game.balls[2].Radius = game.settings.ball_size;
  game.balls[2].InPlay = true;

  game.paddles[0].XPos = 44;
  game.paddles[0].Direction = 1;
  game.paddles[0].Speed = game.settings.paddle_speed;

  initializeBlocks();
}



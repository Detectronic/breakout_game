
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "core/main.h"

#include "settings.h"
#include "core/view_model/app.h"

int position = 0;
int number_of_balls_out_game;
bool atLeastOneBallActive;


void reset_game(void){


  atLeastOneBallActive = true;
  number_of_balls_out_game = 0;

  game.settings.paddle_width = 60;

  game.settings.number_of_balls = number_of_balls;
  game.settings.ball_size = ball_size;
  game.settings.ball_speed = 1.0f;
  game.settings.paddle_speed = paddle_sensitivity_setting;

  game.balls[0].XPos = 64.0f;
  game.balls[0].YPos = 110.0f;
  game.balls[0].XDir = 0.1f;
  game.balls[0].YDir = -1.0f;
  game.balls[0].Speed = game.settings.ball_speed;
  game.balls[0].Collision = false;
  game.balls[0].Radius = game.settings.ball_size;
  game.balls[0].InPlay = true;

  game.balls[1].XPos = 30.0f;
  game.balls[1].YPos = 64.0f;
  game.balls[1].XDir = 1.1f;
  game.balls[1].YDir = -1.0f;
  game.balls[1].Speed = game.settings.ball_speed;
  game.balls[1].Collision = false;
  game.balls[1].Radius = game.settings.ball_size;
  game.balls[1].InPlay = true;

  game.balls[2].XPos = 64.0f;
  game.balls[2].YPos = 64.0f;
  game.balls[2].XDir = 0.1f;
  game.balls[2].YDir = -1.0f;
  game.balls[2].Speed = game.settings.ball_speed;
  game.balls[2].Collision = false;
  game.balls[2].Radius = game.settings.ball_size;
  game.balls[2].InPlay = true;

  game.balls[3].XPos = 64.0f;
  game.balls[3].YPos = 64.0f;
  game.balls[3].XDir = 0.1f;
  game.balls[3].YDir = -1.0f;
  game.balls[3].Speed = game.settings.ball_speed;
  game.balls[3].Collision = false;
  game.balls[3].Radius = game.settings.ball_size;
  game.balls[3].InPlay = true;

  game.balls[4].XPos = 64.0f;
  game.balls[4].YPos = 64.0f;
  game.balls[4].XDir = 0.1f;
  game.balls[4].YDir = -1.0f;
  game.balls[4].Speed = game.settings.ball_speed;
  game.balls[4].Collision = false;
  game.balls[4].Radius = game.settings.ball_size;
  game.balls[4].InPlay = true;

  game.paddles[0].XPos = 44;
  game.paddles[0].Direction = 1;
  game.paddles[0].Speed = game.settings.paddle_speed;

  initializeBlocks();
}

void test_reset_game(void){


  int ball_direction = 1;

  //Ball moving upwards
  if (ball_direction == 1){

	  printf("Reached the test_reset function");


	  game.balls[0].XPos = 64.0f;
	  game.balls[0].YPos = 100.0f;
	  game.balls[0].XDir = 0.1f;
	  game.balls[0].YDir = -1.0f;
	  game.balls[0].Speed = game.settings.ball_speed;
	  game.balls[0].Collision = false;
      game.balls[0].Radius = game.settings.ball_size;
	  game.balls[0].InPlay = true;

  }



  atLeastOneBallActive = true;
  number_of_balls_out_game = 0;

  game.settings.paddle_width = 60;

  game.settings.number_of_balls = number_of_balls;
  game.settings.ball_size = ball_size;
  game.settings.ball_speed = 1.0f;
  game.settings.paddle_speed = paddle_sensitivity_setting;

#if 0
  game.balls[0].XPos = 64.0f;
  game.balls[0].YPos = 110.0f;
  game.balls[0].XDir = 0.1f;
  game.balls[0].YDir = -1.0f;
  game.balls[0].Speed = game.settings.ball_speed;
  game.balls[0].Collision = false;
  game.balls[0].Radius = game.settings.ball_size;
  game.balls[0].InPlay = true;

#endif

  game.balls[1].XPos = 30.0f;
  game.balls[1].YPos = 64.0f;
  game.balls[1].XDir = 1.1f;
  game.balls[1].YDir = -1.0f;
  game.balls[1].Speed = game.settings.ball_speed;
  game.balls[1].Collision = false;
  game.balls[1].Radius = game.settings.ball_size;
  game.balls[1].InPlay = true;

  game.balls[2].XPos = 64.0f;
  game.balls[2].YPos = 64.0f;
  game.balls[2].XDir = 0.1f;
  game.balls[2].YDir = -1.0f;
  game.balls[2].Speed = game.settings.ball_speed;
  game.balls[2].Collision = false;
  game.balls[2].Radius = game.settings.ball_size;
  game.balls[2].InPlay = true;

  game.balls[3].XPos = 64.0f;
  game.balls[3].YPos = 64.0f;
  game.balls[3].XDir = 0.1f;
  game.balls[3].YDir = -1.0f;
  game.balls[3].Speed = game.settings.ball_speed;
  game.balls[3].Collision = false;
  game.balls[3].Radius = game.settings.ball_size;
  game.balls[3].InPlay = true;

  game.balls[4].XPos = 64.0f;
  game.balls[4].YPos = 64.0f;
  game.balls[4].XDir = 0.1f;
  game.balls[4].YDir = -1.0f;
  game.balls[4].Speed = game.settings.ball_speed;
  game.balls[4].Collision = false;
  game.balls[4].Radius = game.settings.ball_size;
  game.balls[4].InPlay = true;

  game.paddles[0].XPos = 44;
  game.paddles[0].Direction = 1;
  game.paddles[0].Speed = game.settings.paddle_speed;

  initializeBlocks();
}



/***************************************************************************//**
 * @file memlcd_app.h
 * @brief Memory Liquid Crystal Display (LCD) example functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>  // For standard integer types

#ifndef MEMLCD_APP_H
#define MEMLCD_APP_H

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

extern Ball_t ball;
extern Paddle_t paddle;
extern Block_t blocks[7][12];



/***************************************************************************//**
 /* Initialize example
 ******************************************************************************/
void memlcd_app_init(void);

/***************************************************************************//**
 * Ticking function
 ******************************************************************************/
void memlcd_game(Paddle_movement_t a_paddle_movement);
void memlcd_mainmenu(uint8_t a_main_menu);
void memlcd_endgame(uint8_t a_gameover_menu);
void memlcd_settings(uint8_t a_settings_menu);
void memlcd_leaderboard(void);
void memlcd_error(void);
void reset_game(void);



#endif // MEMLCD_APP_H

/***************************************************************************//**
 * @file app.h
 * @brief Top level application functions
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
 *  THIS IS A TEST
 
 ******************************************************************************/

#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <stdint.h>


typedef enum State_t {
  MAINMENU,         //0
  GAME,             //1
  ENDGAME,          //2
  SETTINGS,         //3
  LEADERBOARD,      //4
  ERROR,
  TEST
} State_t;

typedef enum Menu_t{
  MENU_START,       //0
  MENU_SETTINGS,    //1
  MENU_LEADERBOARD,  //2
  MENU_TEST
}Menu_t;

typedef enum Setting_t{
  BALL_SPEED,         //0
  PADDLE_SENSITIVITY, //1
  NUMBER_OF_BALLS,    //2
  BALL_SIZE,          //3
  MAIN_MENU           //4
}Setting_t;

typedef enum GameOver_t{
  PLAY_AGAIN,                //0
  GAMEOVER_LEADERBOARD,      //1
  GAMEOVER_MAIN_MENU         //2
}GameOver_t;

typedef enum Paddle_movement_t{
  NONE,       //0
  LEFT,       //1
  RIGHT       //2
}Paddle_movement_t;

/*Defined in seperate file*/
extern GameOver_t gameover;
extern Setting_t setting;
extern State_t state;
extern Menu_t menu;
extern Paddle_movement_t Pmove;

extern paddle_sensitivity_setting;
extern number_of_balls;
extern ball_speed;
extern ball_size;
extern game_setting;
/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void);

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void);

#endif // APP_H

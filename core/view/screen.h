#ifndef MEMLCD_APP_H
#define MEMLCD_APP_H
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



void memlcd_app_init(void);

/***************************************************************************//**
 * Ticking function
 ******************************************************************************/
void memlcd_game(Paddle_movement_t a_paddle_movement);
void memlcd_mainmenu(uint8_t a_main_menu);
void memlcd_endgame(uint8_t a_gameover_menu);
void memlcd_settings(uint8_t a_settings_menu,int *a_game_settings);
int memlcd_leaderboard(int *score_array, int score);
void memlcd_error(void);
void reset_game(void);



#endif // MEMLCD_APP_H

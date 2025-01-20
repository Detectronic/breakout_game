/***************************************************************************//**
 * @file app.c
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
 *
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "app.h"
#include "memlcd_app.h"
#include "debug.h"
#include "main.h"
#include "settings.h"


/*Declerations*/

State_t state;

State_t last_state = ERROR;

Menu_t menu;

//int paddle_width = 0;


/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void){

  app_iostream_eusart_init();
  memlcd_app_init();

}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void){

  app_iostream_eusart_process_action();
  static int menu = 0;
  static int setting = 0;
  static int gameover = 0;

  bool new_state = false;
  if (state != last_state){

      new_state = true;

  }


  switch (state){

    case MAINMENU:

      if (new_state){

          printf("MAINMENU\n");

      }

      if (buttons[0].triggered){

          buttons[0].triggered = false;

          if (buttons[0].state){

             switch(menu){

               case MENU_START:
                 state = GAME;
                 break;

               case MENU_SETTINGS:
                 state = SETTINGS;
                 break;

               case MENU_LEADERBOARD :
                 state = LEADERBOARD;
                 break;
             }
          }

      }

      if (buttons[1].triggered){

            buttons[1].triggered = false;

           if (buttons[1].state){

               if (++menu == 3){

                   menu = 0;
               }
            }
        }

      memlcd_mainmenu(menu);
      break;

    case GAME:
      if (new_state){

            printf("GAME\n");

        }

      Paddle_movement_t Pmove = NONE;

         if (buttons[0].state){

             Pmove = LEFT;

         }

           if (buttons[1].state){

               Pmove = RIGHT;

               }

      memlcd_game(Pmove);
      break;


    case SETTINGS:

      if (new_state){

            printf("SETTING\n");

        }

      if (buttons[0].triggered){

             buttons[0].triggered = false;
             if (buttons[0].state){

                 switch(setting){

                   case BALL_SPEED:
                     return;
                     break;

                   case PADDLE_SENSITIVITY:
                     if (buttons[0].state){

                         game.settings.paddle_width = 0;
                         game.settings.paddle_width++;

                         //Settings_t[paddle_width];
                         //drawPaddle(game.settings.paddle_width);

                         if (game.settings.paddle_width == 3){
                             game.settings.paddle_width = 0;
                     }

               }




                     return;
                     break;

                   case MAIN_MENU:
                     state = MAINMENU;
                     break;
                 }
             }
        }

           if (buttons[1].triggered){

                buttons[1].triggered = false;

                if (buttons[1].state){

                    if (++setting == 3){

                        setting = 0;
                }
            }

        }


      memlcd_settings(setting);
      break;

    case LEADERBOARD:

      if (new_state){

            printf("LEADERBAORD\n");

        }
      if (buttons[0].triggered){

          buttons[0].triggered = false;

          if (buttons[0].state){

              state = MAINMENU;
          }
      }

      memlcd_leaderboard();
      break;


    case ENDGAME:

      if (new_state){

            printf("ENDGAME\n");

        }

      if (buttons[0].triggered){

          buttons[0].triggered = false;

          if (buttons[0].state){

              switch(gameover){

                case PLAY_AGAIN:
                  state = GAME;
                  break;

                case GAMEOVER_LEADERBOARD:
                  state = LEADERBOARD;
                  break;

                case GAMEOVER_MAIN_MENU:
                  state = MAIN_MENU;
                  break;

              }
          }
      }

      if (buttons[1].triggered){

          buttons[1].triggered = false;

      if (buttons[1].state){

          if (++gameover == 3){
              gameover = 0;

          }
      }
  }

      memlcd_endgame(gameover);
      break;

    default:
      memlcd_error();
      break;

  }

  if (new_state){

      last_state = state;
  }

}

/**
 ********************************************************************************
 * @file    ${screen.h}
 * @author  ${Abdul Rahman}
 * @date    ${19.02.2025}
 * @brief
 ********************************************************************************
 */

#ifndef MEMLCD_APP_H
#define MEMLCD_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>  // For standard integer types
/*******************************************************************************
 *
 * MACROS AND DEFINES
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * TYPEDEFS
 *
 ******************************************************************************/

typedef struct ScreenWipe_t{
	int x;
	int y;
	int width;
	int height;

}ScreenWipe_t;



/*******************************************************************************
 *
 * EXPORTED VARIABLES
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * GLOBAL FUNCTION PROTOTYPES
 *
 ******************************************************************************/
void memlcd_app_init(void);
void memlcd_game(Paddle_movement_t a_paddle_movement);
void memlcd_mainmenu(uint8_t a_main_menu);
void memlcd_endgame(uint8_t a_gameover_menu);
void memlcd_settings(uint8_t a_settings_menu,int *a_game_settings);
int memlcd_leaderboard(int *score_array, int score);
void memlcd_error(void);
void reset_game(void);
#ifdef __cplusplus
}
#endif

#endif // MEMLCD_APP_H


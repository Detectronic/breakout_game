//includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sl_board_control.h"
#include "em_assert.h"
#include "glib.h"
#include "dmd.h"
#include "core/view_model/app.h"
#include "sl_sleeptimer.h"
#include "core/model/control.h"
#include "core/main.h"
#include "core/model/settings.h"
#include "core/model/flash.h"
#include "core/view_model/game.h"
#include "core/view/screen.h"
#include "core/model/Timer0.h"

// String definitions
static GLIB_Context_t glibContext;
static GLIB_Context_t glibContextPaddle;
static GLIB_Context_t glibContextBall;
static GLIB_Context_t glibContextBlock;
static GLIB_Context_t glibContextTest;

GLIB_Rectangle_t test;
GLIB_Rectangle_t myBoard;

static int currentLine = 0;
#ifndef LCD_MAX_LINES
#define LCD_MAX_LINES      11
#endif

//Global varible
int main_menu = 1;
extern bool Timer0_OF;
bool once = false;
bool memlcdgame_timer = false;
/*******************************************************************************
 **************************   FUNCTION DECLARATIONS   **************************
 ******************************************************************************/
void initializeBlocks(void);
ScreenWipe_t drawBlocks(GLIB_Context_t *pContext);
ScreenWipe_t updatePaddlePosition(Paddle_movement_t a_paddle_movement);
ScreenWipe_t updateBallPosition(void);
void drawGameObjects(void);
void display_score(GLIB_Context_t *pContext);


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize the LCD application.
 ******************************************************************************/
void memlcd_app_init(void) {
    uint32_t status;

    /* Enable the memory LCD */
    status = sl_board_enable_display();
    EFM_ASSERT(status == SL_STATUS_OK);

    /* Initialize the DMD support for memory LCD display */
    status = DMD_init(0);
    EFM_ASSERT(status == DMD_OK);

    /* Initialize the GLIB context */
    status = GLIB_contextInit(&glibContext);
    EFM_ASSERT(status == GLIB_OK);

    glibContext.backgroundColor = White;
    glibContext.foregroundColor = Black;

    /* Initialize the blocks */
    initializeBlocks();

    /* Fill LCD with background color */
    GLIB_clear(&glibContext);

    /* Display initial message */
    GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNarrow6x8);
    GLIB_drawStringOnLine(&glibContext,
                          "Press BTN1 to start game",
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);
    DMD_updateDisplay();
}


/***************************************************************************//**
 * Draw the paddle on the screen.
 ******************************************************************************/
void drawPaddle(GLIB_Context_t *pContext, int paddle_width) {

    pContext->foregroundColor = Black;

    myBoard.xMin = game.paddles[0].XPos;
    myBoard.yMin = 110;
    myBoard.xMax = game.paddles[0].XPos + game.settings.paddle_width; // Paddle width of 40
    myBoard.yMax = 120;

    GLIB_drawRectFilled(pContext, &myBoard);
}

void draw_lives(void){

  for (int x = 0; x < lives; x++){

      GLIB_drawCircleFilled(&glibContext, x * 10 + 5, 5, 2);

  }

}

/***************************************************************************//**
 * Draw the game objects: blocks, paddle, and ball.
 ******************************************************************************/
void drawGameObjects(void) {

  for (int x = 0; x < game.settings.number_of_balls; x++){

      if (game.balls[x].InPlay){

          GLIB_drawCircleFilled(&glibContext, (int)game.balls[x].XPos, (int)game.balls[x].YPos, (int)game.balls[x].Radius);

      }
  }

  drawPaddle(&glibContext, game.settings.paddle_width);

}

/***************************************************************************//**
 * Game loop function to continuously update and display the game.
 ******************************************************************************/
void memlcd_game(Paddle_movement_t a_paddle_movement) {


	if (!memlcdgame_timer){

		printf("\n(GAME)            memlcd_game");
		memlcdgame_timer = true;

	}


	if (!once){

		printf("\nReached the memlcd draw game screen function inside screen.c");
		once = true;
		printf("\n(game)   state of timer0_of (%d)",Timer0_OF );
	}




	if (Timer0_OF == true){



	bool clear_screen = false;

	if (!clear_screen){

		//clear_screen = true;
		/* Clear the LCD screen with background color */
		glibContext.backgroundColor = White;
		glibContext.foregroundColor = Black;
		GLIB_clear(&glibContext);

	}

    ScreenWipe_t _paddle = updatePaddlePosition(a_paddle_movement);

    glibContextPaddle.clippingRegion.xMin = _paddle.x;
    glibContextPaddle.clippingRegion.xMax = _paddle.width ;
    glibContextPaddle.clippingRegion.yMin = _paddle.y;
    glibContextPaddle.clippingRegion.yMax = _paddle.height;
	GLIB_clearRegion(&glibContextPaddle);

	//printf("\nDirection: %d", a_paddle_movement);

	//printf("\nXMin: %d",_paddle.x );
	//printf("\nWidth: %d",_paddle.width );
	//printf("\nYMin: %d",_paddle.y );
	//printf("\nHeight: %d",_paddle.height );

	ScreenWipe_t _ball = updateBallPosition();
	glibContextBall.clippingRegion.xMin = _ball.x;
	glibContextBall.clippingRegion.xMax = _ball.width ;
	glibContextBall.clippingRegion.yMin = _ball.y;
	glibContextBall.clippingRegion.yMax = _ball.height;
	GLIB_clearRegion(&glibContextBall);

	GLIB_clearRegion(&glibContextBlock);
   	ScreenWipe_t _blocks = drawBlocks(&glibContext);
	glibContextBlock.clippingRegion.xMin = _blocks.x;
	glibContextBlock.clippingRegion.xMax = _blocks.width ;
	glibContextBlock.clippingRegion.yMin = _blocks.y;
	glibContextBlock.clippingRegion.yMax = _blocks.height;

    draw_lives();

    GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNarrow6x8);
    GLIB_drawString(&glibContext,
                      "Score: ",
                      15,
                      70,
                      5,
                      true);







    DMD_updateDisplay(); // Refresh display

    //GPIO_PinOutToggle(LEDPORT,LEDPIN);
    Timer0_OF = false;





    }
}



typedef struct menu_item_t{
  char str [13];
  uint8_t strlen;
  uint8_t yPos;
}menu_item_t;


menu_item_t menu_items[4] = {
    {
        .str = "Start",
        .strlen = 5,
        .yPos = 50
    },
    {
        .str = "Settings",
        .strlen = 8,
        .yPos = 70
    },
    {
        .str = "Leaderboard",
        .strlen = 11,
        .yPos = 90
    },
	{
		.str = "Test",
		.strlen = 5,
		.yPos = 110

	}
};

void memlcd_test(Paddle_movement_t a_paddle_movement){

	test_reset_game();

	if (!memlcdgame_timer){


		printf("\n(TEST)            memlcd_TEST");
		memlcdgame_timer = true;

	}


	if (!once){

		printf("\nReached the memlcd draw game screen function inside screen.c");
		once = true;
		printf("\n(game)   state of timer0_of (%d)",Timer0_OF );
	}




	if (Timer0_OF == true){



	bool clear_screen = false;

	if (!clear_screen){

		//clear_screen = true;
		/* Clear the LCD screen with background color */
		glibContext.backgroundColor = White;
		glibContext.foregroundColor = Black;
		GLIB_clear(&glibContext);

	}

	ScreenWipe_t _paddle = updatePaddlePosition(a_paddle_movement);

	glibContextPaddle.clippingRegion.xMin = _paddle.x;
	glibContextPaddle.clippingRegion.xMax = _paddle.width ;
	glibContextPaddle.clippingRegion.yMin = _paddle.y;
	glibContextPaddle.clippingRegion.yMax = _paddle.height;
	GLIB_clearRegion(&glibContextPaddle);

	//printf("\nDirection: %d", a_paddle_movement);

	//printf("\nXMin: %d",_paddle.x );
	//printf("\nWidth: %d",_paddle.width );
	//printf("\nYMin: %d",_paddle.y );
	//printf("\nHeight: %d",_paddle.height );

	ScreenWipe_t _ball = updateBallPosition();
	glibContextBall.clippingRegion.xMin = _ball.x;
	glibContextBall.clippingRegion.xMax = _ball.width ;
	glibContextBall.clippingRegion.yMin = _ball.y;
	glibContextBall.clippingRegion.yMax = _ball.height;
	GLIB_clearRegion(&glibContextBall);

	GLIB_clearRegion(&glibContextBlock);
	ScreenWipe_t _blocks = drawBlocks(&glibContext);
	glibContextBlock.clippingRegion.xMin = _blocks.x;
	glibContextBlock.clippingRegion.xMax = _blocks.width ;
	glibContextBlock.clippingRegion.yMin = _blocks.y;
	glibContextBlock.clippingRegion.yMax = _blocks.height;

	draw_lives();

	GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNarrow6x8);
	GLIB_drawString(&glibContext,
					  "Score: ",
					  15,
					  70,
					  5,
					  true);







	DMD_updateDisplay(); // Refresh display

	//GPIO_PinOutToggle(LEDPORT,LEDPIN);
	Timer0_OF = false;

}

void memlcd_mainmenu(uint8_t a_main_menu){



  reset_game();



  /* Clear the LCD screen with background color */
  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;
  GLIB_clear(&glibContext);

  /* Draw the title "BREAKOUT" centered near the top of the screen */
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNormal8x8);
  GLIB_drawString(&glibContext,
                  "BREAKOUT",
                  8,                          // Length of the string "BREAKOUT"
                  30,                         // X-position for centering
                  10,                         // Y-position for title near the top
                  true);                      // Transparency mode

  /* Switch to a moderately large font for the menu options */
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNormal8x8);

  for(int x = 0; x < 4; x++){

      if(x == a_main_menu){

          glibContext.backgroundColor = Black;
          glibContext.foregroundColor = White;
      }

      else {

          glibContext.backgroundColor = White;
          glibContext.foregroundColor = Black;

      }

      GLIB_drawString(&glibContext,
                      menu_items[x].str,
                      menu_items[x].strlen,       // Length of the string "Start"
                      30,                         // X-position for centering
                      menu_items[x].yPos,         // Y-position for "Start" option
                      true);                      // Transparency mode

  }

  DMD_updateDisplay();

}

/*local strucuture Initiliasation */

typedef struct setting_item_t{
  char str [20];
  uint8_t strlen;
  uint8_t yPos;
}setting_item_t;


/*Arguments */

setting_item_t setting_items[5] ={
    {
    .str = "Ball Speed",
    .strlen = 10,
    .yPos = 30
    },

    {
    .str = "Paddle Sensitivity",
    .strlen = 17,
    .yPos = 50
    },
    {
    .str = "Number of balls",
    .strlen = 15,
    .yPos = 70
    },
    {
    .str = "Ball size",
    .strlen = 9,
    .yPos = 90
    },
    {
    .str = "Main menu",
    .strlen = 9,
    .yPos = 120
    }
};

void memlcd_settings(uint8_t a_settings_menu,int *a_game_settings ){

  char game_settings[50];

  printf("\nGame setting: %d",a_game_settings);

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;

  /* Clear the LCD screen */
  GLIB_clear(&glibContext);

  /* Draw "Settings" centered at the top */
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNormal8x8);
  GLIB_drawString(&glibContext,
                  "Settings",
                  8,                          // Length of the string "Settings"
                  25,                         // X-position for centering
                  10,                         // Y-position near the top
                  true);                      // Transparency mode

  /* Switch to a smaller font for the settings options */
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNarrow6x8);

  for(int x = 0; x < 5; x++){

        if(x == a_settings_menu){

            glibContext.backgroundColor = Black;
            glibContext.foregroundColor = White;

            sprintf(game_settings,"%d", a_game_settings);

            GLIB_drawString(&glibContext,
                            game_settings,
                            5,                             // Length of the string "Start"
                            10,                            // X-position for centering
                            setting_items[x].yPos,         // Y-position for "Start" option
                            true);                         // Transparency mode
        }

        else {

            glibContext.backgroundColor = White;
            glibContext.foregroundColor = Black;

        }

        GLIB_drawString(&glibContext,
                        setting_items[x].str,
                        setting_items[x].strlen,       // Length of the string "Start"
                        30,                            // X-position for centering
                        setting_items[x].yPos,         // Y-position for "Start" option
                        true);                         // Transparency mode

  }

  /* Update the display */
  DMD_updateDisplay();

}

int sort_leaderboard(int *score_array, int score){

  for (int i = 0; i < position; i++){

      if (leaderboard_score.score_array[i] < leaderboard_score.score_array[i+1] ){

          int temp = score_array[i+1];
          leaderboard_score.score_array[i+1] = leaderboard_score.score_array[i];
          leaderboard_score.score_array[i] = temp;

      }
  }

  printf("\nscore AFTER sorting: %d",score);
  printf("\n 1 score array %d", score_array[0]);
  printf("\n 2 score array %d", score_array[1]);
  printf("\n 3 score array %d", score_array[2]);
  printf("\n 4 score array %d", score_array[3]);
  printf("\n 5 score array %d", score_array[4]);

}




int memlcd_leaderboard(int *score_array, int score){

  /* Clear the LCD screen and set the global background to white */
  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;
  GLIB_clear(&glibContext);

  /* Draw "Leaderboard" centered at the top*/
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNormal8x8);
  GLIB_drawString(&glibContext,
                  "Leaderboard ",
                  11,                         // Length includes extra space
                  20,                         // X-position for centering
                  10,                         // Y-position near the top
                  true);                      // Transparency mode

  /* Set font for the leaderboard items */
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNarrow6x8);

  //score_array[2] = score;

  /* Display ranks and scores in table format */



  for (int i = 0; i < 5; i++){


      char rankStr[4];
      char scoreStr[6];

      /* Convert rank (1-5) and score to strings */
      snprintf(rankStr, sizeof(rankStr), "%d.", i + 1);   // Rank, like "1.", "2.", etc.
      snprintf(scoreStr, sizeof(scoreStr), "%d", leaderboard_score.score_array[i]); // Score, like "1000", "950", etc.

      /* Draw rank on the left column */
      GLIB_drawString(&glibContext,
                      rankStr,
                      strlen(rankStr),           // Length of the rank string
                      10,                        // X-position for rank column
                      30 + (i * 15),             // Y-position for each row, spaced by 15
                      true);                     // Transparency mode

      /* Draw score on the right column */
      GLIB_drawString(&glibContext,
                      scoreStr,
                      strlen(scoreStr),          // Length of the score string
                      70,                        // X-position for score column
                      30 + (i * 15),             // Y-position for each row, spaced by 15
                      true);                     // Transparency mod



        }

  /* Highlight "Return to Main Menu" */
  glibContext.backgroundColor = Black;         // Set background to black for highlight
  glibContext.foregroundColor = White;         // Set text color to white
  GLIB_drawString(&glibContext,
                  "Return to Main Menu ",
                  19,                          // Length includes extra space
                  10,                          // X-position for centering
                  115,                         // Y-position near the bottom
                  true);                       // Transparency mode

  /* Reset colors after highlighting */
  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;



  /* Update the display */
  DMD_updateDisplay();

}

/*local strucuture Initiliasation */
typedef struct game_over_t{
  char str [20];
  uint8_t strlen;
  uint8_t yPos;
}game_over_t;

/*Arguments*/
game_over_t gameover_items[3] ={
    {

    .str = "Play Again",
    .strlen = 10,
    .yPos = 70
    },

    {

    .str = "Leaderboard",
    .strlen = 11,
    .yPos = 90
    },

    {

    .str = "Main Menu",
    .strlen = 9,
    .yPos = 110
    },

};




void memlcd_endgame(uint8_t a_gameover_menu){



  reset_game();

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;
  /* Clear the LCD screen */
  GLIB_clear(&glibContext);

  /* Draw "Game Over" centered near the middle of the screen */
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNormal8x8);
  GLIB_drawString(&glibContext,
                  "Game Over",
                  9,                          // Length of the string "Game Over"
                  25,                         // X-position to center
                  30,                         // Y-position for title
                  true);                      // Transparency mode


  for(int x = 0; x < 3; x++){

      if(x == a_gameover_menu){

          glibContext.backgroundColor = Black;
          glibContext.foregroundColor = White;

      }

      else {

          glibContext.backgroundColor = White;
          glibContext.foregroundColor = Black;

      }

      GLIB_drawString(&glibContext,
                      gameover_items[x].str,
                      gameover_items[x].strlen,       // Length of the string "Start"
                      30,                             // X-position for centering
                      gameover_items[x].yPos,         // Y-position for "Start" option
                      true);                          // Transparency mode

      }


  /* Update the display */
  DMD_updateDisplay();

}




void memlcd_error(void){

      /* Fill lcd with background color */
      GLIB_clear(&glibContext);

      /* Use Narrow font */
      GLIB_setFont(&glibContext, (GLIB_Font_t *) &GLIB_FontNarrow6x8);

      /* Draw initial text on the memory lcd display */
      GLIB_drawStringOnLine(&glibContext,
                            "ERROR",
                            currentLine,
                            GLIB_ALIGN_LEFT,
                            5,
                            5,
                            true);
      DMD_updateDisplay();

}



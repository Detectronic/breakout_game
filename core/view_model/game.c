
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "core/main.h"

#include "app.h"
#include "glib.h"
#include "game.h"
#include "core/model/settings.h"
#include "core/model/flash.h"
#include "core/view/screen.h"
#include "core/model/Timer0.h"

lives = 3;


void initializeBlocks(void) {
  int counter = 0;

    for (int y = 1; y < ROWS_OF_BLOCKS; y++) {

        for (int x = 0; x < COLUMNS_OF_BLOCKS; x++) {

            game.blocks[y][x].active = true;  // Set block as active
            game.blocks[y][x].xMin = (x * BLOCK_OFFSET) + BLOCK_PADDING; // Calculate block's X bounds
            game.blocks[y][x].xMax = game.blocks[y][x].xMin + BLOCK_WIDTH;
            game.blocks[y][x].yMin = (y * BLOCK_OFFSET) + BLOCK_PADDING; // Calculate block's Y bounds
            game.blocks[y][x].yMax = game.blocks[y][x].yMin + BLOCK_HEIGHT;
            game.blocks[y][x].id = counter;
            counter++;
        }
    }
}

/***************************************************************************//**
 * Handle collision with a block and adjust the ball's direction.
 ******************************************************************************/

void handleBlockCollision(Block_t *block) {

  for (int x = 0; x < game.settings.number_of_balls; x++){

      if (!block->active) return;

      // Determine the side of collision
      bool hitHorizontal = (game.balls[x].YPos <= block->yMin || game.balls[x].YPos >= block->yMax); // Top/Bottom
      bool hitVertical = (game.balls[x].XPos <= block->xMin || game.balls[x].XPos >= block->xMax);   // Left/Right

      if (hitHorizontal) {
          game.balls[x].YDir *= -1; // Reverse vertical direction
      }

      if (hitVertical) {
          game.balls[x].XDir *= -1; // Reverse horizontal direction
      }

      // Add slight randomness
      game.balls[x].XDir += (rand() % 3 - 1) * 0.1; // Adjust X slightly by -0.1, 0, or +0.1
      game.balls[x].YDir += (rand() % 3 - 1) * 0.1; // Adjust Y slightly by -0.1, 0, or +0.1

      normalizeDirection();
  }

}


/***************************************************************************//**
 * For consistent speed.
 ******************************************************************************/
void normalizeDirection(void) {
    // Ensure the ball speed is consistent
    float magnitude = sqrt(game.balls[0].XDir * game.balls[0].XDir + game.balls[0].YDir * game.balls[0].YDir);
    game.balls[0].XDir /= magnitude;
    game.balls[0].YDir /= magnitude;



    // Prevent perfectly vertical or horizontal movement
    if (fabs(game.balls[0].XDir) < 0.1) {

        if (game.balls[0].XDir < 0){
            game.balls[0].XDir = -0.1;
        }
        else{
            game.balls[0].XDir = 0.1;
        }

    }
    if (fabs(game.balls[0].YDir) < 0.1) {

        if (game.balls[0].YDir < 0){
            game.balls[0].YDir = -0.1;
        }
        else{
             game.balls[0].YDir = 0.1;
        }
    }
}


bool CheckBallObjCollision(float objXPos, float objYPos , uint16_t width , uint16_t height){

  for (int x = 0; x < game.settings.number_of_balls; x++){


      //Are we making contact with ANY edge of the paddle
       if (game.balls[x].YPos + game.balls[0].Radius >= objYPos && game.balls[x].YPos <= objYPos + height  && game.balls[x].XPos + game.balls[x].Radius >= objXPos && game.balls[x].XPos <= objXPos + width) {

       //printf("TOUCHED paddle\n");
       //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

       if (!game.balls[x].Collision){
           game.balls[x].Collision = true;

           //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

           if (game.balls[x].YPos + game.balls[x].Radius == objYPos && game.balls[x].YDir > 0){

              //printf("Bounced of the TOP object\n");
              game.balls[x].YDir *= -1;
              return true;
          }

           else if (game.balls[x].YPos == objYPos + height && game.balls[x].YDir < 0){
               //printf("Bounced of the BOTTOM object\n");
               game.balls[x].YDir *= -1;
               return true;
          }

          else if (game.balls[x].XPos + game.balls[x].Radius == objXPos &&  game.balls[x].XDir > 0 ){
              //printf("Bounced of the LEFT object\n");
              game.balls[x].XDir *= -1;
              return true;
          }

          else if (game.balls[0].XPos == objXPos + width &&  game.balls[0].XDir < 0 ){
              //printf("Bounced of the RIGHT object\n");
              game.balls[x].XDir *= -1;
              return true;
          }

       }
  }

       else {
           game.balls[x].Collision = false;
   }

}


     return false;
}

ScreenWipe_t updateBallPosition(void) {

    int screenWidth = 127;
    int screenHeight = 127;
    int paddlesYposition = 110;



    for (int x = 0; x < game.settings.number_of_balls;x++){



        if (game.balls[x].InPlay){


        	float frame_rate_multi = 1.0f / TIMER0_FREQUENCY;


            // Update ball's position
            game.balls[x].XPos += game.balls[x].XDir * game.balls[x].Speed * frame_rate_multi;
            game.balls[x].YPos += game.balls[x].YDir * game.balls[x].Speed * frame_rate_multi;


            ScreenWipe_t _return;
					_return.x = game.balls[x].XPos;
					_return.y = game.balls[x].YPos;
					_return.width = game.balls[x].XPos + game.balls->Radius;
					_return.height = game.balls[x].YPos + game.balls->Radius;





            // Bounce off the left and right screen edges
            if (game.balls[x].XPos <= 0 || game.balls[x].XPos >= screenWidth) {
                //printf("Bounced of the side walls\n");
                //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , game.balls[0].XDir , game.balls[0].YDir , game.balls[0].XPos , game.balls[0].YPos);


                game.balls[x].XDir *= -1;
            }
            // Bounce off top
            if (game.balls[x].YPos <= 0) {
                //printf("Bounced of the top wall\n");
                //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , game.balls[0].XDir , game.balls[0].YDir , game.balls[0].XPos , game.balls[0].YPos);


                game.balls[x].YDir *= -1;
            }

            //Bounces on bottom of the screen
            if (game.balls[x].YPos > screenHeight) {
                game.balls[x].InPlay = false;
                number_of_balls_out_game++;

                if (number_of_balls_out_game == game.settings.number_of_balls){
                    atLeastOneBallActive = false;
                }

                //printf("Bottom wall, out the game\n");

            }

            // Check for collision with the paddle
            CheckBallObjCollision(game.paddles[0].XPos, paddlesYposition , game.settings.paddle_width  , paddleHeight);

            // Check for collision with game.blocks
            for (int y = 0; y < 7; y++) {

                for (int x = 0; x < 12; x++) {

                    if (game.blocks[y][x].active){

                        if(CheckBallObjCollision(game.blocks[y][x].xMax, game.blocks[y][x].yMax , BLOCK_WIDTH , BLOCK_HEIGHT)){

                            game.blocks[y][x].active = false;

                            score++;

                            leaderboard_score.score_array[position] = score;
                            flash_save_user_data();

                        }
                    }

                }
            }

            return _return;

        }if (!atLeastOneBallActive){
            state = ENDGAME;

            lives--;


        }



}



}

ScreenWipe_t drawBlocks(GLIB_Context_t *pContext) {



    pContext->foregroundColor = Black;
    GLIB_Rectangle_t myRect;

    for (int y = 0; y < 7; y++) {

        for (int x = 0; x < 12; x++) {

            Block_t *block = &game.blocks[y][x];
            if (block->active) {



                myRect.xMin = block->xMin;
                myRect.yMin = block->yMin;
                myRect.xMax = block->xMax;
                myRect.yMax = block->yMax;

                GLIB_drawRectFilled(pContext, &myRect);


            }
        }
    }

    ScreenWipe_t _return;
		_return.x = myRect.xMin;
		_return.y = myRect.yMin;
		_return.width = myRect.xMax;
		_return.height = myRect.yMax;

		return _return;
}


/***************************************************************************//**
 * Update the paddle position and handle screen edges.
 ******************************************************************************/


ScreenWipe_t updatePaddlePosition(Paddle_movement_t a_paddle_movement) {

	ScreenWipe_t _return;
	_return.x = game.paddles[0].XPos;
	_return.y = 110;
	_return.width = game.paddles[0].XPos + game.settings.paddle_width;
	_return.height =  120;

    int screenWidth = 127;


    switch(a_paddle_movement){


      case NONE:

        //printf("(game)   updatePaddlePosition  ");

        buttons[0].state = false;
        buttons[0].state = false;
        break;


      case LEFT:
        if (game.paddles[0].XPos + game.settings.paddle_width >= screenWidth){
        	Pmove = NONE;
            return _return;

        }

        //printf("	(updatePaddlePosition)   MOVED(LEFT)Obeyed command");

        game.paddles[0].Speed = 2;
        game.paddles[0].Direction = 1;
        game.paddles[0].XPos += paddle_sensitivity_setting;
        break;


      case RIGHT:
        if (game.paddles[0].XPos <= 0){
        	Pmove = NONE;
            return _return;

        }

        //printf("	(updatePaddlePosition)   Moved(RIGHT)Obeyed command");

        game.paddles[0].Speed = -2;
        game.paddles[0].Direction = -1;
        game.paddles[0].XPos -= paddle_sensitivity_setting;
        break;


    }
    _return.x = game.paddles[0].XPos;
    return _return;
}

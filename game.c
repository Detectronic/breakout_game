#include <stdbool.h>
#include "app.h"
#include "memlcd_app.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "glib.h"
#include "main.h"
#include "game.h"
#include "settings.h"


void reset_game(void){

  //TEST CODE
  game.settings.paddle_width = 60;
  game.settings.number_of_balls = 2;
  game.settings.ball_size = 4;

  //ENDTEST CODE
  game.balls[0].XPos = 64.0f;
  game.balls[0].YPos = 64.0f;
  game.balls[0].XDir = 0.1f;
  game.balls[0].YDir = -1.0f;
  game.balls[0].Speed = 1.0f;
  game.balls[0].Collision = false;

  game.balls[0].Radius = game.settings.ball_size;

  game.paddles[0].XPos = 44;
  game.paddles[0].Direction = 1;
  game.paddles[0].Speed = 2;

  initializeBlocks();
}

#define ROWS_OF_BLOCKS 7
#define COLUMNS_OF_BLOCKS 12
#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 8
#define BLOCK_PADDING 2
#define BLOCK_OFFSET 10

void initializeBlocks(void) {
  int counter = 0;

    for (int y = 0; y < ROWS_OF_BLOCKS; y++) {

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

    if (!block->active) return;

    // Determine the side of collision
    bool hitHorizontal = (game.balls[0].YPos <= block->yMin || game.balls[0].YPos >= block->yMax); // Top/Bottom
    bool hitVertical = (game.balls[0].XPos <= block->xMin || game.balls[0].XPos >= block->xMax);   // Left/Right

    if (hitHorizontal) {
        game.balls[0].YDir *= -1; // Reverse vertical direction
    }

    if (hitVertical) {
        game.balls[0].XDir *= -1; // Reverse horizontal direction
    }

    // Add slight randomness
    game.balls[0].XDir += (rand() % 3 - 1) * 0.1; // Adjust X slightly by -0.1, 0, or +0.1
    game.balls[0].YDir += (rand() % 3 - 1) * 0.1; // Adjust Y slightly by -0.1, 0, or +0.1

    normalizeDirection();

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
  //Are we making contact with ANY edge of the paddle
     if (game.balls[0].YPos + game.balls[0].Radius >= objYPos && game.balls[0].YPos <= objYPos + height  && game.balls[0].XPos + game.balls[0].Radius >= objXPos && game.balls[0].XPos <= objXPos + width) {

     printf("TOUCHED paddle\n");
     //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

     if (!game.balls[0].Collision){
         game.balls[0].Collision = true;

         //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

         if (game.balls[0].YPos + game.balls[0].Radius == objYPos && game.balls[0].YDir > 0){

            printf("Bounced of the TOP object\n");
            game.balls[0].YDir *= -1;
            return true;
        }

         else if (game.balls[0].YPos == objYPos + height && game.balls[0].YDir < 0){
             printf("Bounced of the BOTTOM object\n");
             game.balls[0].YDir *= -1;
             return true;
        }

        else if (game.balls[0].XPos + game.balls[0].Radius == objXPos &&  game.balls[0].XDir > 0 ){
            printf("Bounced of the LEFT object\n");
            game.balls[0].XDir *= -1;
            return true;
        }

        else if (game.balls[0].XPos == objXPos + width &&  game.balls[0].XDir < 0 ){
            printf("Bounced of the RIGHT object\n");
            game.balls[0].XDir *= -1;
            return true;
        }

     }
}

     else {
         game.balls[0].Collision = false;
 }

     return false;
}

void updateBallPosition(void) {

    int screenWidth = 128;
    int screenHeight = 128;
    int paddlesYposition = 110;

    // Update ball's position
    game.balls[0].XPos += game.balls[0].XDir * game.balls[0].Speed;
    game.balls[0].YPos += game.balls[0].YDir * game.balls[0].Speed;

    // Bounce off the left and right screen edges
    if (game.balls[0].XPos <= 0 || game.balls[0].XPos >= screenWidth) {
        printf("Bounced of the side walls\n");
        printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , game.balls[0].XDir , game.balls[0].YDir , game.balls[0].XPos , game.balls[0].YPos);


        game.balls[0].XDir *= -1;
    }
    // Bounce off top
    if (game.balls[0].YPos <= 0) {
        printf("Bounced of the top wall\n");
        printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , game.balls[0].XDir , game.balls[0].YDir , game.balls[0].XPos , game.balls[0].YPos);


        game.balls[0].YDir *= -1;
    }
    //Bounces on bottom of the screen
    if (game.balls[0].YPos > screenHeight) {
        printf("Bottom wall, out the game\n");
        state = ENDGAME;
    }

    // Check for collision with the paddle
    CheckBallObjCollision(game.paddles[0].XPos, paddlesYposition , game.settings.paddle_width  , paddleHeight);

    // Check for collision with game.blocks
    for (int y = 0; y < 7; y++) {

        for (int x = 0; x < 12; x++) {

            if (game.blocks[y][x].active){

                if(CheckBallObjCollision(game.blocks[y][x].xMax, game.blocks[y][x].yMax , 8 , 8)){

                    game.blocks[y][x].active = false;
                }
            }

        }
    }

}

void drawBlocks(GLIB_Context_t *pContext) {

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
}


/***************************************************************************//**
 * Update the paddle position and handle screen edges.
 ******************************************************************************/


void updatePaddlePosition(Paddle_movement_t a_paddle_movement) {

    int screenWidth = 128;


    switch(a_paddle_movement){

      case NONE:

        buttons[0].state = false;
        buttons[0].state = false;
        break;


      case RIGHT:
        if (game.paddles[0].XPos <= 0){

            return;

        }

        game.paddles[0].Speed = -2;
        game.paddles[0].Direction = -1;
        game.paddles[0].XPos -= 1;
        break;


      case LEFT:
        if (game.paddles[0].XPos + 40 >= screenWidth){

            return;

        }

        game.paddles[0].Speed = 2;
        game.paddles[0].Direction = 1;
        game.paddles[0].XPos += 1;
        break;

    }

}

#include <stdbool.h>
#include "app.h"
#include "memlcd_app.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "glib.h"
#include "game.h"
#include "main.h"



void reset_game(void){
  ball.XPos = 64.0f;
  ball.YPos = 64.0f;
  ball.XDir = 0.1f;
  ball.YDir = -1.0f;
  ball.Speed = 1.0f;
  ball.Collision = false;

  paddle.XPos = 44;
  paddle.Direction = 1;
  paddle.Speed = 2;

  initializeBlocks();
}

void initializeBlocks(void) {
  int counter = 0;

    for (int y = 0; y < 7; y++) {

        for (int x = 0; x < 12; x++) {

            blocks[y][x].active = true;  // Set block as active
            blocks[y][x].xMin = (x * 10) + 2; // Calculate block's X bounds
            blocks[y][x].xMax = blocks[y][x].xMin + 8;
            blocks[y][x].yMin = (y * 10) + 2; // Calculate block's Y bounds
            blocks[y][x].yMax = blocks[y][x].yMin + 8;
            blocks[y][x].id = counter;
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
    bool hitHorizontal = (ball.YPos <= block->yMin || ball.YPos >= block->yMax); // Top/Bottom
    bool hitVertical = (ball.XPos <= block->xMin || ball.XPos >= block->xMax);   // Left/Right

    if (hitHorizontal) {
        ball.YDir *= -1; // Reverse vertical direction
    }

    if (hitVertical) {
        ball.XDir *= -1; // Reverse horizontal direction
    }

    // Add slight randomness
    ball.XDir += (rand() % 3 - 1) * 0.1; // Adjust X slightly by -0.1, 0, or +0.1
    ball.YDir += (rand() % 3 - 1) * 0.1; // Adjust Y slightly by -0.1, 0, or +0.1

    normalizeDirection();

    block->active = false; // Deactivate the block

}


/***************************************************************************//**
 * For consistent speed.
 ******************************************************************************/
void normalizeDirection(void) {
    // Ensure the ball speed is consistent
    float magnitude = sqrt(ball.XDir * ball.XDir + ball.YDir * ball.YDir);
    ball.XDir /= magnitude;
    ball.YDir /= magnitude;

    // Prevent perfectly vertical or horizontal movement
    if (fabs(ball.XDir) < 0.1) {

        if (ball.XDir < 0){
            ball.XDir = -0.1;
        }
        else{
            ball.XDir = 0.1;
        }

    }
    if (fabs(ball.YDir) < 0.1) {

        if (ball.YDir < 0){
            ball.YDir = -0.1;
        }
        else{
             ball.YDir = 0.1;
        }
    }
}


bool CheckBallPaddleCollision(float paddleXPos, float paddleYPos , uint16_t width , uint16_t height){
  //Are we making contact with ANY edge of the paddle
     if (ball.YPos + 4 >= paddleYPos && ball.YPos <= paddleYPos + height  && ball.XPos + 4 >= paddleXPos && ball.XPos <= paddleXPos + width) {

     printf("TOUCHED paddle\n");
     //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

     if (!ball.Collision){
         ball.Collision = true;

         //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

         if (ball.YPos + 4 == paddleYPos && ball.YDir > 0){

            printf("Bounced of the TOP object\n");
            ball.YDir *= -1;
            return true;
        }

         else if (ball.YPos == paddleYPos + height && ball.YDir < 0){
             printf("Bounced of the BOTTOM object\n");
             ball.YDir *= -1;
             return true;
        }

        else if (ball.XPos + 4 == paddleXPos &&  ball.XDir > 0 ){
            printf("Bounced of the LEFT object\n");
            ball.XDir *= -1;
            return true;
        }

        else if (ball.XPos == paddleXPos + width &&  ball.XDir < 0 ){
            printf("Bounced of the RIGHT object\n");
            ball.XDir *= -1;
            return true;
        }

     }
}

     else {
         ball.Collision = false;
 }

     return false;
}

void updateBallPosition(void) {

    int screenWidth = 128;
    int screenHeight = 128;

    // Update ball's position
    ball.XPos += ball.XDir * ball.Speed;
    ball.YPos += ball.YDir * ball.Speed;

    // Bounce off the left and right screen edges
    if (ball.XPos <= 0 || ball.XPos >= screenWidth) {
        printf("Bounced of the side walls\n");
        printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);


        ball.XDir *= -1;
    }
    // Bounce off top or endgame of bottom of screen
    if (ball.YPos <= 0) {
        printf("Bounced of the top wall\n");
        printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);


        ball.YDir *= -1;
    }
    if (ball.YPos > screenHeight) {
        printf("Bottom wall, out the game\n");
        state = ENDGAME;
    }

    // Check for collision with the paddle
    CheckBallPaddleCollision(paddle.XPos, paddleYposition , paddleWidth , paddleHeight);

    // Check for collision with blocks
    for (int y = 0; y < 7; y++) {

        for (int x = 0; x < 12; x++) {

            Block_t *block = &blocks[y][x];

            if (blocks[y][x].active){

                if(CheckBallPaddleCollision(blocks[y][x].xMax, blocks[y][x].yMax , 8 , 8)){

                    blocks[y][x].active = false;
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

            Block_t *block = &blocks[y][x];
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
        if (paddle.XPos <= 0){

            return;

        }

        paddle.Speed = -2;
        paddle.Direction = -1;
        paddle.XPos -= 1;
        break;


      case LEFT:
        if (paddle.XPos + 40 >= screenWidth){

            return;

        }

        paddle.Speed = 2;
        paddle.Direction = 1;
        paddle.XPos += 1;
        break;

    }

}







#include <stdbool.h>
#include "app.h"
#include "memlcd_app.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "glib.h"
#include "game.h"
#include "main.h"
#include "settings.h"


void reset_game(void){
  balls[1].XPos = 64.0f;
  balls[1].YPos = 64.0f;
  balls[1].XDir = 0.1f;
  balls[1].YDir = -1.0f;
  balls[1].Speed = 1.0f;
  balls[1].Collision = false;

  paddles[1].XPos = 44;
  paddles[1].Direction = 1;
  paddles[1].Speed = 2;

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
    bool hitHorizontal = (balls[1].YPos <= block->yMin || balls[1].YPos >= block->yMax); // Top/Bottom
    bool hitVertical = (balls[1].XPos <= block->xMin || balls[1].XPos >= block->xMax);   // Left/Right

    if (hitHorizontal) {
        balls[1].YDir *= -1; // Reverse vertical direction
    }

    if (hitVertical) {
        balls[1].XDir *= -1; // Reverse horizontal direction
    }

    // Add slight randomness
    balls[1].XDir += (rand() % 3 - 1) * 0.1; // Adjust X slightly by -0.1, 0, or +0.1
    balls[1].YDir += (rand() % 3 - 1) * 0.1; // Adjust Y slightly by -0.1, 0, or +0.1

    normalizeDirection();

    block->active = false; // Deactivate the block

}


/***************************************************************************//**
 * For consistent speed.
 ******************************************************************************/
void normalizeDirection(void) {
    // Ensure the ball speed is consistent
    float magnitude = sqrt(balls[1].XDir * balls[1].XDir + balls[1].YDir * balls[1].YDir);
    balls[1].XDir /= magnitude;
    balls[1].YDir /= magnitude;

    // Prevent perfectly vertical or horizontal movement
    if (fabs(balls[1].XDir) < 0.1) {

        if (balls[1].XDir < 0){
            balls[1].XDir = -0.1;
        }
        else{
            balls[1].XDir = 0.1;
        }

    }
    if (fabs(balls[1].YDir) < 0.1) {

        if (balls[1].YDir < 0){
            balls[1].YDir = -0.1;
        }
        else{
             balls[1].YDir = 0.1;
        }
    }
}


bool CheckBallObjCollision(float objXPos, float objYPos , uint16_t width , uint16_t height){
  //Are we making contact with ANY edge of the paddle
     if (balls[1].YPos + 4 >= objYPos && balls[1].YPos <= objYPos + height  && balls[1].XPos + 4 >= objXPos && balls[1].XPos <= objXPos + width) {

     printf("TOUCHED paddle\n");
     //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

     if (!balls[1].Collision){
         balls[1].Collision = true;

         //printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , ball.XDir , ball.YDir , ball.XPos , ball.YPos);

         if (balls[1].YPos + 4 == objYPos && balls[1].YDir > 0){

            printf("Bounced of the TOP object\n");
            balls[1].YDir *= -1;
            return true;
        }

         else if (balls[1].YPos == objYPos + height && balls[1].YDir < 0){
             printf("Bounced of the BOTTOM object\n");
             balls[1].YDir *= -1;
             return true;
        }

        else if (balls[1].XPos + 4 == objXPos &&  balls[1].XDir > 0 ){
            printf("Bounced of the LEFT object\n");
            balls[1].XDir *= -1;
            return true;
        }

        else if (balls[1].XPos == objXPos + width &&  balls[1].XDir < 0 ){
            printf("Bounced of the RIGHT object\n");
            balls[1].XDir *= -1;
            return true;
        }

     }
}

     else {
         balls[1].Collision = false;
 }

     return false;
}

void updateBallPosition(void) {

    int screenWidth = 128;
    int screenHeight = 128;
    int paddlesYposition = 110;

    // Update ball's position
    balls[1].XPos += balls[1].XDir * balls[1].Speed;
    balls[1].YPos += balls[1].YDir * balls[1].Speed;

    // Bounce off the left and right screen edges
    if (balls[1].XPos <= 0 || balls[1].XPos >= screenWidth) {
        printf("Bounced of the side walls\n");
        printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , balls[1].XDir , balls[1].YDir , balls[1].XPos , balls[1].YPos);


        balls[1].XDir *= -1;
    }
    // Bounce off top
    if (balls[1].YPos <= 0) {
        printf("Bounced of the top wall\n");
        printf("XDir  : %f , YDir : %f  , XPos : %f , YPos : %f \n" , balls[1].XDir , balls[1].YDir , balls[1].XPos , balls[1].YPos);


        balls[1].YDir *= -1;
    }
    //Bounces on bottom of the screen
    if (balls[1].YPos > screenHeight) {
        printf("Bottom wall, out the game\n");
        state = ENDGAME;
    }

    // Check for collision with the paddle
    CheckBallObjCollision(paddles[1].XPos, paddlesYposition , paddleWidth , paddleHeight);

    // Check for collision with blocks
    for (int y = 0; y < 7; y++) {

        for (int x = 0; x < 12; x++) {

            Block_t *block = &blocks[y][x];

            if (blocks[y][x].active){

                if(CheckBallObjCollision(blocks[y][x].xMax, blocks[y][x].yMax , 8 , 8)){

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
        if (paddles[1].XPos <= 0){

            return;

        }

        paddles[1].Speed = -2;
        paddles[1].Direction = -1;
        paddles[1].XPos -= 1;
        break;


      case LEFT:
        if (paddles[1].XPos + 40 >= screenWidth){

            return;

        }

        paddles[1].Speed = 2;
        paddles[1].Direction = 1;
        paddles[1].XPos += 1;
        break;

    }

}







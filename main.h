#ifndef __MAIN_H__
#define __MAIN_H__

/***************************************************************************//**
 * Update the ball position and handle collisions.
 ******************************************************************************/


#define HIGH true
#define LOW false
/*Defintions*/

typedef struct Button_t {
  uint8_t id;
  bool state;
  bool triggered;
}Button_t;

extern Button_t buttons[2];
#if 0
typedef struct temp_t{
  Button_t button;
  Ball_t ball;
}temp_t;

#endif




#endif

























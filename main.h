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


#endif

























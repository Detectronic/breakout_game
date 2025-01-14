/***************************************************************************//**
 * Callback on button change.
 *
 * This function overrides a weak implementation defined in the simple_button
 * module. It is triggered when the user activates one of the buttons.
 *
 ******************************************************************************/
#include "control.h"
//#include "main.h"
#include "main.h"

int DOWN = 0;
int UP = 1;


//void sl_button_on_change(const sl_button_t *handle);

void sl_button_on_change(const sl_button_t *handle){

  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
      /* When button 0 is pushed down*/
    if (&BUTTON_INSTANCE_0 == handle) {

        buttons[0].state = HIGH;
        buttons[0].triggered = true;

    } else if (&BUTTON_INSTANCE_1 == handle) {

        /* When button 1 is pushed down*/
        buttons[1].state = HIGH;
        buttons[1].triggered = true;

    }
  }
  else {

      /* When button 0 is released*/
      if (&BUTTON_INSTANCE_0 == handle) {

            buttons[0].state = LOW;
            buttons[0].triggered = true;

        } else if (&BUTTON_INSTANCE_1 == handle) {

            /* When button 1 is released*/
            buttons[1].state = LOW;
            buttons[1].triggered = true;

        }
      }
    }

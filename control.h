#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stdbool.h>
#include <stdint.h>
#include "sl_simple_button_instances.h"

#define HIGH true
#define LOW false


extern int DOWN;
extern int UP;


// Button instance definitions
#ifndef BUTTON_INSTANCE_0
#define BUTTON_INSTANCE_0   sl_button_btn0
#endif

#ifndef BUTTON_INSTANCE_1
#define BUTTON_INSTANCE_1   sl_button_btn1
#endif



#endif

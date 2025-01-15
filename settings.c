
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "settings.h"

// Paddle initilazation

Paddle_t paddles [2] = {
    {
        .XPos = 44,
        .Direction = 1,
        .Speed = 2

    },
    {
        .XPos = 44,
        .Direction = -1,
        .Speed = 4

    }

};

// Ball initilazation
Ball_t balls [5] = {
    {
        .XPos = 110.0f,
        .YPos = 110.0f,
        .XDir = -1.0f,
        .YDir =  0.0f,
        .Speed = 1.0f,
        .Radius = 4.0f

    },
    {
        .XPos = 110.0f,
        .YPos = 110.0f,
        .XDir = -1.0f,
        .YDir =  0.0f,
        .Speed = 2.0f,
        .Radius = 4.0f


    },
    {
        .XPos = 110.0f,
        .YPos = 110.0f,
        .XDir = -1.0f,
        .YDir =  0.0f,
        .Speed = 3.0f,
        .Radius = 4.0f

    },
    {
        .XPos = 110.0f,
        .YPos = 110.0f,
        .XDir = -1.0f,
        .YDir =  0.0f,
        .Speed = 4.0f,
        .Radius = 4.0f

    },
    {
        .XPos = 110.0f,
        .YPos = 110.0f,
        .XDir = -1.0f,
        .YDir =  0.0f,
        .Speed = 5.0f,
        .Radius = 4.0f

    }

};

// New declaration
Block_t blocks[7][12];



























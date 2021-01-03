#include "Led.h"

//****************************************************************************************
//Led (index)
Led::Led(uint8_t index)
{
    index = index;

    //calculate corresponding channel for tlc5940
    channel_r = (index*3);
    channel_g = (index*3 + 1);
    channel_b = (index*3 + 2);

    //set led to idle color
    last_r = 30;
    last_g = 30;
    last_b = 30;

    new_r = 30;
    new_g = 30;
    new_b = 30;
}

void Led::newValue(uint8_t r, uint8_t g, uint8_t b)
{
    new_r = r;
    new_g = g;
    new_b = b;
}



#include "Led.h"
#include "Tlc5940.h"

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

    _busy = false;
}

void Led::newValue(uint8_t r, uint8_t g, uint8_t b)
{
    new_r = r;
    new_g = g;
    new_b = b;

    //isLedColorChaged = true;
}

void Led::updateTime(unsigned long time)
{
    _time = time;
}

unsigned long Led::getTime()
{
    return _time;
}

//set gs value for this led
void Led::update()
{
    //if value does not need to be updated
    if (new_r == last_r && new_g == last_g && new_b == last_b)
    {
        return;
    }
    

    Tlc.set(channel_r, new_r);
    Tlc.set(channel_g, new_g);
    Tlc.set(channel_b, new_b);

    last_r = new_r;
    last_g = new_g;
    last_b = new_b;
}




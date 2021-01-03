
#ifndef Led_h
#define Led_h

#include <arduino.h>

//************************************************************************
//LED (index)
class Led
{
  public:
    uint8_t last_r;
    uint8_t last_g;
    uint8_t last_b;

    uint8_t new_r;
    uint8_t new_g;
    uint8_t new_b;

    int index; //corresponding led index number, 0-13

//corresponding pin in tlc
    uint8_t channel_r;
    uint8_t channel_g;
    uint8_t channel_b;

    //
    Led(uint8_t index);
    void newValue(uint8_t r, uint8_t g, uint8_t b);

  private:
    unsigned long _time;
    bool _busy;
};
//*************************************************************************

#endif
#include "Tlc5940.h"


///////////CONSTANTS//////////

/*Range of LED brightness, 
  RGB value form 0-255 will be maped to this, 
  then parse to TLC
  (0-4095)
*/
#define BRIGHTNESS_MIN 0  //The minimum grascale value globally
#define BRIGHTNESS_MAX 255  //The maximum grascale value globally

/*LEDs
  Corresponding index for led on panle
*/
#define LED_INPUT_SELECTOR 0
#define LED_14INCH 1
#define LED_XLR 2
#define LED_GAIN_CONTROL 3
#define LED_GAIN_CH1 4
#define LED_GAIN_CH2 5
#define LED_LINK 6
#define LED_MASTERL 7
#define LED_SLAVEL 8
#define LED_MASTERR 9
#define LED_SLAVER 10
#define LED_CLIP_INDICATOR 11
#define LED_CLIP_CH1 12
#define LED_CLIP_CH2 13

void setup()
{
  // Call Tlc.init() to setup the tlc.
  Tlc.init();
}

void loop()
{
  
}

///////////Utility Methods/////////////

int GetGrayscaleValue(uint8_t value)
{
  return map(value, 0, 255, BRIGHTNESS_MIN, BRIGHTNESS_MAX);
}
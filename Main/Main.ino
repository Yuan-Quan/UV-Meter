#include "Tlc5940.h"


///////////CONSTANTS//////////

/*Range of LED brightness, 
  RGB value form 0-255 will be maped to this, 
  then parse to TLC
  (0-4095)
*/
#define BRIGHTNESS_MIN 0  //The minimum grascale value globally
#define BRIGHTNESS_MAX 255  //The maximum grascale value globally

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
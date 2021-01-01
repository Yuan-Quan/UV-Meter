#include "Tlc5940.h"


///////////CONSTANTS//////////

/*Range of LED brightness, 
  RGB value form 0-255 will be maped to this, 
  then parse to TLC
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

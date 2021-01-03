#include "Led.h"
#include "Tlc5940.h"
#include <arduino.h>
#include <SPI.h>


///////////CONSTANTS//////////

/*Range of LED brightness, 
  RGB value form 0-255 will be maped to this, 
  then parse to TLC
  (0-4095)
*/
#define BRIGHTNESS_MIN 0  //The minimum grascale value globally
#define BRIGHTNESS_MAX 255  //The maximum grascale value globally

///////////VARIABLES///////////

//Led changed needs update
bool isLedColorChaged;

////////////LEDs/////////////
/*LEDs
  Corresponding index for led on panle
*/
#define LED_INPUT_SELECTOR_INDEX 0
#define LED_14INCH_INDEX 1
#define LED_XLR_INDEX 2
#define LED_GAIN_CONTROL_INDEX 3
#define LED_GAIN_CH1_INDEX 4
#define LED_GAIN_CH2_INDEX 5
#define LED_LINK_INDEX 6
#define LED_MASTERL_INDEX 7
#define LED_SLAVEL_INDEX 8
#define LED_MASTERR_INDEX 9
#define LED_SLAVER_INDEX 10
#define LED_CLIP_INDICATO_INDEXR 11
#define LED_CLIP_CH1_INDEX 12
#define LED_CLIP_CH2_INDEX 13

Led LedInputSelector(LED_INPUT_SELECTOR_INDEX);
Led Led14Inch(LED_14INCH_INDEX);
Led LedXlr(LED_XLR_INDEX);
Led LedGainControl(LED_GAIN_CONTROL_INDEX);
Led LedGainCh1(LED_GAIN_CH1_INDEX);
Led LedGainCh2(LED_GAIN_CH2_INDEX);
Led LedLink(LED_LINK_INDEX);
Led LedMasterL(LED_MASTERL_INDEX);
Led LedMasterR(LED_MASTERR_INDEX);
Led LedSlaveL(LED_SLAVEL_INDEX);
Led LedSlaveR(LED_SLAVER_INDEX);
Led LedClipIndicator(LED_CLIP_INDICATO_INDEXR);
Led LedClipCh1(LED_CLIP_CH1_INDEX);
Led LedClipCh2(LED_CLIP_CH2_INDEX);


///////////LED ARRAY///////////

Led *LEDs[] {
  &LedInputSelector, 
  &Led14Inch, 
  &LedXlr, 
  &LedGainControl, 
  &LedGainCh1, 
  &LedGainCh2, 
  &LedLink, 
  &LedMasterL, 
  &LedMasterR, 
  &LedSlaveL, 
  &LedSlaveR, 
  &LedClipIndicator, 
  &LedClipCh1, 
  &LedClipCh2
};

///////////SETUP & LOOP///////
void setup()
{
  // Call Tlc.init() to setup the tlc.
  Tlc.init();

  isLedColorChaged = true; //initial led
}

void loop()
{
  
  updateLeds();

  //do not update if color is not chaged
  if (isLedColorChaged)
  {
    Tlc.update(); //update gs values of tlc 
    isLedColorChaged = false;
  }
}

///////////Methods/////////////

//get the gs value for tlc, from brightness
int GetGrayscaleValue(uint8_t value)
{
  return map(value, 0, 255, BRIGHTNESS_MIN, BRIGHTNESS_MAX);
}

void updateLeds()
{
  for (size_t i = 0; i < (sizeof(LEDs)/sizeof(LEDs[0])); i++)
  {
    LEDs[i]->update();
  }
  
}

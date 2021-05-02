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

// Turn on debug statements to the serial output
#define DEBUG 0

#if DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTX(x) Serial.println(x, HEX)
#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)
#endif

///////////VARIABLES///////////

//Led changed needs update
bool isLedColorChaged;

unsigned long currentMillis = millis();

////////////LEDs/////////////
/*LEDs
  Corresponding index for led on panle
*/
#define LED_INPUT_SELECTOR_L_INDEX 16
#define LED_INPUT_SELECTOR_R_INDEX 15
#define LED_GAIN_CONTROL_L_INDEX 14
#define LED_GAIN_CONTROL_R_INDEX 13
#define LED_CLIP_INDICATO_INDEXR 12
#define LED_14INCH_INDEX 11
#define LED_XLR_INDEX 10
#define LED_GAIN_CH1_INDEX 9
#define LED_GAIN_CH2_INDEX 8
#define LED_LINK_INDEX 7
#define LED_MASTERL_INDEX 6
#define LED_SLAVEL_INDEX 5
#define LED_MASTERR_INDEX 4
#define LED_SLAVER_INDEX 3
#define LED_CLIP_CH1_INDEX 2
#define LED_CLIP_CH2_INDEX 1

Led LedInputSelectorL(LED_INPUT_SELECTOR_L_INDEX);
Led LedInputSelectorR(LED_INPUT_SELECTOR_R_INDEX);
Led LedGainControlL(LED_GAIN_CONTROL_L_INDEX);
Led LedGainControlR(LED_GAIN_CONTROL_R_INDEX);
Led LedClipIndicator(LED_CLIP_INDICATO_INDEXR);
Led Led14Inch(LED_14INCH_INDEX);
Led LedXlr(LED_XLR_INDEX);
Led LedGainCh1(LED_GAIN_CH1_INDEX);
Led LedGainCh2(LED_GAIN_CH2_INDEX);
Led LedLink(LED_LINK_INDEX);
Led LedMasterL(LED_MASTERL_INDEX);
Led LedMasterR(LED_MASTERR_INDEX);
Led LedSlaveL(LED_SLAVEL_INDEX);
Led LedSlaveR(LED_SLAVER_INDEX);
Led LedClipCh1(LED_CLIP_CH1_INDEX);
Led LedClipCh2(LED_CLIP_CH2_INDEX);


///////////LED ARRAY///////////

Led *LEDs[] {
  &LedInputSelectorL,
  &LedInputSelectorR, 
  &LedGainControlL,
  &LedGainControlR, 
  &LedClipIndicator, 
  &Led14Inch, 
  &LedXlr, 
  &LedGainCh1, 
  &LedGainCh2, 
  &LedLink, 
  &LedMasterL, 
  &LedMasterR, 
  &LedSlaveL, 
  &LedSlaveR, 
  &LedClipCh1, 
  &LedClipCh2
};

///////////SETUP & LOOP///////
void setup()
{
  if (DEBUG)
  {
    Serial.begin(115200);
    PRINTS("//////////DEBUG MODE///////");
  }
  

  // Call Tlc.init() to setup the tlc.
  Tlc.init();

  Tlc.clear();

  //set all led to white
  for (size_t i = 0; i < (sizeof(LEDs)/sizeof(LEDs[0])); i++)
  {
    setLedColor(&*LEDs[i], 30, 30, 30);
  }

  //for gain control, set two channle to master
  setLedColor(&LedMasterL, 0,100,4); //green
  setLedColor(&LedSlaveL, 10,10,10);
  setLedColor(&LedMasterR, 0,100,4); //green
  setLedColor(&LedSlaveR, 10,10,10);
  //link not enabled
  setLedColor(&LedLink, 40, 20, 2); //orange

  //clip indicator shold be dimmer
  setLedColor(&LedClipCh1,10,10,10);
  setLedColor(&LedClipCh2,10,10,10);

  //selector to quater inch
  setLedColor(&Led14Inch, 20,2,26); //purple
  setLedColor(&LedXlr, 10, 10, 10); 

  isLedColorChaged = true; //initial led
}

void loop()
{
  //update all led
  updateLeds();

  //do not update if color is not chaged
  if (isLedColorChaged)
  {
    Tlc.update(); //update gs values of tlc 
    isLedColorChaged = false;
    PRINTS("tlc update called");
  }

  if (DEBUG)
  {
    //just to slow things down
    delay(300);
  }
  
}

///////////Methods/////////////

//get the gs value for tlc, from brightness
int GetGsValue(uint8_t value)
{
  return map(value, 0, 255, BRIGHTNESS_MIN, BRIGHTNESS_MAX);
}

void updateLeds()
{
  for (size_t i = 0; i < (sizeof(LEDs)/sizeof(LEDs[0])); i++)
  {
    PRINTS("///\n ");
    LEDs[i]->update();
    PRINTX(LEDs[i]->last_r);
  }
  
}

//set the color of given led*
void setLedColor(Led* led, uint8_t r, uint8_t g, uint8_t b)
{
  led->newValue(GetGsValue(r), GetGsValue(g), GetGsValue(b));
}

#include "Led.h"
#include "Tlc5940.h"
#include <Arduino.h>
#include <SPI.h>


///////////CONSTANTS//////////

/*Range of LED brightness, 
  RGB value form 0-255 will be maped to this, 
  then parse to TLC
  (0-4095)
*/
#define BRIGHTNESS_MIN 0  //The minimum grascale value globally
#define BRIGHTNESS_MAX 4095  //The maximum grascale value globally 0-4095

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

unsigned long currentMillis = 0;

////////////LEDs/////////////
/*LEDs
  Corresponding index for led on panle
*/
#define LED_INPUT_SELECTOR_L_INDEX 15
#define LED_INPUT_SELECTOR_R_INDEX 14
#define LED_GAIN_CONTROL_L_INDEX 13
#define LED_GAIN_CONTROL_R_INDEX 12
#define LED_CLIP_INDICATO_INDEXR 11
#define LED_14INCH_INDEX 10
#define LED_XLR_INDEX 9
#define LED_GAIN_CH1_INDEX 8
#define LED_GAIN_CH2_INDEX 7
#define LED_LINK_INDEX 6
#define LED_MASTERL_INDEX 5
#define LED_SLAVEL_INDEX 4
#define LED_MASTERR_INDEX 3
#define LED_SLAVER_INDEX 2
#define LED_CLIP_CH1_INDEX 1
#define LED_CLIP_CH2_INDEX 0

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

////////////// Set static colors//////
  //set all led to white
  for (size_t i = 0; i < (sizeof(LEDs)/sizeof(LEDs[0])); i++)
  {
    setLedColor(&*LEDs[i], 100, 150, 200); //white
  }
  //input selector
  setLedColor(&Led14Inch, 5, 0, 255); //blue
  setLedColor(&LedXlr, 5, 5, 5); 

  //gain control
  setLedColor(&LedGainCh1, 0, 0, 255); //blue
  setLedColor(&LedGainCh2, 0, 0, 255); //green
  setLedColor(&LedLink, 255, 69, 0); //orange
  setLedColor(&LedMasterL, 0, 255, 0); //green
  setLedColor(&LedMasterR, 10, 10, 10); 
  setLedColor(&LedSlaveL, 10, 10, 10); 
  setLedColor(&LedSlaveR, 255, 150, 0); //yellow
  
  //clip indicator
  setLedColor(&LedClipCh1, 10, 10, 10); 
  setLedColor(&LedClipCh2, 10, 10, 10); 

  isLedColorChaged = true; //initial led
}

void loop()
{
  //update all led
  updateLeds();

  blinkLed(&LedSlaveR, 255, 150, 0, 500);

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
    delay(30);
  }
  
  //update time
  currentMillis = millis();
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
    LEDs[i]->update();
  }
  
}

//set the color of given led*
//  Led: instance of led
//  r, g, b: rgb value, 0-255
void setLedColor(Led* led, uint8_t r, uint8_t g, uint8_t b)
{
  led->newValue(GetGsValue(r), GetGsValue(g), GetGsValue(b));
}

void blinkLed(Led* led, uint8_t r, uint8_t g, uint8_t b, long interval)
{
  if (currentMillis - led->getTime() >= interval) {
    // save the last time you blinked the LED
    led->updateTime(currentMillis);

    // if the LED is off turn it on and vice-versa:
    if (led->last_r == 0) {
      led->newValue(GetGsValue(r), GetGsValue(g), GetGsValue(b));
      PRINTS("high");
    } else {
      led->newValue(0, 0, 0);
      PRINTS("low");
    }

    isLedColorChaged = true;
  }
}
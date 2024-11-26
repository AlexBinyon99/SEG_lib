
#include <SEG.h>
#include <FastLED.h>

const int WHICH_SETUP = 1; //choose from a number of setups
//1 is a neopixel ring on pin 4
//2 is an APA102 setup on 11(data) and 12(clock)

const int NUM_LEDS = 12;
const int DELAY_TIME = 5;

SEG mySEG(NUM_LEDS,WHICH_SETUP, DELAY_TIME);

void setup() {

}

void loop() { 
  mySEG.lightTest();
  delay(1000);
  mySEG.resetDisplay();
  delay(1000);
}

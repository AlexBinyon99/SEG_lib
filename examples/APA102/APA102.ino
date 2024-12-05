//WARNING
/*
If you show the '8' but with more than a single colour
the board crashes out - presumably because of current draw
*/

//NOTE
/*
when you pass in a character, it's an ASCII
so 48 - 57 are numbers 0 - 9
65 - 90 are letters A - Z
*/

#include <SEG.h>
#include <FastLED.h>

const uint8_t WHICH_SETUP = 2; //choose from a number of setups
//1 is a neopixel ring on pin 4
//2 is an APA102 setup on 11(data) and 12(clock)

const uint8_t NUM_LEDS = 43;
const uint8_t DELAY_TIME = 5;

SEG mySEG(NUM_LEDS,WHICH_SETUP, DELAY_TIME);

void setup() {
Serial.begin(250000);

}

void loop() { 

   //1.
   //LIGHT ONE LED
   //light up ONE led on the board, this can be 0 through 42.
   //Pass in a 'text' colour or a 'hex' colour
   mySEG.lightIndividualLED(0, CRGB::Red);
   delay(1000); //leave it on for 1 second

   //1b.
   //TURN THINGS OFF
   mySEG.resetDisplay();
   delay(350);

   //2.
   //LIGHT A CHARACTER (Ascii character for 2)
   mySEG.lightCharacter(50, CRGB(0x0000ff));
   delay(1000); //add a short delay

   //2b.
   //LIGHT A CHARACTER WITH A DELAY
   //Here we can pass in a delay to the function. If a delay is detected, 
   //then after this delay the function runs 'resetDisplay()' and turns off
   mySEG.lightCharacter(47, CRGB(0xdd0000), 500);

   //3.
   //COLOUR SHIFT
   //colour shift a character between two hues: pass in chr, and the two HUES along with a delay
   mySEG.clrShiftCharacter(68,20,240,15); 

   //4. 
   //FADE A CHARACTER
   //fade a character up from DARK and back down again, pass in fade speed - higher = slower
   mySEG.fadeCharacter(51, CRGB::Blue, 500); 
   delay(300);

   //5.
   //RUNNING A LOOP
   //here we loop through some characters with an inbuilt delay and then a delay showing BLANK
   for (uint8_t i=65; i<91; i++){
      mySEG.lightCharacter(i, CRGB(0x0000dd), 500); //use hex colours
      delay(350);
   }

   //6.
   //PREDEFINED ROUTINES
   mySEG.countUp(300); //predefined routine to count up
   mySEG.countDown(80); //and countdown - sending in the delay

   //7.
   //LIGHT THE POINT
   mySEG.lightPt(CRGB(0xff0000)); //light the point, note this must come after the digit, as the digit clears everything
   delay(500);

 

   


}
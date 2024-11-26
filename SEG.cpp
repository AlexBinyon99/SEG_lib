//this constructor below reads in the LED COUNT, TYPE of BOARD, and the DELAY
//note that the type of board is used in a switch which means that you don't
//have to dynamically set the pin number which is impossible with fastLED.
//instead we define a bunch of options and we just pick 1
//these can be added to as FifeX increases its boards
//v3 : Ken : 19th March 2021 : 23:00

#include "Arduino.h"
#include "SEG.h"
#include <FastLED.h>

//CONSTRUCTOR - setup things
SEG::SEG(uint8_t DATA, uint8_t CLOCK, uint8_t boardCnt, uint8_t ledCnt, uint8_t whichSetup, uint8_t whatDelay){
  //the following can be set at run time
  _dataPin = DATA;
  _clockPin = CLOCK;
  _boardAmount = boardCnt;
  _delayTime = whatDelay;
  _ledsPerBoard = ledCnt;
  _FXnumLeds = _ledsPerBoard * _boardAmount;
  //Serial.println(_FXnumLeds);
  leds = new CRGB(_FXnumLeds);

  //the PIN has to be set at compile time
  switch (whichSetup) {
    //because the pins have to be hardcoded, we just have to do this the long way - it's crap but it does work
    case 1:
      FastLED.addLeds<NEOPIXEL, 4>(leds, _FXnumLeds);
      break;
    case 2:
      FastLED.addLeds<APA102,11,12,RBG>(leds, _FXnumLeds);
      break;
  }

  FastLED.setBrightness(96);
}

//TEST SETUP TURN ALL LEDS ON BLUE
void SEG::lightTest(){
   fill_solid(leds, _FXnumLeds, CRGB::Cyan);  //fill_solid fills the whole strip to one colour
   FastLED.show();
}

//SHOWS INDIVIDUAL LED FOR TESTING
void SEG::lightIndividualLED(uint8_t dig, CRGB myColor){
  resetDisplay(false, 0);
  leds[dig] = myColor;
  FastLED.show();
}

//PRIVATE FUNCTIONS, FOR INTERNAL USE

//THESE NEXT TWO JUST SET THE COLOURS FOR A SET OF SEGMENTS
//THEY ARE CALLED INTERNALLY ONLY AND YOU HAVE TO TURN THE LEDS OFF and ON ELSEWHERE

//TODO - THESE TWO SHOULD BE COMBINED INTO ONE WITH AN OPTION FOR COLOUR
//CRGB 
void SEG::setLedsForCharacterRGB(uint8_t dig, CRGB myColor, uint8_t chosen_board){
    //Serial.println(dig); //34
    uint8_t fiftyDetected = 0; //int to hold detection of the line ending char
    for (int arrIndex = 0; arrIndex < MAXQTYSEGSPERNUM; arrIndex++ ){
      uint8_t seg = characterPattern[dig][arrIndex];  //store which segment
      if (seg == 50){
        fiftyDetected = 1;
        break; //signals end of character
      }
      else {
        for (int l = 0; l < LEDSPERSEGDEF; l++){ //look through all the leds per segment
          if (segmentContents[seg][l] == 50){
            break;
          } else {
            uint8_t chosen_led = segmentContents[seg][l] + _ledsPerBoard * (chosen_board - 1);
            leds[chosen_led] = myColor;
            //Serial.println(segmentContents[seg][l] + _ledsPerBoard * (chosen_board - 1));
          }
        }
      }
    }
    if (fiftyDetected == 0){ //we should have detected a line ending character
    //   Serial.print("warning: no '50' line-ending character detected in characterPattern index: "); 
       Serial.println(dig);
     }
}

//CHSV 
void SEG::setLedsForCharacterHSV(uint8_t dig, CHSV myColor){
    uint8_t fiftyDetected = 0; //int to hold detection of the line ending char
    for (int arrIndex = 0; arrIndex < MAXQTYSEGSPERNUM; arrIndex++ ){
      uint8_t seg = characterPattern[dig][arrIndex];  //store which segment
      if (seg == 50){
        fiftyDetected = 1;
        break; //signals end of character
      }
      else {
        for (int l = 0; l < LEDSPERSEGDEF; l++){ //look through all the leds per segment
          if (segmentContents[seg][l] == 50){
            break;
          } else {
            leds[segmentContents[seg][l]] = myColor;
          }
        }
      }
    }
    if (fiftyDetected == 0){ //we should have detected a line ending character
       Serial.print("warning: no '50' line-ending character detected in characterPattern index: "); 
       Serial.println(dig);
     }
}

//** PUBLIC FUNCTIONS

//TURN ALL LEDS OFF
void SEG::resetDisplay(bool selection, uint8_t board){
  CRGB myColor = CRGB(0x000000);

  uint8_t start;
  uint8_t end;
  //Serial.println(_FXnumLeds);
  
  if(selection == false){
    start = 0;
    end = _FXnumLeds;
  }
  else{
    if(board == 1){
      start = _ledsPerBoard * (board - 1);
      end = _ledsPerBoard;
    }
    else{
      start = (_ledsPerBoard * (board - 1)) + 1;
      end = _ledsPerBoard * board;
    }
  }

  for(int i = start; i <= end; i++){
    //Serial.println(i);
    leds[i] = myColor;
    FastLED.show();
  }
}

//CALLED EXTERNALLY TO LIGHT UP ONE CHARACTER - OPTIONAL DELAY
void SEG::lightCharacter(uint8_t chosenBoard, uint8_t dig, CRGB myColor, int showDelayOption) {
  setLedsForCharacterRGB(whichAddressForThisAscii[dig], myColor, chosenBoard);
  FastLED.show();
  //Serial.println(dig);
  if (showDelayOption > 0){ //if user specifies this then leave on for a duration and turn off
    delay (showDelayOption);
    //resetDisplay(); //turn off display
  }
}

void SEG::lightString(uint8_t *chosenString, CRGB myColor, uint8_t start_point){
  uint8_t array_len = 0;
  bool readArray = true;
  
    for(int i = 0; i <= 20; i++){
      if(chosenString[i] == 255){
        readArray = false;
      }
      if(readArray == true){
        array_len = array_len + 1; 
      }
    }
    Serial.println(array_len);
    uint8_t j = start_point;
    for(int i = 0; i <= array_len -1 ; i++){
      Serial.println(chosenString[i]);
      lightCharacter(j, chosenString[i], myColor);
      j = j + 1;
    }
}

//CALLED EXTERNALLY TO FADE IN AND OUT OF A CHACTER
void SEG::fadeCharacter(uint8_t chosenBoard, uint8_t dig, CRGB myColor, int fadeWait){
  resetDisplay(false, 0);
  setLedsForCharacterRGB(whichAddressForThisAscii[dig], myColor, chosenBoard);

  //fade in
  for (int br = 0; br < 97; br++){
     FastLED.setBrightness(br);
     FastLED.show();
     delay(10);
  }

  //wait
  delay(fadeWait);
  
  //fade out
  for (int br = 97; br > -1; br--){
     FastLED.setBrightness(br);
     FastLED.show();
     delay(10);
  }

  resetDisplay(false, 0);
  FastLED.setBrightness(97); //reset at end of this so we can see things
}

//CALLED EXTERNALLY TO FADE IN AND OUT OF A CHACTER
void SEG::clrShiftCharacter(uint8_t dig, uint8_t Hue1, uint8_t Hue2, int fadeWait){
  resetDisplay(false, 0);
  //TODO we could add a control for saturation here...
  //work out which direction the fade is going in
  if (Hue2 > Hue1){
    for (int i = Hue1; i < Hue2; i++){
      setLedsForCharacterHSV(whichAddressForThisAscii[dig], CHSV(i,255,255));
      FastLED.show();
      delay(fadeWait);
    }
  } else if (Hue1 > Hue2) {
    for (int i = Hue1; i > Hue2; i--){
      setLedsForCharacterHSV(whichAddressForThisAscii[dig], CHSV(i,255,255));
      FastLED.show();
      delay(fadeWait);
    }
  }
}

//just light up the point
void SEG::lightPt(CRGB myColor)
{
  leds[THEPOINT] = myColor;
  FastLED.show();
}

//counts up with random colour, colour is either R,G or B
void SEG::countUp(int inBetweenTime){
  for (int x = 48; x < 58; x++){ //ascii code
    int channel = random (0,3);
    switch (channel){
      case 0:
        lightCharacter(1, x, CRGB(0xcc0000));
        break;
      case 1:
        lightCharacter(1, x, CRGB(0x00cc00));
        break;
      case 2:
        lightCharacter(1, x, CRGB(0x0000cc));
        break;
    }
    delay(inBetweenTime);
  }
}

//counts up with random colour, colour is either R,G or B
void SEG::countDown(int inBetweenTime){
 for (int x = 57; x > 47; x--){
    lightCharacter(1, x, CRGB(0x550000));
    delay(inBetweenTime);
  }
}

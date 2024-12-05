#ifndef SEG_h
#define SEG_h
#include "Arduino.h"
#include <FastLED.h>

const uint8_t MAXQTYSEGSPERNUM = 11; //add 1 to the max here for the terminator
const uint8_t THEPOINT = 42;
const uint8_t LEDSPERSEGDEF = 4; //add 1 here for the terminator in the array

class SEG {
  public:
    // CRGB leds[40];
    SEG(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

    // void setupRoutine(int DATA_PIN, int CLK_PIN, int NUM_LEDS, int DELAY_TIME);
    void resetDisplay(bool, uint8_t);
    void countUp(int);
    void countDown(int);
    void lightTest();
    void lightCharacter(uint8_t, uint8_t, CRGB, int showDelayOption=0); //specify optional argument
    void fadeCharacter(uint8_t, uint8_t, CRGB, int);
    void clrShiftCharacter(uint8_t, uint8_t, uint8_t, int);
    void lightPt(CRGB);
    void lightIndividualLED(uint8_t, CRGB);
    void lightString(uint8_t[50], CRGB, uint8_t);

  private:
   
    void setLedsForCharacterRGB(uint8_t, CRGB, uint8_t);
    void setLedsForCharacterHSV(uint8_t, CHSV);
    uint8_t _delayTime = 5;
    long int _FXnumLeds = 4;
    uint8_t _ledsPerBoard;
    uint8_t _boardAmount = 1;
    uint8_t _dataPin;
    uint8_t _clockPin;
    CRGB *leds = NULL; //we make a pointer to this but set it null, then allocate it in the constructor

    //hold the LED nos per segment - patterns are stored per segment from now on
    const uint8_t segmentContents[16][4] = {
      {0,1,2,50}, //0
      {3,4,5,50}, //1
      {6,7,50}, //2
      {8,9,50}, //3
      {10,11,12,50}, //4
      {13,14,15,50}, //5
      {16,17,50}, //6
      {18,19,50}, //7
      {20,21,22,50}, //8
      {23,24,25,50}, //9
      {26,27,28,50}, //10
      {29,30,31,50}, //11
      {32,33,34,50}, //12
      {35,36,37,50}, //13 
      {38,39,50}, //14
      {40,41,50} //15
    };

    const uint8_t characterPattern[50][MAXQTYSEGSPERNUM] = {
      //the things held in here are segment references used against segmentContents
      //rather than typing out indivdiual LEDs - this is also a RAM saver
      {0,1,2,3,4,5,6,7,50},       //0 ASCII 48
      {4,5,50},                   //1 ASCII 49
      {2,3,4,15,14,0,7,6,50},     //2 ASCII 50
      {2,3,4,15,5,6,7,14,50},     //3 ASCII 51
      {1,14,15,4,5,50},           //4 ASCII 52
      {3,2,1,14,15,5,6,7,50},     //5 ASCII 53
      {3,2,1,0,7,6,5,15,14,50},   //6 ASCII 54
      {2,3,9,8,50},               //7 ASCII 55
      {2,3,4,15,14,0,7,6,5,1,50}, //8 ASCII 56
      {3,2,1,14,15,4,5,6,7,50},   //9 ASCII 57
      {0,1,2,3,4,5,14,15,50},     //A ASCII 65
      {2,3,4,15,10,7,6,5,11,50},  //B ASCII 66
      {0,1,2,3,6,7,50},           //C ASCII 67
      {10,11,2,3,4,5,6,7,50},     //D ASCII 68
      {0,1,2,3,6,7,14, 15,50},    //E ASCII 69
      {0,1,2,14,3,15,50},         //F ASCII 70
      {0,1,2,3,7,6,5,15,50},      //G ASCII 71
      {0,1,14,15,4,5,50},         //H ASCII 72
      {10,11,2,3,7,6,50},         //I ASCII 73
      {4,5,6,7,0,50},             //J ASCII 74
      {10,11,9,12,50},            //K ASCII 75
      {0,1,7,6,50},               //L ASCII 76
      {0,1,13,9,4,5,50},          //M ASCII 77
      {0,1,13,12,5,4,50},         //N ASCII 78
      {0,1,2,3,4,5,6,7,50},       //O ASCII 79
      {0,1,2,3,4,15,14,50},       //P ASCII 80
      {0,1,2,3,4,5,6,7,12,50},    //Q ASCII 81
      {0,1,2,3,4,15,14,12,50},    //R ASCII 82
      {3,2,1,14,15,5,6,7,50},     //S ASCII 83
      {10,11,2,3,50},             //T ASCII 84
      {0,1,4,5,6,7,50},           //U ASCII 85
      {0,1,8,9,50},               //V ASCII 86
      {0,1,8,12,5,4,50},          //W ASCII 87
      {8,9,13,12,50},             //X ASCII 88
      {13,9,11,50},               //Y ASCII 89
      {2,3,9,8,7,6,50},           //Z ASCII 90
      {8,9,50}                    // '/' ASCII 47

    };

const uint8_t whichAddressForThisAscii[100] = {
      255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  // 9
      255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  // 19
      255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  // 29
      255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  // 39
      255, 255, 255, 255, 255, 255, 255,  36,  0,  1,    // 49
        2,   3,   4,   5,   6,   7,   8,   9, 255, 255, // 59
      255, 255, 255, 255, 255,  10,  11,  12,  13,  14, // 69
       15,  16,  17,  18,  19,  20,  21,  22,  23,  24, // 79
       25,  26,  27,  28,  29,  30,  31,  32,  33,  34, // 89
       35, // Z end of alphabet
    };


};

#endif

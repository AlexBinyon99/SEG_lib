#include <SEG.h>
#include <FastLED.h>
#include "SoftwareSerial.h"
#include <Wire.h> // ------------------------------------------- As soon as this like is commented out, the code works as expected  

const uint8_t DATA_PIN = 11;
const uint8_t CLOCK_PIN = 12;
const uint8_t NUM_BOARDS = 4;
const uint8_t NUM_LEDS = 43; // per board
const uint8_t LED_TYPE = 2; // 1-Neopixel 2-APA102
const uint8_t DELAY_TIME = 10;// delay

SEG mySEG(DATA_PIN, CLOCK_PIN, NUM_BOARDS, NUM_LEDS, LED_TYPE, DELAY_TIME);

int VisualreactionTime = 0; // Initialize counter



// Define Software Serial pins for the Arduino Nano
#define RXD 8 // RX pin
#define TXD 9 // TX pin

// Create Software Serial object
SoftwareSerial mySerial(RXD, TXD);

void setup() {
  Serial.begin(115200);
    mySerial.begin(9600);
  mySEG.resetDisplay(false, 0); // Initialize the display
  displayNumber(1111);
  delay (2000);
  mySEG.resetDisplay(false, 0); // Initialize the display
  displayNumber(9999);
  delay (2000);
  mySEG.resetDisplay(false, 0); // Initialize the display
  displayNumber(VisualreactionTime);
}

void loop() {
  clearDisplay(); // Clear the display before updating
  displayNumber(VisualreactionTime); // Display the current counter value
  VisualreactionTime = (VisualreactionTime + 1); // Increment counter
  Serial.println("counter: " + String(VisualreactionTime)); // Debugging
  delay(900); // Short delay to debounce button
}

void displayNumber(int number) {
  // Convert number to string
  char numStr[5];
  snprintf(numStr, 5, "%04d", number);

  // Loop through each character in the string
  for (int i = 0; i < 4; i++) {
    char digit = numStr[i];

    // Check if character is a valid digit (0-9)
    if (digit >= '0' && digit <= '9') {
      int digitValue = digit - '0'; // Convert to integer (0–9)
      int asciiValue = digitValue + 48; // Map to ASCII index (48–57 for '0'–'9')

      // Debugging output
      Serial.print("Character: ");
      Serial.print(digit);
      Serial.print(" | Digit Value: ");
      Serial.print(digitValue);
      Serial.print(" | ASCII Value: ");
      Serial.println(asciiValue);

      // Call lightCharacter with the correct index
      mySEG.lightCharacter(i + 1, asciiValue, CRGB(0xFFFFFF));
    } else {
      Serial.print("Invalid character: ");
      Serial.println(digit); // Print invalid character for debugging
    }
  }
}
void clearDisplay() {
  mySEG.resetDisplay(false, 0); // Initialize the display
}

#include <Arduino.h>
#include "leds.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

//Pin connected to ST_CP of 74HC595
uint8_t latchPin = 8;
//Pin connected to SH_CP of 74HC595
uint8_t clockPin = 12;
////Pin connected to DS of 74HC595
uint8_t greenDataPin = 13;
uint8_t redLED = 7;

const PROGMEM byte dataArray[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
const PROGMEM byte allLEDS[] = { 0xFF };

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {

  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    } else {
      pinState= 0;
    }
    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }
  digitalWrite(myClockPin, 0);
}


void blinkGreenTwice() {
  digitalWrite(latchPin, 0);
  shiftOut(greenDataPin, clockPin, 0);
  shiftOut(greenDataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < 2; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(greenDataPin, clockPin, 255);
    shiftOut(greenDataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(500);
    digitalWrite(latchPin, 0);
    shiftOut(greenDataPin, clockPin, 0);
    shiftOut(greenDataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(500);
  }
}


void setupLEDS() {
	pinMode(redLED, OUTPUT);
	pinMode(latchPin, OUTPUT);
	blinkGreenTwice();
}

void redRunning () {
	digitalWrite(redLED, HIGH);
	vTaskDelay(500);
	digitalWrite(redLED, LOW);
	vTaskDelay(500);
}
void greenRunning () {
	 byte data;
	  for (int j = 0; j < 8; j++) {
	    data = pgm_read_byte_near(dataArray + j);
	    digitalWrite(latchPin, 0);
	    shiftOut(greenDataPin, clockPin, data);
	    digitalWrite(latchPin, 1);
	    vTaskDelay(300);
	  }
}

void redStationary() {
	digitalWrite(redLED, HIGH);
	vTaskDelay(250);
	digitalWrite(redLED, LOW);
	vTaskDelay(250);
}

/**ground latchPin and hold low for as long as you are transmitting**/
void greenStationary () {
    digitalWrite(latchPin, 0);
    shiftOut(greenDataPin, clockPin, 0xFF);
    digitalWrite(latchPin, 1);
}

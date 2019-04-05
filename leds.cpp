#include <Arduino.h>
#include "leds.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>



//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int greenDataPin = 13;
int redLED = 7;

byte data, allLEDS;
byte dataArray[10];

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


void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(greenDataPin, clockPin, 0);
  shiftOut(greenDataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(greenDataPin, clockPin, 255);
    shiftOut(greenDataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(greenDataPin, clockPin, 0);
    shiftOut(greenDataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}


void setupLEDS() {
	pinMode(redLED, OUTPUT);
	pinMode(latchPin, OUTPUT);

	dataArray[0] = 0x01; //0b00000001
	dataArray[1] = 0x02; //0b00000010
	dataArray[2] = 0x04; //0b00000100
	dataArray[3] = 0x08; //0b00001000
	dataArray[4] = 0x10; //0b00010000
	dataArray[5] = 0x20; //0b00100000
	dataArray[6] = 0x40; //0b01000000
	dataArray[7] = 0x80; //0b10000000

	allLEDS = 0xFF;

	blinkAll_2Bytes(2,500);

}

void runningMode() {
	greenRunning();
	redRunning();
}


void stationaryMode() {
	greenStationary();
	redStationary();
}

void redRunning () {
	digitalWrite(redLED,HIGH);
	vTaskDelay(500);
	digitalWrite(redLED, LOW);
	vTaskDelay(500);
}
void greenRunning () {
	  for (int j = 0; j < 8; j++) {
	    data = dataArray[j];
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
    shiftOut(greenDataPin, clockPin, allLEDS);
    digitalWrite(latchPin, 1);

}

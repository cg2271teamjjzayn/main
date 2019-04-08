#include <Arduino.h>
#include "music.h"
#include "themes.h"
#include "pitches.h"

void myTone(byte pin, uint16_t frequency, uint16_t duration)
{ // input parameters: Arduino pin number, frequency in Hz, duration in milliseconds
 unsigned long startTime=millis();
 unsigned long halfPeriod= 1000000L/frequency/2;
 pinMode(pin,OUTPUT);
 while (millis()-startTime< duration) {
   digitalWrite(pin,HIGH);
   delayMicroseconds(halfPeriod);
   digitalWrite(pin,LOW);
   delayMicroseconds(halfPeriod);
 }
 pinMode(pin,INPUT);
}


void Play_BabyShark() {
  for (int thisNote = 0; thisNote < (sizeof(Babyshark_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Babyshark_duration[thisNote];//convert duration to time delay
    myTone(2, Babyshark_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 0.50; //Here 1.05 is tempo, increase to play it slower
    delay(pauseBetweenNotes);
    digitalWrite(2, LOW); //stop music on pin 8
    }

}

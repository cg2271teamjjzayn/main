#include <Arduino.h>
#include "music.h"
#include "themes.h"
#include "pitches.h"
#include <FreeRTOS.h>
#include <task.h>
#include <avr/io.h>


void myTone(byte pin, uint16_t frequency, uint16_t duration) {
	// input parameters: Arduino pin number, frequency in Hz, duration in milliseconds
	unsigned long startTime = millis();
	unsigned long halfPeriod = 1000000L / frequency / 2;
	pinMode(pin, OUTPUT);
	while (millis() - startTime < duration) {
		digitalWrite(pin, HIGH);
		delayMicroseconds(halfPeriod);
		digitalWrite(pin, LOW);
		delayMicroseconds(halfPeriod);
	}
	pinMode(pin, INPUT);
}

void Play_Pirates() {
	TickType_t xLastWakeTime = xTaskGetTickCount();

	for (int thisNote = 0; thisNote < (sizeof(Pirates_note2)/sizeof(int)); thisNote++) {

		int noteDuration = 1000 / Pirates_duration2[thisNote];
		myTone(2, Pirates_note2[thisNote], noteDuration);

		int pauseBetweenNotes = noteDuration * 1.5;
		vTaskDelayUntil(&xLastWakeTime, pauseBetweenNotes);

		digitalWrite(2, LOW);
    }

}


void Play_BabyShark() {
	TickType_t xLastWakeTime = xTaskGetTickCount();

	for (int thisNote = 0; thisNote < (sizeof(Babyshark_notes) / sizeof(int)); thisNote++) {

		int noteDuration = 1000 / Babyshark_durations[thisNote];
		myTone(2, Babyshark_notes[thisNote], noteDuration);

		int pauseBetweenNotes = noteDuration * 1.5;
		vTaskDelayUntil(&xLastWakeTime, pauseBetweenNotes);
		digitalWrite(2, LOW);
	}

}

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

	uint16_t currentNote;
	uint16_t currentDuration;
	for (int i = 0; i< 89 ; i++) {
		currentNote = pgm_read_word_near(Pirates_note + i);
		currentDuration = pgm_read_word_near(Pirates_duration + i);
		int noteDuration = 1000 / currentDuration;
		myTone(2, currentNote, noteDuration);

		int pauseBetweenNotes = noteDuration * 0.1;
		vTaskDelayUntil(&xLastWakeTime, pauseBetweenNotes);

		digitalWrite(2, LOW);
    }

}


void Play_BabyShark() {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	uint16_t currentNote;
	uint16_t currentDuration;
	for (int i = 0; i < 50; i++) {

		currentNote = pgm_read_word_near(Babyshark_notes + i);
		currentDuration = pgm_read_word_near(Babyshark_durations + i);
		int noteDuration = 1000 / currentDuration;
		myTone(2, currentNote, noteDuration);
		Serial.println(20);
		int pauseBetweenNotes = noteDuration * 0.5;
		vTaskDelayUntil(&xLastWakeTime, pauseBetweenNotes);
		delay(pauseBetweenNotes);
		digitalWrite(2, LOW);
	}

}

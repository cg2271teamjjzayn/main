/*
 * music.cpp
 *
 *  Created on: 20 Mar 2019
 *      Author: zhuan
 */
#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "pitches.h"

int melody[] = {
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_FS4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_FS4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16
};

void setupMusic() {
	pinMode(2, OUTPUT);
}

//#define BUZZER_PIN 2
//
//// #define TEMPO 400
//#define TEMPO 3200
//#define DNOTE 2349
//#define ENOTE 2637
//#define GNOTE 3136
//#define FSNOTE 2960
//
//const TickType_t xTempo = (TEMPO/portTICK_PERIOD_MS);
//const TickType_t xHalf  = xTempo/2;
//const TickType_t xQuarter = xHalf/2;
//const TickType_t xThird = xTempo/3;
//const TickType_t xEigth = xQuarter/2;
//
//TickType_t xLastWakeTime;

//void babysharkdoo() {
//	xLastWakeTime = xTaskGetTickCount();
//	//D-E G GG  GG  GG
//	tone(BUZZER_PIN, DNOTE); //D
//	vTaskDelayUntil(&xLastWakeTime, xHalf);
//	tone(BUZZER_PIN, ENOTE); //E
//	vTaskDelayUntil(&xLastWakeTime, xHalf);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xQuarter);
//
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xHalf);
//
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xHalf);
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xThird);
//
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xQuarter);
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xQuarter);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xQuarter);
//
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xThird);
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xThird);
//
//}
//
//void babyshark() {
//	xLastWakeTime = xTaskGetTickCount();
//
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xHalf);
//	tone(BUZZER_PIN, GNOTE); //G
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xHalf);
//
//	tone(BUZZER_PIN, FSNOTE); //F#
//	vTaskDelayUntil(&xLastWakeTime, xEigth);
//	noTone(BUZZER_PIN);
//	vTaskDelayUntil(&xLastWakeTime, xTempo);
//	vTaskDelayUntil(&xLastWakeTime, xTempo);
//}

void playBBShark() {

	while(1) {

		for (int thisNote = 0; thisNote < 60; thisNote++) {
			// to calculate the note duration, take one second divided by the note type.
			//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
			int noteDuration = 1000 / noteDurations[thisNote];
			tone(2, melody[thisNote], noteDuration);

			// to distinguish the notes, set a minimum time between them.
			// the note's duration + 30% seems to work well:
			int pauseBetweenNotes = noteDuration * 1.30;
			delay(pauseBetweenNotes);
			// stop the tone playing:
			noTone(8);
		}
	}
}

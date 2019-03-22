#include <Arduino.h>
#include "pitches.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>



int melody[] = {
		NOTE_D6, NOTE_E6,  NOTE_G6,   NOTE_G6,   NOTE_G6,   NOTE_G6,   NOTE_G6,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_FS4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
		NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_FS4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:

void setupMusic() {
	pinMode(2, OUTPUT);
}

void playTune() {

	while(1) {
		for (int thisNote = 0; thisNote < 60; thisNote++) {
			int noteDurations[] = {
			  200, 200, 200, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16
			};

			// to calculate the note duration, take one second divided by the note type.
			//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
			int noteDuration = 1000 / noteDurations[thisNote];
			//tone(2, melody[thisNote]);

			//digitalWrite(2,HIGH);
			vTaskDelay(noteDurations[0]);

			// to distinguish the notes, set a minimum time between them.
			// the note's duration + 30% seems to work well:
//			int pauseBetweenNotes = noteDuration * 1.30;
//			vTaskDelay(pauseBetweenNotes);
			// stop the tone playing:
			//noTone(8);
		}
	}
}

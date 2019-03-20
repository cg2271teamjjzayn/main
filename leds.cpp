#include <Arduino.h>
#include "leds.h"
#define GREENLED 7
#define REDLED 8

void setupLEDS() {
	pinMode(GREENLED, OUTPUT);
	pinMode(REDLED, OUTPUT);
}

void runningMode() {

	/**
	 * The front 8 green led's must be in
	 * RUNNING MODE(??) -- 1 LED at a time??
	 * whenever the robot is moving
	 */

	//Write code here for green leds

	/**
	 * The 8 Red LED's must be flashing
	 * continuously at a rate of 500ms ON,
	 * 500ms off, while the robot is moving
	 */
	digitalWrite(REDLED,HIGH);
	delay(500);
	digitalWrite(REDLED, LOW);
	delay(500);
}

void stationaryMode() {
	/** The front 8 green leds must be
	 * all lighted up whenever the robot is stationary
	 */

	digitalWrite(GREENLED, HIGH);

	/**
	 * The rear 8 Red leds must be flashing
	 * continously at a rate of 250ms ON, 250ms OFF,
	 * while the robot is stationary.
	 */

	digitalWrite(REDLED, HIGH);
	delay(250);
	digitalWrite(REDLED, LOW);
	delay(250);

}

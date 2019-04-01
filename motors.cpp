#include <Arduino.h>
#include "motors.h"
boolean forwardFlag = true;
boolean backwardFlag = false;

#define RF 10
#define RB 11

#define LF 6
#define LB 9

void setupMotors() {

	pinMode(RF, OUTPUT);
	pinMode(RB, OUTPUT);

	pinMode(LF, OUTPUT);
	pinMode(LB, OUTPUT);
}


void brake() {
}

void left() {

}

void right() {

}


void forward() {
	analogWrite(RF, 250);
	analogWrite(LF, 250);
	analogWrite(RB, 0);
	analogWrite(LB, 0);

}

void backward() {

}

int remap(int value) {
  return value/1023.0 * 255;
}

int convertX(int value) {
  return remap(value);
}

int convertY(int value) {
  return remap(value);
}

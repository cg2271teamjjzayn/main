#include <Arduino.h>
#include "motors.h"
boolean forwardFlag = true;
boolean backwardFlag = false;

#define FW1 12
#define BW1 13

#define FW2 10 // PWM PIN
#define BW2 11 // PWM PIN

#define FW3 6 // PWM PIN
#define BW3 9 // PWM PIN

#define FW4 3 // PWM PIN
#define BW4 5 // PWM PIN



void setupMotors() {

	pinMode(FW1, OUTPUT);
	pinMode(FW2, OUTPUT);

	pinMode(FW2, OUTPUT);
	pinMode(BW2, OUTPUT);

	pinMode(FW3, OUTPUT);
	pinMode(BW3, OUTPUT);

	pinMode(FW4, OUTPUT);
	pinMode(BW4, OUTPUT);

}


void brake() {
  analogWrite(FW1, 0);
  analogWrite(FW2, 0);
  analogWrite(FW3, 0);
  analogWrite(FW4, 0);

  analogWrite(BW1, 0);
  analogWrite(BW2, 0);
  analogWrite(BW3, 0);
  analogWrite(BW4, 0);
}

void left() {
  analogWrite(FW1, 200);
  analogWrite(FW4, 200);
  analogWrite(BW2, 200);
  analogWrite(BW3, 200);

  analogWrite(BW1, 0);
  analogWrite(BW4, 0);
  analogWrite(FW2, 0);
  analogWrite(FW3, 0);
}

void right() {

  analogWrite(BW1, 200);
  analogWrite(BW4, 200);
  analogWrite(FW2, 200);
  analogWrite(FW3, 200);

  analogWrite(FW1, 0);
  analogWrite(FW4, 0);
  analogWrite(BW2, 0);
  analogWrite(BW3, 0);
}


void forward() {

  analogWrite(FW1, 200);
  analogWrite(FW2, 200);
  analogWrite(FW3, 200);
  analogWrite(FW4, 200);

  analogWrite(BW1, 0);
  analogWrite(BW2, 0);
  analogWrite(BW3, 0);
  analogWrite(BW4, 0);

}

void backward() {

  analogWrite(FW1, 0);
  analogWrite(FW2, 0);
  analogWrite(FW3, 0);
  analogWrite(FW4, 0);

  analogWrite(BW1, 200);
  analogWrite(BW2, 200);
  analogWrite(BW3, 200);
  analogWrite(BW4, 200);
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

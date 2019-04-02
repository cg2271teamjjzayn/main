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

void forwardRight(int pwm_L, int pwm_R) {
	analogWrite(RIGHT_F, pwm_L - pwm_R  + 10);
	analogWrite(LEFT_F, pwm_L );

	analogWrite(RIGHT_B, 0);
	analogWrite(LEFT_B, 0);
}

void forwardLeft(int pwm_R, int pwm_L) {
	analogWrite(RIGHT_F, pwm_R );
	analogWrite(LEFT_F, pwm_R - pwm_L + 10);

	analogWrite(RIGHT_B, 0);
	analogWrite(LEFT_B, 0);
}

void backwardRight(int pwm_L, int pwm_R) {
	analogWrite(RIGHT_B, pwm_L - pwm_R + 10);
	analogWrite(LEFT_B, pwm_L );

	analogWrite(RIGHT_F, 0);
	analogWrite(LEFT_F, 0);
}

void backwardLeft(int pwm_R, int pwm_L) {
	analogWrite(RIGHT_B, pwm_R );
	analogWrite(LEFT_B, pwm_R - pwm_L + 10);

	analogWrite(RIGHT_F, 0);
	analogWrite(LEFT_F, 0);
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

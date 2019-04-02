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

#define RIGHT_F 10
#define RIGHT_B 11

#define LEFT_F 6
#define LEFT_B 9



void setupMotors() {

//	pinMode(FW1, OUTPUT);
//	pinMode(FW2, OUTPUT);
//
//	pinMode(FW2, OUTPUT);
//	pinMode(BW2, OUTPUT);
//
//	pinMode(FW3, OUTPUT);
//	pinMode(BW3, OUTPUT);
//
//	pinMode(FW4, OUTPUT);
//	pinMode(BW4, OUTPUT);

	pinMode(RIGHT_F, OUTPUT);
	pinMode(RIGHT_B, OUTPUT);

	pinMode(LEFT_F, OUTPUT);
	pinMode(LEFT_B, OUTPUT);

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

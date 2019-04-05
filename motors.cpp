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
	analogWrite(RF, pwm_L - pwm_R  + 10);
	analogWrite(LF, pwm_L );

	analogWrite(RB, 0);
	analogWrite(LB, 0);
}

void forwardLeft(int pwm_R, int pwm_L) {
	analogWrite(RF, pwm_R );
	analogWrite(LF, pwm_R - pwm_L + 10);

	analogWrite(RB, 0);
	analogWrite(LB, 0);
}

void backwardRight(int pwm_L, int pwm_R) {
	analogWrite(RB, pwm_L - pwm_R + 10);
	analogWrite(LB, pwm_L );

	analogWrite(RF, 0);
	analogWrite(LF, 0);
}

void backwardLeft(int pwm_R, int pwm_L) {
	analogWrite(RB, pwm_R );
	analogWrite(LB, pwm_R - pwm_L + 10);

	analogWrite(RF, 0);
	analogWrite(LF, 0);
}


void brake() {
}

void forward () {
	analogWrite(RF, 250);
	analogWrite(LF, 250);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
}

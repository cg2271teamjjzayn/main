#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include "motors.h"

boolean forwardFlag = true;
boolean backwardFlag = false;

#define RF 9
#define RB 10

#define LF 5
#define LB 6

TickType_t ticks;
const TickType_t xFrequency = 40;
TickType_t xLastWakeTime;

TickType_t highFrequency = 0;
TickType_t lowFrequency = 0;

void setupMotors() {
	pinMode(RF, OUTPUT);
	pinMode(RB, OUTPUT);

	pinMode(LF, OUTPUT);
	pinMode(LB, OUTPUT);

}

void forwardRight(int pwm_L, int pwm_R) {

//    //xLastWakeTime = xTaskGetTickCount();
//
//	highFrequency = pwm_L / 255 * 40 ;
//	lowFrequency = pwm_R / 255 * 40;
//
//
//	digitalWrite(RF, HIGH);
//	vTaskDelay(highFrequency - lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime, highFrequency - lowFrequency);
//	digitalWrite(LF, HIGH);
//	vTaskDelay(highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency);
//	digitalWrite(RF, LOW);
//	vTaskDelay(xFrequency - highFrequency + lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency);
//	digitalWrite(LF, LOW);
//	vTaskDelay(xFrequency - highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency - lowFrequency);
//
//	digitalWrite(RB, LOW);
//	digitalWrite(LB, LOW);

	analogWrite(RF, pwm_L - pwm_R);
	analogWrite(LF, pwm_L );

	analogWrite(RB, 0);
	analogWrite(LB, 0);
}

void forwardLeft(int pwm_R, int pwm_L) {
//    //xLastWakeTime = xTaskGetTickCount();
//
//	highFrequency = pwm_R / 255 * 40;
//	lowFrequency = pwm_L / 255 * 40;
//
//
//	digitalWrite(RF, HIGH);
//	vTaskDelay(highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency);
//	digitalWrite(LF, HIGH);
//	vTaskDelay(highFrequency - lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency - lowFrequency);
//	digitalWrite(RF, LOW);
//	vTaskDelay(xFrequency - highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency - lowFrequency);
//	digitalWrite(LF, LOW);
//	vTaskDelay(xFrequency - highFrequency + lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency);
//
//	digitalWrite(RB, LOW);
//	digitalWrite(LB, LOW);

	analogWrite(RF, pwm_R );
	analogWrite(LF, pwm_R - pwm_L);

	analogWrite(RB, 0);
	analogWrite(LB, 0);
}

void backwardRight(int pwm_L, int pwm_R) {
//    //xLastWakeTime = xTaskGetTickCount();
//
//	highFrequency = pwm_L / 255 * 40;
//	lowFrequency = pwm_R / 255 * 40;
//
//
//	digitalWrite(RB, HIGH);
//	vTaskDelay(highFrequency - lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency - lowFrequency);
//	digitalWrite(RB, LOW);
//	vTaskDelay(xFrequency - highFrequency + lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency);
//	digitalWrite(LB, HIGH);
//	vTaskDelay(highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency);
//	digitalWrite(LB, LOW);
//	vTaskDelay(xFrequency - highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency - lowFrequency);
//
//	digitalWrite(RF, LOW);
//	digitalWrite(LF, LOW);

	analogWrite(RB, pwm_L - pwm_R);
	analogWrite(LB, pwm_L );

	analogWrite(RF, 0);
	analogWrite(LF, 0);
}

void backwardLeft(int pwm_R, int pwm_L) {
//    //xLastWakeTime = xTaskGetTickCount();
//
//	highFrequency = pwm_R / 255 * 40;
//	lowFrequency = pwm_L / 255 * 40;
//
//	digitalWrite(RB, HIGH);
//	vTaskDelay(highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency);
//	digitalWrite(RB, LOW);
//	vTaskDelay(xFrequency - highFrequency);
//	//vTaskDelayUntil(&xLastWakeTime, highFrequency - lowFrequency);
//	digitalWrite(LB, HIGH);
//	vTaskDelay(highFrequency - lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime,highFrequency - lowFrequency);
//	digitalWrite(LB, LOW);
//	vTaskDelay(xFrequency - highFrequency + lowFrequency);
//	//vTaskDelayUntil(&xLastWakeTime, highFrequency);
//
//	digitalWrite(RF, LOW);
//	digitalWrite(LF, LOW);

	analogWrite(RB, pwm_R);
	analogWrite(LB, pwm_R - pwm_L);

	analogWrite(RF, 0);
	analogWrite(LF, 0);
}


void brake() {
	digitalWrite(RF, LOW);
	digitalWrite(RB, LOW);
	digitalWrite(LF, LOW);
	digitalWrite(LB, LOW);
}

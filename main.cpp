#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "motors.h"
#include "bluetooth.h"
#include "music.h"
#include "leds.h"

#define STACK_SIZE 200
#define maxMotorDelayCommand portMAX_DELAY
bool isMoving;

QueueHandle_t xMotorCommandQueue, xBluetoothCommandQueue;
void xTaskLed (void *p) {
	for (;;) {
		if (isMoving) {
			runningMode();
		} else {
			stationaryMode();
		}
	}
}


void xTaskPlayBabyShark(void *p ) {
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {
		//playTune();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);

	}
}


void xTaskBluetooth(void *p) {
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;
	xLastWakeTime = xTaskGetTickCount();

	char command;
	for (;;) {
		command = receiveData();
		if (command != 'e') {
			Serial.println(command);
			switch (command) {
				case 'f':
				case 'b':
				case 'l':
				case 'r':
				case 's':
					xQueueSendToBack(xMotorCommandQueue, &command, 10);
					break;
				default :
					xQueueSendToBack(xBluetoothCommandQueue, &command, 10);
			}
		}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void xTaskMotor(void *p) {
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100;
	xLastWakeTime = xTaskGetTickCount();

	char command;
	for (;;) {
		if (xQueueReceive(xMotorCommandQueue, &command, 10)) {
		    switch(command) {
		      case 'f' :
		    	  forward();
		    	  break;
		      case 'b' :
		    	  backward();
		    	  break;
		      case 'l' :
		    	  left();
		    	  break;
		      case 'r' :
		    	  right();
		    	  break;
		      case 's' :
		    	  brake();
		    	  break;
		      case 'e' :
		    	  break;
		    }
		}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void setup() {
	isMoving = true;
	setupMotors();
	setupLEDS();
	setupBluetooth();
	xMotorCommandQueue = xQueueCreate(10, sizeof(char));
	xBluetoothCommandQueue = xQueueCreate(10, sizeof(char));
	xTaskCreate(xTaskBluetooth, "TaskBluetooth", STACK_SIZE, NULL, 4, NULL);
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 4, NULL);
	xTaskCreate(xTaskPlayBabyShark, "TaskBabyShark", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(xTaskLed, "TaskLed", STACK_SIZE, NULL, 1, NULL);

}

void loop() {
	vTaskStartScheduler();

}

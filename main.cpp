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
	MotorData command;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {
		command = getData();
		xQueueSendToBack(xMotorCommandQueue, &command, 100);
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void xTaskMotor(void *p) {
	MotorData command;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100;
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {
		if (xQueueReceive(xMotorCommandQueue, &command, 100)) {
			if (command.mData[1] >= 0) {
				if (command.mData[0] >= 0) {
					forwardRight(command.mData[1], command.mData[0]);
				} else if (command.mData[0] < 0) {
					forwardLeft(command.mData[1], -command.mData[0]);
				}
			} else if (command.mData[1] < 0) {
				if (command.mData[0] >= 0) {
					backwardRight(-command.mData[1], command.mData[0]);
				}else if (command.mData[0] < 0) {
					backwardLeft(-command.mData[1], -command.mData[0]);
				}
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

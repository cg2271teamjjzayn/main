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

MotorData dataMotor;

QueueHandle_t xMotorCommandQueue = xQueueCreate(1, sizeof(struct MotorData *));

void xTaskLed (void *p) {
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {
		if (isMoving) {
			runningMode();
		} else {
			stationaryMode();
		}
	vTaskDelayUntil(&xLastWakeTime, xFrequency);

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
	TickType_t xLastWakeTime= xTaskGetTickCount();
	//const TickType_t xFrequency = 10;

	MotorData *command;

	for (;;) {
		dataMotor = getData();
		command = &dataMotor;
		if (xMotorCommandQueue != 0) {
			xQueueSend(xMotorCommandQueue, (void * ) &command,
					(TickType_t ) 10);
		}
		vTaskDelayUntil(&xLastWakeTime, 5);
	}
}

void xTaskMotor (void *p) {
	for (;;) {
		MotorData *cmd;
		//if (xMotorCommandQueue != 0) {
		if (xQueueReceive(xMotorCommandQueue, &(cmd),
				(TickType_t ) 10) == pdFALSE) {
			brake();
		} else if (cmd->mData[1] >= 0) {
			if (cmd->mData[0] >= 0) {
				forwardRight(cmd->mData[1], cmd->mData[0]);
			} else if (cmd->mData[0] < 0) {
				forwardLeft(cmd->mData[1], -cmd->mData[0]);
			}
		} else if (cmd->mData[1] < 0) {
			if (cmd->mData[0] >= 0) {
				backwardRight(-cmd->mData[1], cmd->mData[0]);
			} else if (cmd->mData[0] < 0) {
				backwardLeft(-cmd->mData[1], -cmd->mData[0]);
			}
		}
	}
	//}
}


void setup() {
	isMoving = true;
	setupMotors();
	setupLEDS();
	setupBluetooth();
}


void loop() {
	xTaskCreate(xTaskBluetooth, "TaskBluetooth", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(xTaskLed, "TaskLed", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}

#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "motors.h"
#include "bluetooth.h"
#include "leds.h"
#include "music.h"
#include "pitches.h"
#define STACK_SIZE 200
#define STACK_SIZE_M 100
#define maxMotorDelayCommand portMAX_DELAY

#define CONNECTED 0
#define MOVING 1
#define STOPPED 2
#define FINISHED 3

MotorData dataMotor;

QueueHandle_t xMotorCommandQueue = xQueueCreate(1, sizeof(struct MotorData *));
QueueHandle_t xLEDGreenCommandQueue = xQueueCreate(1, sizeof(char));
QueueHandle_t xLEDRedCommandQueue = xQueueCreate(1, sizeof(char));
QueueHandle_t xMusicCommandQueue = xQueueCreate(1, sizeof(char));

void xTaskGreenLed(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 5;

	char status = MOVING;
	for (;;) {
		xQueueReceive(xLEDGreenCommandQueue, &status, 0);
		if (status == CONNECTED) {
			blinkGreenTwice();
		} else if (status == MOVING) {
			greenRunning();
		} else if (status == STOPPED) {
			greenStationary();
		}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void xTaskRedLed(void * p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 5;

	char status = MOVING;
	for (;;) {
		xQueueReceive(xLEDRedCommandQueue, &status, 0);
		if (status == MOVING) {
			redRunning();
		} else if (status == STOPPED) {
			redStationary();
		}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}

}

void xTaskPlayMusic(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 5;
	char status = STOPPED;
	for (;;) {
		xQueueReceive(xMusicCommandQueue, &status, 0);
		if (status == CONNECTED) {
			Play_Mario();
			status = STOPPED;
		} else if (status == FINISHED) {
			Play_Pirates();
			status = FINISHED;
		} else {
			Play_BabyShark();
		}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void xTaskBluetooth(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 5;

	MotorData *command;
	char currStatus = STOPPED;

	for (;;) {
		if (Serial.available()) {
			dataMotor = getData();
			if (dataMotor.command == CONNECTED) {
				currStatus = CONNECTED;
				xQueueSendToBack(xLEDGreenCommandQueue, &currStatus, 3);
				xQueueSendToBack(xLEDRedCommandQueue, &currStatus, 3);
				xQueueSendToBack(xMusicCommandQueue, &currStatus, 3);
			} else if (dataMotor.command == FINISHED) {
				currStatus = FINISHED;
				xQueueSendToBack(xLEDGreenCommandQueue, &currStatus, 3);
				xQueueSendToBack(xLEDRedCommandQueue, &currStatus, 3);
				xQueueSendToBack(xMusicCommandQueue, &currStatus, 3);
			} else {
				command = &dataMotor;
				if (xMotorCommandQueue != 0) {
					xQueueSend(xMotorCommandQueue, (void * ) &command,
							(TickType_t ) 10);
				}
			}
		}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);

	}
}

void xTaskMotor(void *p) {

	char currStatus = STOPPED;
	char prevStatus = STOPPED;

	for (;;) {
		MotorData *cmd;
		if (xMotorCommandQueue != 0) {
			if (xQueueReceive(xMotorCommandQueue, &(cmd),
					(TickType_t ) 10) == pdFALSE) {
				currStatus = STOPPED;
				brake();
			} else if (cmd->mData[1] >= 0) {
				currStatus = MOVING;
				if (cmd->mData[0] >= 0) {
					forwardRight(cmd->mData[1], cmd->mData[0]);
					if (cmd->mData[0] == 0 && cmd->mData[1] == 0) {
						currStatus = STOPPED;
					}
				} else if (cmd->mData[0] < 0) {
					forwardLeft(cmd->mData[1], -cmd->mData[0]);
				}
			} else if (cmd->mData[1] < 0) {
				currStatus = MOVING;
				if (cmd->mData[0] >= 0) {
					backwardRight(-cmd->mData[1], cmd->mData[0]);
				} else if (cmd->mData[0] < 0) {
					backwardLeft(-cmd->mData[1], -cmd->mData[0]);
				}
			}
			if (prevStatus != currStatus) {
				xQueueSendToBack(xLEDGreenCommandQueue, &currStatus, 3);
				xQueueSendToBack(xLEDRedCommandQueue, &currStatus, 3);
				xQueueSendToBack(xMusicCommandQueue, &currStatus, 3);
				prevStatus = currStatus;
			}
		}
	}
}

void setup() {
	setupLEDS();
	setupMotors();
	setupBluetooth();

	xTaskCreate(xTaskBluetooth, "TaskBluetooth", STACK_SIZE, NULL, 4, NULL);
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(xTaskPlayMusic, "TaskMusic", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(xTaskGreenLed, "TaskGreenLed", STACK_SIZE_M, NULL, 2, NULL);
	xTaskCreate(xTaskRedLed, "TaskRedLed", STACK_SIZE_M, NULL, 2, NULL);

	vTaskStartScheduler();
}

void loop() {
}

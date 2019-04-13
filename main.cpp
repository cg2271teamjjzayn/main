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
#include "constants.h"
#define STACK_SIZE 200
#define maxMotorDelayCommand portMAX_DELAY

bool isMoving;

BluetoothData bData;

QueueHandle_t xMotorCommandQueue = xQueueCreate(1,
		sizeof(struct BluetoothData *));
QueueHandle_t xLEDCommandQueue = xQueueCreate(1, sizeof(char));
QueueHandle_t xMusicCommandQueue = xQueueCreate(1, sizeof(char));

void xTaskLed(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 5;
	char status = STOPPED;
	for (;;) {
		xQueueReceive(xLEDCommandQueue, &status, 0);
		if (status == CONNECTED) {
			blinkAll_2Bytes(2, 500);
		} else if (status == MOVING) {
			runningMode();
		} else if (status == STOPPED) {
			stationaryMode();
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
		} else if (status == FINISHED) {
			Play_Pirates();
		} else {
			Play_BabyShark();
		}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void xTaskBluetooth(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 5;

	BluetoothData * motorCommand;
	char currStatus = STOPPED;

	for (;;) {
		bData = getData();
//		if (bData.command == CONNECTED) {
//			currStatus = CONNECTED;
//			xQueueSendToBack(xLEDCommandQueue, &currStatus, 3);
//			xQueueSendToBack(xMusicCommandQueue, &currStatus, 3);
//		} else if (bData.command == FINISHED) {
//			currStatus = FINISHED;
//			xQueueSendToBack(xLEDCommandQueue, &currStatus, 3);
//			xQueueSendToBack(xMusicCommandQueue, &currStatus, 3);
//		} else {
			motorCommand = &bData;
			if (xMotorCommandQueue != 0) {
				xQueueSend(xMotorCommandQueue, (void * ) &motorCommand,
						(TickType_t ) 10);
//			}
			}
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void xTaskMotor(void *p) {

	char currStatus = STOPPED;
	char prevStatus = STOPPED;

	for (;;) {
		BluetoothData * motorCommand;
		if (xMotorCommandQueue != 0) {
			if (xQueueReceive(xMotorCommandQueue, &(motorCommand),
					(TickType_t ) 10) == pdFALSE) {
				currStatus = STOPPED;
				brake();
			} else if (motorCommand->mData[1] >= 0) {
				currStatus = MOVING;
				if (motorCommand->mData[0] >= 0) {
					forwardRight(motorCommand->mData[1],
							motorCommand->mData[0]);
					if (motorCommand->mData[0] == 0
							&& motorCommand->mData[1] == 0) {
						currStatus = STOPPED;
					}
				} else if (motorCommand->mData[0] < 0) {
					forwardLeft(motorCommand->mData[1],
							-motorCommand->mData[0]);
				}
			} else if (motorCommand->mData[1] < 0) {
				currStatus = MOVING;
				if (motorCommand->mData[0] >= 0) {
					backwardRight(-motorCommand->mData[1],
							motorCommand->mData[0]);
				} else if (motorCommand->mData[0] < 0) {
					backwardLeft(-motorCommand->mData[1],
							-motorCommand->mData[0]);
				}
			}
			if (prevStatus != currStatus) {
				xQueueSendToBack(xLEDCommandQueue, &currStatus, 3);
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
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 2, NULL);
//	xTaskCreate(xTaskPlayMusic, "TaskMusic", STACK_SIZE, NULL, 2, NULL);
//	xTaskCreate(xTaskLed, "TaskLed", STACK_SIZE, NULL, 2, NULL);
	vTaskStartScheduler();
}

void loop() {
}

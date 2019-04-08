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
#define maxMotorDelayCommand portMAX_DELAY

#define CONNECT 'C'
#define MOVING 'M'
#define STOPPED 'S'
#define FIN 'F'

bool isMoving;

MotorData dataMotor;

QueueHandle_t xMotorCommandQueue = xQueueCreate(1, sizeof(struct MotorData *));
QueueHandle_t xLEDCommandQueue = xQueueCreate(1, sizeof(char));
QueueHandle_t xMusicCommandQueue = xQueueCreate(1, sizeof(char));

void xTaskLed(void *p) {
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;
	xLastWakeTime = xTaskGetTickCount();

	char status = STOPPED;

	for (;;) {
		xQueueReceive(xLEDCommandQueue, &status, 0);
		if (status == MOVING) {
			runningMode();
		} else if (status == STOPPED) {
			stationaryMode();
		} else if (status == CONNECT) {
			//connectMode(); to be implemented
		}
	}
}


void xTaskPlayMusic(void *p) {
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {
		Play_BabyShark();
//		vTaskDelayUntil(&xLastWakeTime, xFrequency);

	}
}


void xTaskBluetooth(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
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
				xQueueSendToBack(xLEDCommandQueue, &currStatus, 3);
				prevStatus = currStatus;
			}
		}
	}
}

void setup() {
	setupMotors();
	setupLEDS();
	setupBluetooth();
}


void loop() {
//	xTaskCreate(xTaskBluetooth, "TaskBluetooth", STACK_SIZE, NULL, 4, NULL);
//	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(xTaskPlayMusic, "TaskMusic", STACK_SIZE, NULL, 2, NULL);
//	xTaskCreate(xTaskLed, "TaskLed", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();


}

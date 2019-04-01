#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "motors.h"
#include "bluetooth.h"
#include "music.h"
//#include "leds.h"

#define STACK_SIZE 200
#define maxMotorDelayCommand portMAX_DELAY
bool isMoving;

QueueHandle_t xMotorCommandQueue, xBluetoothCommandQueue;
void xTaskLed (void *p) {
	if (isMoving) {
		//runningMode();
	} else {
		//stationaryMode();
	}
}


void xTaskPlayBabyShark(void *p ) {
	for (;;) {
		playTune();
	}
}


void xTaskBluetooth(void *p) {
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
	}
}

void xTaskMotor(void *p) {
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
	}
}

void setup() {
	isMoving = false;
	setupMotors();
//	setupLEDS();
//	setupBluetooth();
//	xMotorCommandQueue = xQueueCreate(10, sizeof(char));
//	xBluetoothCommandQueue = xQueueCreate(10, sizeof(char));
//	xTaskCreate(xTaskBluetooth, "TaskBluetooth", STACK_SIZE, NULL, 4, NULL);
//	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 4, NULL);
//	xTaskCreate(xTaskPlayBabyShark, "TaskBabyShark", STACK_SIZE, NULL, 2, NULL);
//	xTaskCreate(xTaskLed, "TaskLed", STACK_SIZE, NULL, 1, NULL);

}

void loop() {
	//	vTaskStartScheduler();
//	runningMode();

}

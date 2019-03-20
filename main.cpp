#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "motors.h"
#include "bluetooth.h"
#include "queues.h"
#include "music.h"
#include "leds.h"

#define STACK_SIZE 200
#define maxMotorDelayCommand portMAX_DELAY
bool isMoving;

QueueHandle_t xMotorCommandQueue;
void xTaskLed (void *p) {
	if (isMoving) {
		runningMode();
	} else {
		stationaryMode();
	}
}


void xTaskPlayBabyShark(void *p ) {

}
void xTaskMotor(void *p) {
	char command;

	for (;;) {
		command = receiveData();
		if (command != 'e') {
			Serial.println(command);
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
	setupBluetooth();
	xMotorCommandQueue = xQueueCreate(10, sizeof(char));
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 3, NULL);
}

void loop() {
	// playTune();
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(xTaskLed, "TaskLed", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}

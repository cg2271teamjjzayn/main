#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "motors.h"
#include "bluetooth.h"
#include "queues.h"
#include "music.h"

#define STACK_SIZE 200
#define maxMotorDelayCommand portMAX_DELAY

QueueHandle_t xMotorCommandQueue;

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
	setupMotors();
	setupBluetooth();
	xMotorCommandQueue = xQueueCreate(10, sizeof(char));
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 3, NULL);
}

void loop() {
	// playTune();
	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 3, NULL);
	vTaskStartScheduler();
}

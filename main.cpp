#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "motors.h"
#include "bluetooth.h"
#include "queues.h"

#define STACK_SIZE 200
#define maxMotorDelayCommand portMAX_DELAY

QueueHandle_t xMotorCommandQueue = xQueueCreate(10, sizeof(char));

void xTaskMotor(void *p) {
	char command;
	for (;;) {
		if (xQueueReceive(xMotorCommandQueue, &command, maxMotorDelayCommand)) {
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
}

void loop() {

	xTaskCreate(xTaskMotor, "TaskMotor", STACK_SIZE, NULL, 3, NULL);
	vTaskStartScheduler();
}

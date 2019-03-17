#include <Arduino.h>
#include <FreeRTOS.h>
#include "queues.h"
#include "bluetooth.h"


#define bluetoothTX 0
#define bluetoothRX 1

void setupBluetooth() {
	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(bluetoothRX), bluetoothISR, CHANGE);
}

char receiveData() {
	if(Serial.available()>0) {
		char data= Serial.read(); // reading the data received from the bluetooth module
		return data;
	}

	return 'e'; //error
}

void bluetoothISR() {
	char data = receiveData();
	xQueueSendToBackFromISR(xMotorCommandQueue, &data, false);
}


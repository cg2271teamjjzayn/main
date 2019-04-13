#include <Arduino.h>
#include <FreeRTOS.h>
#include "bluetooth.h"
#include <string.h>

BluetoothData bluetoothData;
BluetoothData nullData;

char in_code;
char allData[11];
int j = 0;

void setupBluetooth() {
	Serial.begin(9600);
}

BluetoothData getData() {

	if (Serial.available()) {
		in_code = Serial.read();
		if (in_code == 'c') {
			bluetoothData.mData[0] = 0;
			bluetoothData.mData[0] = 0;
			bluetoothData.command = 0;
			return bluetoothData;

		} else if (in_code == 'f') {
			bluetoothData.mData[0] = 0;
			bluetoothData.mData[0] = 0;
			bluetoothData.command = 3;
			return bluetoothData;

		} else if (in_code == 'e') {
			j = 0;
			char *token = strtok(allData, "#");
			bluetoothData.mData[0] = atoi(token);
			if (token != NULL) {
				token = strtok(NULL, "#");
				bluetoothData.mData[1] = atoi(token);
			}
			bluetoothData.command = 1;
			memset(allData, 0, sizeof(allData));
			return bluetoothData;

		} else {
			allData[j++] = in_code;
		}

	}
	nullData.mData[0] = 0;
	nullData.mData[1] = 0;
	nullData.command = 4;
	return nullData;
}


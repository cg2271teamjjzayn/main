#include <Arduino.h>
#include <FreeRTOS.h>
#include "bluetooth.h"
#include <string.h>

MotorData nullData;
MotorData mdata;

char in_code;
char allData[11];
int j = 0;


void setupBluetooth() {
	Serial.begin(9600);
}

MotorData getData() {


	if(Serial.available()) {
		in_code = Serial.read();
		if(in_code != 'e') {
			allData[j++] = in_code;
		} else {
			j = 0;
			char *token = strtok(allData, "#");
			mdata.mData[0] = atoi(token);
			if (token != NULL){
				token = strtok(NULL, "#");
				mdata.mData[1] = atoi(token);
			}
			if (token != NULL){
				token = strtok(NULL, "#");
				mdata.command = atoi(token);
			}
		    memset(allData, 0, sizeof(allData));
		}

		return mdata;
	}
	nullData.mData[0] = 0;
	nullData.mData[1] = 0;
	nullData.command = 4;
	return nullData;
}



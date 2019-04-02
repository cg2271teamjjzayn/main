#include <Arduino.h>
#include <FreeRTOS.h>
#include "bluetooth.h"
#include <string.h>

//typedef struct MotorData {
//   int mData[2];
//}Struct;

//typedef struct MotorData Struct;

MotorData mdata;

MotorData nullData;

char in_code;
char allData[9];
int j = 0;

void setupBluetooth() {
	Serial.begin(9600);
}

MotorData getData() {
	if(Serial.available()) {
		in_code = Serial.read();
		if(in_code != 'e') {
			allData[j++] = in_code;
		} else{
			j = 0;
			char *token = strtok(allData, "#");
			mdata.mData[0] = atoi(token);
			if (token != NULL){
				token = strtok(NULL, "#");
				mdata.mData[1] = atoi(token);
			}
			//Serial.println(allData);
		    memset(allData, 0, sizeof(allData));
		}
		return mdata;
	}
	return nullData;
}



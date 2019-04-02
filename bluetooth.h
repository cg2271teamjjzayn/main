typedef struct MotorData {
   int mData[2];
}Struct;


void setupBluetooth();
MotorData getData();
void bluetoothISR();

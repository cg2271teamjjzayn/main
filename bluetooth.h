struct MotorData {
   int mData[2];
   int command;
};


void setupBluetooth();
MotorData getData();
void bluetoothISR();

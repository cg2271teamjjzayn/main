struct BluetoothData {
   int mData[2]; // MotorData
   int command; // Bluetooth command
};

void setupBluetooth();
BluetoothData getData();
void bluetoothISR();

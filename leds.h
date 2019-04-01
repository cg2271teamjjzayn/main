//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int greenDataPin = 13;
int redLED = 7;

byte data, allLEDS;
byte dataArray[10];

void setupLEDS();
void runningMode();
void stationaryMode();

/**
 * internal function setup
 * This shifts 8 bits out MSB first,
 * on the rising edge of the clock,
 * clock idles low
 * clear everything out just in case to
 * prepare shift register for bit shifting
 * for each bit in the byte myDataOut�
 * NOTICE THAT WE ARE COUNTING DOWN in our for loop
 * This means that %00000001 or "1" will go through such
 * that it will be pin Q0 that lights.
 * if the value passed to myDataOut and a bitmask result
 * true then... so if we are at i=6 and our value is
 * %11010100 it would the code compares it to %01000000
 * and proceeds to set pinState to 1.
 * Sets the pin to HIGH or LOW depending on pinState
 * register shifts bits on upstroke of clock pin
 * zero the data pin after shift to prevent bleed through
 * stop shifting
**/
void shiftOut(int, int, byte);

/**
 * function that blinks all the LEDs
 * gets passed the number of blinks and the pause time
 * blinks the whole register based on the number of times you want to
 * blink "n" and the pause between them "d"
 * starts with a moment of darkness to make sure the first blink
 * has its full visual effect.
**/
void blinkAll_2Bytes(int , int);

void greenStationary();

void redStationary();

/**
 * load the light sequence you want from array
 * ground latchPin and hold low for as long as you are transmitting
 * move 'em out
 * return the latch pin high to signal chip that it
 * no longer needs to listen for information
 **/

void greenRunning();

void redRunning();


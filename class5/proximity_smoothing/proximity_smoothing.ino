/*
Class 5 Exercise for Intangible Interaction at ITP by Yeseul Song
1. Read proximity values from a APDS9960 sensor
2. Avaerage the last 10 values for smoothing
3. Change the brightness of 2 LEDs, one with the raw reading and the other with the average, to compare the two

Wiring (Arduino IoT33):
D9 - 220k - LED
D10 - 220k - LED
ADPS9960 SDA - A4, SCL - A5

This sketch uses a calibration technique that was introduced on this page: 
(created by David A Mellis and modified by Tom Igoe)
https://www.arduino.cc/en/tutorial/smoothing

*/

#include <Arduino_APDS9960.h>

const int numReadings = 10;  // adjust the number depending on how many values you want to average

int readings[numReadings];  // the raw proximity readings from the sensor
int readIndex = 0;  // the index of the current reading
int total = 0;  // the total to be divided by numReadings
int average = 0;  // the average

const int ledPins[2] = {9, 10};  // using array to assign multiple pins

int proximity;

void setup() {
  Serial.begin(9600);

  while (!Serial);
  
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }

  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);

  // reset every slot of the array to 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
}

void loop() {

  if (APDS.proximityAvailable()) {
    proximity = APDS.readProximity();
  }

  averageReadings();
 
  Serial.print(proximity);
  Serial.print(", ");
  Serial.println(average);

  // visualize the raw proximity reading with one LED and the averaged values with the other LED for comparison
  analogWrite(ledPins[0], proximity);
  analogWrite(ledPins[1], average);
  
  delay(100);
 
}

void averageReadings() {
  
  total = total - readings[readIndex];  // subtract the last reading in the array
 
  readings[readIndex] = proximity;  // save the latest proximity value from the sensor to the array's [readIndex]th slot
  total = total + readings[readIndex];  // add the latest proximity value to the total  
  readIndex = readIndex + 1;  // advance to the next position in the array

  if (readIndex >= numReadings) {
    readIndex = 0;  // if we're at the end of the array, reset readIndex to 0
  }

  average = total / numReadings;  // calculate the average
}

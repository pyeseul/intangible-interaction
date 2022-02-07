/*
Class 3 Exercise for Intangible Interaction at ITP by Yeseul Song
1. Read proximity values from a APDS9960 sensor
2. Avaerage the last 10 values for smoothing, using an averaging library
3. Change the brightness of 2 LEDs, one with the raw reading and the other with the average, to compare the two

Wiring (Arduino IoT33):
D5 - 220k - LED
D6 - 220k - LED
ADPS9960 SDA - A4, SCL - A5

This sketch uses a calibration technique that was introduced on this page: 
(created by David A Mellis and modified by Tom Igoe)
https://www.arduino.cc/en/tutorial/smoothing

*/

#include <Arduino_APDS9960.h>
#include <AverageValue.h>

int proximity;
int average;

// Number of values to calculate with. Prevents memory problems
const long MAX_VALUES_NUM = 10;

AverageValue<long> averageValue(MAX_VALUES_NUM);

const int ledPins[2] = {5, 6};  // using array to assign multiple pins

void setup() {
	Serial.begin(9600);

  while (!Serial);
  
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }

  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);

}

void loop() {
  
  // read proximity from the sensor
  
  if (APDS.proximityAvailable()) {
    proximity = APDS.readProximity();
  }
 
  // adding up the proximity values and calculate the average
  averageValue.push(proximity);  
  average = averageValue.average();

  // print things out wo we can see 
  Serial.print("raw proximity: ");
  Serial.print(proximity);
  Serial.print(", ");
  Serial.println(average);

  // visualize the raw proximity reading with one LED and the averaged values with the other LED for comparison
  analogWrite(ledPins[0], proximity);
  analogWrite(ledPins[1], average);
  
  delay(100);
}

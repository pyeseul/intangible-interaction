/*
Class 3 Exercise for Intangible Interaction at ITP by Yeseul Song
1. Read brightness values from a APDS9960 sensor
2. Calibrate the value range for the first 10 seconds and map that to the full range of the output
3. Read values based on the calibration

Wiring (Arduino IoT33):
D5 - 220k - LED
D6 - 220k - LED
ADPS9960 SDA - A4, SCL - A5

This sketch uses a calibration technique that was introduced on this page: 
https://www.arduino.cc/en/Tutorial/BuiltInExamples/Calibration

*/

#include <Arduino_APDS9960.h>

int r, g, b, a;
int ledPin = 8;
int ledPinOut = 4;

int sensorMin = 10000; 
int sensorMax = 0;
int calibrated_a = 0;

void setup() {
  
  // Initiate serial and make sure APDS9960 is working
  
  Serial.begin(9600);
  
  while (!Serial);
  
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }

  // set pin mode for an led (output)
  pinMode(ledPin, OUTPUT);
  pinMode(ledPinOut, OUTPUT);

}

void loop() {

  // read rgb and ambient light value from APDS9960  
  while(!APDS.colorAvailable());
  
  APDS.readColor(r, g, b, a);

  // for the first 10 seconds, 
  // fast blink led and run the calibrateSensor() function
  if (millis() < 10000) {  
    
    if (millis() % 5 == 0) { // to indicate calibrating  
      digitalWrite(ledPin, HIGH);  
    } else {
      digitalWrite(ledPin, LOW);
    }
    calibrateSensor();    

  // after the 10 seconds,   
  } else {
    
    // map and constrain the ambient light reading
    // using sensorMin and sensorMax that is set during the calibration process
    calibrated_a = map(a, sensorMin, sensorMax, 0, 255);
    calibrated_a = constrain(calibrated_a, 0, 255);
       
    Serial.print("original value:");
    Serial.print(a);
    Serial.print(" calibrated:");
    Serial.println(calibrated_a);

    // change the LED brightness
    a = map(a, 0, 1024, 0, 255);
    analogWrite(ledPinOut, calibrated_a); // change the input value to "a" to see what the raw value does
      
    delay(1000);
  }

}

void calibrateSensor() {

  // set sensorMax to and sensorMin  
  // if any value is bigger than the sensorMax, save the value to sensorMax
  if (a > sensorMax) {
    sensorMax = a;
  }
  // if any value is smaller than the sensorMin, save the value to sensorMin
  if (a < sensorMin) {
    sensorMin = a;
  }

  Serial.print("min:");
  Serial.print(sensorMin);
  Serial.print(" max:");
  Serial.println(sensorMax);

}

/* 
Class 2 exercise for Intangible Interaciton at ITP by Yeseul Song
Wiring:
Digital Pin 5 - 220k resistor - LED
Analog Pin A2 - phototransistor - 10k resistor - ground
Power - phototransistor
*/

const int sensorPin = A2;  // Analog input pin that the light sensor is attached to
const int ledPin = 5; // Digital pin that the LED is attached to

int sensorValue = 0;        // value read from the sensor
int threshold = 30;         // threshold for controlling LED and sending serial
byte belowThres = 0;

void setup() {
  Serial.begin(9600); // initialize serial
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  
  sensorValue = analogRead(sensorPin); // read the analog in value:

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(sensorValue);

  // if sensor value is lower than threshold, 
  if (sensorValue < threshold) { 
    belowThres = 1;    
  } else { // if not
    belowThres = 0;     
  } 

  // control the led and send the value to serial
  Serial.write(belowThres);
  digitalWrite(5, belowThres);
  
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}

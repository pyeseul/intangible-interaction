/* 
Class 2 exercise for Intangible Interaciton at ITP by Yeseul Song
Wiring:
Digital Pin 4 - 220k resistor - LED
Digital Pin 2 - the signal pin of a beam breaker receiver
*/

int ledPin = 4;
int receiverPin = 2;
volatile byte reading = 0; // volatile because we're going to use interrupts

void setup() {

  // define pin modes
  pinMode(receiverPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);

  // we're using interrupts to read the receiver's status
  attachInterrupt((digitalPinToInterrupt(receiverPin)), sendToSerial, CHANGE);
  
  // initiate serial: to set the speed of serial data transmission
  Serial.begin(9600);
}

void loop() {

  // turn on and off LED as the value of "reading" changes
  digitalWrite(outputPin, reading);
}
  
// when the receiver's status changes, turn on/off LED and send reading's value to serial as binary
void sendToSerial() {
  reading = !reading;
  Serial.write(reading);
}
  
 

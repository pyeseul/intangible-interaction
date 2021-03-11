// blink without delay

const int ledPin =  3;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

long interval = 1000;           // interval at which to blink (milliseconds)
 
void setup() {
  pinMode(ledPin, OUTPUT);      
}
 
void loop()
{
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) { // method 1
    previousMillis = currentMillis;  // method 1

  // if (currentMillis % 1000 == 1) {  // method 2
    
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
 
    digitalWrite(ledPin, ledState);
  }
}

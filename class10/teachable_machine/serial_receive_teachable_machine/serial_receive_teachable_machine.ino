// intangible interaction 2021
// the code receives serial inputs and triggeres different LEDs. 

byte fromP5;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}
void loop() {
  if(Serial.available()){
    fromP5 = Serial.read();    
  } 
  if (fromP5 == 1) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  } else if (fromP5 == 2) {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
}

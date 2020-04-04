byte fromP5;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  
}
void loop() {
  if(Serial.available()){
    fromP5 = Serial.read();    
  } 
  if (fromP5 == 1) {
    digitalWrite(4, HIGH);
  
  } else {
    digitalWrite(4, LOW);
  
  }
}

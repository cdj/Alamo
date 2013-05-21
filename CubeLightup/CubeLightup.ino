int led = 13;
unsigned long bufferTime = 8000; // wait this long after spinning ends to turn off
unsigned long endTime = 0; // when to turn off lights

void setup() {
  pinMode(led, OUTPUT);     
  digitalWrite(led, HIGH);
}

void loop() {
  // if spinning
  {
    digitalWrite(led, HIGH);
    endTime = millis() + bufferTime;
  }
  
  if(millis() > endTime)
  {
    digitalWrite(led, LOW);
  }
}

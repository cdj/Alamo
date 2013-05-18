const int switchPin = 2;      // digital input 

void setup() {
  Serial.begin(9600);
  // configure the digital input:
  pinMode(switchPin, INPUT);
}

void loop() {
   int sensorValue = analogRead(A2);
   // print the results:
   Serial.print("x=");
   Serial.print(sensorValue);
   Serial.print(",");

   // read the sensor:
   sensorValue = analogRead(A1);
   // print the results:
   Serial.print("y=");
   Serial.print(sensorValue);
   Serial.print(","); 
   
   // read the sensor:
   sensorValue = analogRead(A0);
   // print the results:
   Serial.print("z=");
   Serial.print(sensorValue);
   Serial.print(","); 

   // read the sensor:
   sensorValue = digitalRead(switchPin);
   // print the last reading with a println() so that
   // each set of three readings prints on a line by itself:
   Serial.println(sensorValue);
   delay(200);
 }

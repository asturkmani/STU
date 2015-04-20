/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int INductor = 12;
int val = 0;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(INductor, INPUT);
 Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() {
//  Serial.write("Hello");
val = digitalRead(INductor);
  Serial.println(val);

  // wait for a second
  
  delay(100);
}

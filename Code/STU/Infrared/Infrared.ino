/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/AnalogInput

 */

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int sumValue=0;      // variable to store the sum of all sensor values.
int avgValue = 0;    // variable to store average value
int count=1;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  cli();//stop interrupts
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 100hz increments
  OCR1A = 156;// = (16*10^6) / (100*10224) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();
}

ISR(TIMER1_COMPA_vect) {
  
  //read analog input
  sensorValue = analogRead(sensorPin);
  
    //sensorValue = analogRead(sensorPin) + sensorValue;
    sumValue = sumValue + sensorValue;
    
    
    if(count == 200){
      avgValue = sumValue/count;
      //Serial.print(avgValue);
      //Serial.println("");
      count=1;
      sumValue = 0;
    
      if(avgValue > 104){
        Serial.print("Nothing");
        Serial.println("");}
      if (avgValue >101 && avgValue <104){
        Serial.print("Plastic");
        Serial.println("");}
       if (avgValue > 90 && avgValue < 94){
         Serial.print("Metal");
         Serial.println("");}
       if (avgValue > 95 && avgValue < 100){
         Serial.print("Paper");
         Serial.println("");}
  
    }
   count=count+1;
  
}

void loop() {
  // read the value from the sensor:
  //sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  //Serial.print(sensorValue);
  // turn the ledPin off:
  //digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  //delay(500);
  //Serial.println("");
}

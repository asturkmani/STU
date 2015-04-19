/* STU - Abdel Wahab Turkmani, Ibrahim Youssef, Karim Ramadan, Khalil Fakih.

Reads analog input from an infrared receiver/transmitter. Transmitter's infrared
beam is transmitted from transmitter, reflected by substance above the
transmitter and received by the receiver. The amount of infrared reflected
is an analog input to the arduino. 

Output of SerialPort proportionally to amount of infrared reflected.*/


int sensorPin = A0;    // select the input pin for the potentiometer
//int referencePin = A1;
//int referenceValue = 0;
int sensorValue = 0;  // variable to store the value coming from the sensor
int sumValue=0;      // variable to store the sum of all sensor values.
int avgValue = 0;    // variable to store average value
int count=1;

void setup() {
  Serial.begin(9600);
  
  cli();//stop interrupts
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 100hz increments
  OCR1A = 2;// = (16*10^6) / (1000*10224) - 1 (must be <65536)
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
  Serial.println(sensorPin);
//  referenceValue = analogRead(referencePin);
  
//  sensorValue = map(sensorValue,0,1024,0,5000);
//  Serial.println(sensorValue);
    sumValue = sumValue + sensorValue;
    
    
//    if(count == 200){
//      avgValue = sumValue/count;
//      //Serial.print(avgValue);
//      //Serial.println("");
//      count=0;
//      sumValue = 0;
//      Serial.println(avgValue);
//      avgValue=0;
//    }
//   count=count+1;
  
}

void loop() {

}


/* credits to Amanda Ghassaei from */
//http://www.instructables.com/id/Arduino-Timer-Interrupts/

int sensorValue;
float voltage;
long Force;
unsigned long Resistance;
unsigned long Conductance;

void setup() {
  
  Serial.begin(9600);

}

void loop() {
  
  //get the voltage output of the force sensing circuit
  
  sensorValue = analogRead(A0);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  
  voltage = sensorValue * (5.0 / 1023.0);
  
  // print out the value you read:
  
  Serial.println(voltage);
  
  if (Conductance <= 1000) {
      Force = Conductance / 80;
      Serial.print("Force in Newtons: ");
      Serial.println(Force);      
    } else {
      Force = Conductance - 1000;
      Force /= 30;
      Serial.print("Force in Newtons: ");
      Serial.println(Force);            
    }
  

}

//NOTE: The following code is specific for a resistance of 10kohms in series with the FSR! The ranges used for linearization will change with a more or less sensitive circuit
 
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
long fsrForce;       // Finally, the resistance converted to force
long percent;
int trashVoltage=650; //this is the voltage produced with empty can and 10k ohms
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}
 
void loop(void) {
  
  fsrReading = analogRead(fsrPin);  
  //Serial.print("Analog reading = ");
  //Serial.println(fsrReading);
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  fsrVoltage=fsrVoltage-trashVoltage; //calibrate to zero the trash weight
  Serial.print("Voltage reading in mV = ");
  Serial.println(fsrVoltage+trashVoltage);  
  
  //Since this is an application that doesn't require extremely hight accuracy, we chose to linearize
  //the voltage/ force curve via a lookup table.
 
  if (fsrVoltage < 1600) {
  
    percent=0;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
    
  } 
  
  //A voltage within the range of 1600 and 2000 mV is considered 100 grams
  
  if((fsrVoltage>=1600)&&(fsrVoltage<=2000)){
    
    percent=10;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }
  
  if((fsrVoltage>2000)&&(fsrVoltage<=2300)){
    
    percent=20;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }
  
  if((fsrVoltage>2300)&&(fsrVoltage<=2600)){
    
    percent=30;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  } 
  
  if((fsrVoltage>2600)&&(fsrVoltage<=2750)){
    
    percent=40;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }  
  
  if((fsrVoltage>2750)&&(fsrVoltage<=2990)){
    
    percent=50;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }  

  if((fsrVoltage>2990)&&(fsrVoltage<=3100)){
    
    percent=60;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }  
  
  if((fsrVoltage>3100)&&(fsrVoltage<=3200)){
    
    percent=70;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }   
  
  if((fsrVoltage>3200)&&(fsrVoltage<=3333)){
    
    percent=80;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }
  
  if((fsrVoltage>3333)&&(fsrVoltage<=3400)){
    
    percent=90;
    
    Serial.print("Approximate percent of paper : ");
    Serial.println(percent); 
  
  }
  
  if (fsrVoltage>3400){
  
    Serial.print("Empty the bin!");
  
  }
  
  Serial.println("--------------------");
  delay(1000);
}

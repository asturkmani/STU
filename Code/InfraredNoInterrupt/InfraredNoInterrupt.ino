int sensorPin = A1;
int sensorValue = 0;
int sumValue = 0;
int avgValue = 0;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(1);
//  sensorValue2 = analogRead(sensor2);
  
//  sumValue = sensorValue + sumValue;
//  sumValue2 = sensorValue2 + sumValue2;
  
//  if(count==300){
//    avgValue = sumValue/count;
////    avgValue2 = sumValue2/count;
//    Serial.println(avgValue);
//    sumValue = 0;
//    avgValue = 0;
//    sumValue2 = 0;
//    avgValue2 = 0;
//    count =0;
//    delay(1000);
//  }
//  count = count + 1;
}

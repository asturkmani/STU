int sensorPin = A0;
int refPin= A1;
int refValue=0;
Â
int sensorValue = 0;
int sumValue = 0;
int avgValue = 0;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);
  refValue=analogRead(refPin);
//  Serial.println(sensorValue);
  sumValue = sensorValue + sumValue-refValue;
  
  if(count==200){
    avgValue = sumValue/count;
    Serial.println(avgValue);
    sumValue = 0;
    avgValue = 0;
    count =0;
     delay(1000);
  }
  count = count + 1;
}

int sensorValue = 0;
int sensorOld = 0;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // use serial port

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorOld = sensorValue;
  sensorValue = analogRead(0);
//  voltageDiff = abs(sensorValue)*5/1024;
  if(sensorOld != sensorValue){
    if(sensorValue > 20)
        counter++;
  }
  if(counter > 7){
    Serial.println("Glass detected");
    counter = 0;}

}

//**********************************************************************************

//**********************DIGITAL INPUT PINS******************************************

//**********************************************************************************



int Inductor = 12;



//**********************************************************************************

//***********************ANALOG INPUT PINS******************************************

//**********************************************************************************

 

int fsrPin = A0;     // the FSR and 10K pulldown are connected to a0

int IRpin = A2;      // the infrared pin 1.



//**********************************************************************************

//************************CREATE VARIABLES******************************************

//**********************************************************************************



int inductiveVal = 0; //The value input by the inductive sensor

int counterPiezo = 0;

int counterLoop = 0;

float IRval = 0;

int piezoVal = 0;

float fsrReading;     // the analog reading from the FSR resistor divider

float fsrVoltage;     // the analog reading converted to voltage

byte fsrState = 0;

long avePaperDensity=700; //we assume that the average density of paper is 7 g/L 

long canVolume=8; //our can's volume is 8L

long M=0; //the mass of the paper

long fullness=0; //the effective volume full

long percent=0; //the percent fullness





void setup() {

  

  // initialize the Inductor as an input.

  pinMode(Inductor, INPUT);

  

  Serial.begin(9600);



}

 

void loop() {  



  //************************************************************************************************

  //***************************TRASH CAN CODE STARTS HERE*******************************************

  //************************************************************************************************

 

  fsrReading = analogRead(fsrPin);

  fsrVoltage = fsrReading*5;

  fsrVoltage=fsrVoltage/1024;

  

  //Calibrated force sensor, increases in 20% increments.

  

  if( fsrVoltage < 0.7){



      Serial.println("Can is 0% full");

  }

  else if ( fsrVoltage < 1.5){

       Serial.println("Can is 20% full");

 

   }

  else if ( fsrVoltage < 2.0 ){



      Serial.println("Can is 40% full");



  }

  else if ( fsrVoltage < 2.9){



      Serial.println("Can is now 60% full");

  }

  else if (fsrVoltage < 3.3){

      Serial.println("Can is 80% full");

  }

  

   else {

      Serial.println("Can is full!");

  }

    

  //*******************************************************************************************************

  //**************************************INDUCTIVE CODE HERE**********************************************

  //*******************************************************************************************************

  

  //This is a simple digitial device. A one indicates the presence of a metal object.

  //Otherwise the object may be paper, plastic, or glass.

  

  inductiveVal = digitalRead(Inductor);

  

  

  //*******************************************************************************************************

  //**************************************INFRA RED CODE HERE**********************************************

  //*******************************************************************************************************

 

 IRval = analogRead(IRpin);

 IRval = IRval*5000.0/1024;

 

  //*******************************************************************************************************

  //**************************************FINAL DECISION AND PRINTING**************************************

  //*******************************************************************************************************



  //Here we make the decision about what is to be printed.

  

   if(inductiveVal==HIGH){

     Serial.println("Metal");}



   else if(IRval > 2600){

     Serial.print("Paper,");

     Serial.print(" voltage from IR: ");

     Serial.println(IRval);

 }

   else if(IRval < 1700 && IRval > 200){

     Serial.print("Plastic,");

     Serial.print(" voltage from IR: ");

     Serial.println(IRval);

  }

   else if(IRval >1700 && IRval < 2600){

     Serial.print("Glass,");

     Serial.print(" voltage from IR: ");

     Serial.println(IRval);}

   else

     Serial.println("Nothing is on the sensing platform");

  



  //Print the decision and percent fullnes for 2 seconds

  

  delay(2000);  



}

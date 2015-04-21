/*

fft_codec.pde
guest openmusiclabs.com 8.18.12
example sketch for running an fft on data collected
with the codecshield.  this will send out 128 bins of
data over the serial port at 115.2kb.  there is a
pure data patch for visualizing the data.

note: be sure to download the latest AudioCodec library
if yours is older than 8.16.12.  there were modifications
made that allow for code outside of the interrupt.
*/

#define SAMPLE_RATE 44 // 44.1Khz
#define ADCS 0 // no ADCs are being used
#define LOG_OUT 1 // use the log output function
#define FFT_N 64 // set to 256 point fft

// include necessary libraries
#include "FFT.h"
//#include <Wire.h>
//#include <SPI.h>
//#include <AudioCodec.h>

// create data variables for audio transfer
int analogIn = 0;
int PiezoPin = A0;
int Dword=0;
int countOfN = 0;
unsigned int count = 0;
volatile byte flag = 1;

void setup() {
  Serial.begin(115200); // use serial port
  
    //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 100hz increments
  OCR1A = 100;// = (16*10^6) / (10*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();  

}

void loop() {
  
  // wait for command to read

 
    while(1) { // reduces clock jitter
      while(flag); // wait for samples to be collected
      fft_window(); // window the data
      fft_reorder(); // reorder for fft input
      fft_run(); // process fft
      fft_mag_log(); // take output of fft
              countOfN =0;
      for (byte i=0; i< FFT_N/2 ; i++) {
        if ( fft_log_out[i] != 0){
          countOfN = countOfN + 1;}
      }
      if (countOfN > 10){
        for (byte i = 0 ; i < FFT_N/2 ; i++) { 
        Serial.print(fft_log_out[i]); // send out the data
        Serial.print(" "); 
          }
         Serial.print(";");
         Serial.println();
       }
      flag = 1; // tell the codec that processing is done
    }
    
}

// timer1 interrupt routine - data collected here
ISR(TIMER1_COMPA_vect) { // store registers (NAKED removed)
  
  if (flag) { // check if the fft is ready for more data
    fft_input[count] = analogRead(analogIn); // put real data into even bins
    fft_input[count + 1] = 0; // put zeros in odd bins
    count += 2; // increment to next bin
    if (count >= FFT_N*2) { // check if all bins are full
      flag = 0; // tell the fft to start running
      count = 0; // reset the bin counter
    }
  }
}



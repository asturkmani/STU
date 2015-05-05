#define SAMPLE_RATE 44 // 44.1Khz
#define ADCS 0 // no ADCs are being used
#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

// include necessary libraries
#include "FFT.h"

// create data variables for audio transfer
int analogIn = 0;
int PiezoPin = A0;
unsigned int count = 0;
volatile byte flag = 1;
void setup() {
Serial.begin(115200); // use serial port

}

void loop() {
  
  // wait for command to read
    while(1) { // reduces clock jitter
      while(!flag); // wait for samples to be collected
      fft_window(); // window the data
      fft_reorder(); // reorder for fft input
      fft_run(); // process fft
      fft_mag_log(); // take output of fft
      Serial.write(255); // send out a start byte
      Serial.write(fft_log_out, FFT_N/2); // send out data bytes
      Serial.println();
      flag = 1; // tell the codec that processing is done
    }
}
// timer1 interrupt routine - data collected here
ISR(TIMER1_COMPA_vect) { // store registers (NAKED removed)
  
  if (flag) { // check if the fft is ready for more data
    fft_input[count] = analogRead(PiezoPin); // put real data into even bins
    fft_input[count + 1] = 0; // put zeros in odd bins
    count += 2; // increment to next bin
    if (count >= FFT_N*2) { // check if all bins are full
      flag = 0; // tell the fft to start running
      count = 0; // reset the bin counter
    }
  }
}



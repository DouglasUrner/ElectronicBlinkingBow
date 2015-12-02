/*
** Generalized interrupt driven frequency detection on A0 at
** 38.5kHz sampling rate.
**
** Original code by Amanda Ghassaei
** http://www.instructables.com/id/Arduino-Frequency-Detection
** Sept 2012
*/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef ARDUINO_AVR_TRINKET5
// Clipping indicator variables
boolean clipping = 0;
#endif

// Data storage variables
byte newData = 0;
byte prevData = 0;
unsigned int ticks = 0; // Keeps time (interrupts), tracked in timer[].
int timer[10];          // Storage for timing of events
int slope[10];          // Slope history
unsigned int totalTimer;// Used to calculate period
unsigned int period;    // Storage for period of wave
byte index = 0;         // Current storage index
float frequency;        // Storage for frequency calculations
int maxSlope = 0;       // Used to calculate max slope as trigger point
int newSlope;           // Storage for incoming slope data

// Variables for deciding if you have a match
byte noMatch = 0;       // Counts how many non-matches you've received to reset
                        // variables if it's been too long
byte slopeTol = 3;      // Slope tolerance - adjust this if needed.
int timerTol = 10;      // Timer tolerance - adjust this if needed.

// Variables for amplitude detection
unsigned int ampTimer = 0;
byte maxAmp = 0;
byte checkMaxAmp;
byte ampThreshold = 30; // Raise if you have a very noisy signal

void setup() {

#ifndef ARDUINO_AVR_TRINKET5
  Serial.begin(9600);

  pinMode(13, OUTPUT);    // LED clipping indicator pin
  pinMode(12, OUTPUT);    // Output pin (for scope), high on positive
                          // slope zero (midpoint) crossings.
#endif

  cli();                  // Disable interrupts

  // Set up continuous sampling on analog pin 0 at 38.5kHz

  // Clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;

  ADMUX |= (1 << REFS0);  // Set reference voltage
  ADMUX |= (1 << ADLAR);  // Left align the ADC result - so we can read only
                          // the high 8 bits from the ADCH register.

  ADCSRA |= (1 << ADPS2) | (1 << ADPS0);  // Set ADC clock pre-scaler to 32 -
                                          // 16 MHz/32 = 500 KHz.
  ADCSRA |= (1 << ADATE); // Enable auto trigger
  ADCSRA |= (1 << ADIE);  // Enable interrupt when measurement completes
  ADCSRA |= (1 << ADEN);  // Enable ADC
  ADCSRA |= (1 << ADSC);  // Start ADC running

  sei();                  // Reenable interrupts
}

/*
** Interrupt Service Routine
**
** Handle new ADC data interrupts.
*/
ISR(ADC_vect) {

#ifndef ARDUINO_AVR_TRINKET5
  PORTB &= B11101111;     // Set pin 12 low, so we can watch with scope.
#endif
  prevData = newData;     // Store previous value
  newData = ADCH;         // Get high 8-bits of data from A0
  if (prevData < 127 && newData >= 127) {
    // If value is increasing and we're crossing the midpoint (offset zero).
    newSlope = newData - prevData;  // Calculate slope
    if (abs(newSlope - maxSlope) < slopeTol) {  // Consider slopes to be equal.
      // Record new data and reset time
      slope[index] = newSlope;
      timer[index] = ticks;
      ticks = 0;
      if (index == 0) { // New max slope just reset
#ifndef ARDUINO_AVR_TRINKET5
        PORTB |= B00010000; // Set pin 12 high
#endif
        noMatch = 0;
        index++;
      } else if (abs(timer[0] - timer[index]) < timerTol &&
                 abs(slope[0] - newSlope) < slopeTol) {
        // If timer duration and slopes match, sum timer values.
        totalTimer = 0;
        for (byte i = 0; i < index; i++) {
          totalTimer += timer[i];
        }
        period = totalTimer;  // Set period
        // Reset new zero index values to compare with
        timer[0] = timer[index];
        slope[0] = slope[index];
        index = 1;
#ifndef ARDUINO_AVR_TRINKET5
        PORTB |= B00010000;   // Set pin 12 high
#endif
        noMatch = 0;
      } else {
        // Crossing midpoint but not match
        index++;
        if (index > 9){
          reset();
        }
      }
    } else if (newSlope > maxSlope) {
      // If new slope is much larger than max slope.
      maxSlope = newSlope;
      ticks = 0; // Reset clock
      noMatch = 0;
      index = 0;
    } else {
      // Slope not steep enough
      noMatch++;
      if (noMatch > 9) {
        reset();
      }
    }
  }

#ifndef ARDUINO_AVR_TRINKET5
  if (newData == 0 || newData == 1023) {  // Detect clipping
    // XXX shouldn't 1023 above be 255, we're only reading 8 bits.
    PORTB |= B00100000; // Set pin 13 high - clipping indicator LED
    clipping = 1;
  }
#endif

  ticks++; // Increment timer at rate of 38.5kHz

  ampTimer++; // Increment amplitude timer
  if (abs(127 - ADCH) > maxAmp) {
    maxAmp = abs(127 - ADCH);
  }
  if (ampTimer == 1000) {
    ampTimer = 0;
    checkMaxAmp = maxAmp;
    maxAmp = 0;
  }
}     // ISR()

void reset() { // Clear out some variables
  index = 0;    // reset index
  noMatch = 0;  // reset match counter
  maxSlope = 0; // reset max slope
}

#ifndef ARDUINO_AVR_TRINKET5
void checkClipping() {  // Manage clipping indicator LED
  if (clipping) {
    PORTB &= B11011111; // Turn off clipping indicator LED
    clipping = 0;
  }
}
#endif

void loop() {

#ifndef ARDUINO_AVR_TRINKET5
  checkClipping();
#endif

  if (checkMaxAmp > ampThreshold) {
    frequency = 38462 / float(period);  // Frequency = timer rate / period
#ifndef ARDUINO_AVR_TRINKET5
    Serial.print(frequency); Serial.println(" Hz");
#endif
  }

  //delay(100); // XXX - Delete for production code.

  // Do other stuff here
}

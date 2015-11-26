#include <FastLED.h>
#include <RunningMedian.h>

#define LED_COUNT 5

void setup(){
  freqSetup();
  ledSetup();
}

void loop() {
  processFrequency();
}

void handleFrequency(float hz) {
  setLightsToColorForHz(hz);
}

void handleStop() {
  turnLightsOff();
}


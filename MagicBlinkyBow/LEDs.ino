#define DATA_PIN 6
#define NUM_LEDS 5

CRGB leds[NUM_LEDS];

void ledSetup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

#define RANGE_LOW 196
#define RANGE_HIGH 3136

void setLightsToColorForHz(float hz) {
  FastLED.showColor(CHSV(hzToHue(hz), 255, 255), 255 /* brightness */);
}

float hzToHue(float hz) {
  return constrain(map(hz, RANGE_LOW, RANGE_HIGH, 0, 360), 0, 360);
}

void turnLightsOff() {
  FastLED.show(0 /* brightness */);
}


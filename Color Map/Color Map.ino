#include <FastLED.h>

const int numLEDs = 2;
const int dataPin = 6;

CRGB leds[numLEDs];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, numLEDs);
}

void loop() {
  sweepH();
}

void sweepColors() {
  uint8_t h, s, v;

  for (h = 0; h < 255; h += 32) {
    for (s = 0; s < 255; s += 32) {
      for (v = 0; v < 255; v += 32) {
          setColor(h, s, v);
      }
    }
  }
}

void sweepH() {
  for (int h = 0; h < 255; h += 32) {
    sweepS(h);
  }
}

void sweepS(int h) {
  for (int s = 0; s < 255; s += 32) {
    sweepV(h, s);
  }
}

void sweepV(int h, int s) {
  for (int v = 0; v <= 160; v += 32) {
    setColor(h, s, v);
  }
}

void setColor(int h, int s, int v)
{
  Serial.print("h = "); Serial.print(h);
  Serial.print(" s = "); Serial.print(s);
  Serial.print(" v = "); Serial.println(v);

  leds[0] = leds[1].setHSV(h, s, v);
  FastLED.show();
  delay(1000);
}


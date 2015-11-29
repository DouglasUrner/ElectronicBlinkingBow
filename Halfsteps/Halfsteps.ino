#include <math.h>

int halfsteps(float, float);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  int rawhz;

  rawhz = analogRead(A0);
  Serial.print(rawhz); Serial.print(" ");
  Serial.println(halfsteps((float)rawhz, 440.0));
  delay(1000);
}

int halfsteps(float f, float ref) {
  return roundf(12.0 * log(f/ref) / log(2.0));
}

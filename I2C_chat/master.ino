#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  Serial.println("Master stared");
}

void loop() {
  delay(1000);
}

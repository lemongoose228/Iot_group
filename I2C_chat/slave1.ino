#include <Wire.h>

String userMessage = "";
bool sendLength = true;

void setup() {
  Serial.begin(9600);
  Wire.begin(8); 
  Serial.println("Petya (Slave 8) is ready");
}

void loop() {
  delay(100);
}

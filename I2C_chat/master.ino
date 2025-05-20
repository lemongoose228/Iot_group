#include <Wire.h>

const int slaveAddresses[] = {8, 9, 10}; 
const char* names[] = {"Petya", "Vasya", "Masha"};


void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  Serial.println("Master stared");
}

void loop() {
  delay(1000);
}

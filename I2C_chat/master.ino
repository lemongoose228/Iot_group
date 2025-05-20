#include <Wire.h>

const int slaveAddresses[] = {8, 9, 10}; 
const char* names[] = {"Petya", "Vasya", "Masha"};


void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  Serial.println("Master stared");
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Wire.requestFrom(slaveAddresses[i], 1); // запрашиваем длину сообщения
    if (Wire.available()) {
      uint8_t len = Wire.read();
      if (len > 0 && len < 100) { // допустимая длина
        delay(10); 
        Wire.requestFrom(slaveAddresses[i], len); // запрашиваем точную длину

        String message = "";
        for (int j = 0; j < len && Wire.available(); j++) {
          char c = Wire.read();
          message += c;
        }

        Serial.print("Get from ");
        Serial.print(names[i]);
        Serial.print(": ");
        Serial.println(message);
      }
    }
  }

  delay(500);
}


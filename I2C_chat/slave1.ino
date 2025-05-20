#include <Wire.h>

String userMessage = "";
bool sendLength = true;

void setup() {
  Serial.begin(9600);
  Wire.begin(8); 
  Serial.println("Petya (Slave 8) is ready");
}

void loop() {
  if (Serial.available()) {
    userMessage = readSerialMessage();
    Serial.print("New message to send: ");
    Serial.println(userMessage);
  }
  delay(100);
}

String readSerialMessage() {
  String message = "";
  while (Serial.available() == 0) {
    delay(10);
  }
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') break;
    message += c;
    delay(5);
  }
  return message;
}


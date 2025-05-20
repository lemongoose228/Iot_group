#include <Wire.h>

String userMessage = "";
bool sendLength = true;

void setup() {
  Serial.begin(9600);
  Wire.begin(9); 
  Wire.onReceive(receiveHandler);
  Wire.onRequest(requestHandler);
  Serial.println("Vasya (Slave 9) is ready");
}

void loop() {
  if (Serial.available()) {
    userMessage = readSerialMessage();
    Serial.print("New message to send: ");
    Serial.println(userMessage);
  }
  delay(100);
}

void receiveHandler(int howMany) {
  String incoming = "";
  for (int i = 0; i < howMany; i++) {
    if (Wire.available()) {
      char c = Wire.read();
      incoming += c;
    }
  }
  Serial.print("Received: ");
  Serial.println(incoming);
}

void requestHandler() {
  if (userMessage.length() > 0) {
    if (sendLength) {
      Wire.write((uint8_t)userMessage.length());
      sendLength = false;
    } else {
      Wire.write(userMessage.c_str(), userMessage.length());
      sendLength = true;
      userMessage = "";
    }
  }
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

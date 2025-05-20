#include <Wire.h>

struct Message {
  uint8_t from;
  uint8_t to;
  String text;
};

Message lastMessage;

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

void handleIncomingMessage(uint8_t fromAddress, String rawMsg) {
  int senderIndex = getNameIndexByAddress(fromAddress);

  if (rawMsg.startsWith("@last:")) {
    String replyText = rawMsg.substring(6);
    replyText.trim();
    String fullReply = String(names[senderIndex]) + ": " + replyText;
    sendMessage(lastMessage.from, fullReply);
  } else {
    int colonIndex = rawMsg.indexOf(':');
    if (colonIndex > 0) {
      String destName = rawMsg.substring(0, colonIndex);
      String msgText = rawMsg.substring(colonIndex + 1);
      msgText.trim();

      for (int j = 0; j < 3; j++) {
        if (String(names[j]) == destName) {
          String fullMsg = String(names[senderIndex]) + ": " + msgText;
          sendMessage(slaveAddresses[j], fullMsg);

          lastMessage.from = slaveAddresses[senderIndex];
          lastMessage.to = slaveAddresses[j];
          lastMessage.text = msgText;
        }
      }
    }
  }
}

void sendMessage(uint8_t toAddress, String msg) {
  Wire.beginTransmission(toAddress);
  Wire.write((uint8_t)msg.length()); 
  Wire.endTransmission();
  delay(10);

  Wire.beginTransmission(toAddress);
  Wire.write(msg.c_str(), msg.length()); // точно по длине
  Wire.endTransmission();

  Serial.print("Send to ");
  Serial.print(toAddress);
  Serial.print(": ");
  Serial.println(msg);
}

int getNameIndexByAddress(uint8_t addr) {
  for (int i = 0; i < 3; i++) {
    if (slaveAddresses[i] == addr) {
      return i;
    }
  }
  return -1;
}

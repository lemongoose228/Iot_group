int mode = 0; // 0 - transmitter, 1 - receiver
int time = 0;
String textMessage = "";
String morseMessage = "";

char letters[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z', ' '
};

String morse[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
  "....", "..", ".---", "-.-", ".-..", "--", "-.",
  "---", ".--.", "--.-", ".-.", "...", "-", "..-",
  "...-", ".--", "-..-", "-.--", "--.."
};

String start = "";

byte digits[] = {
  0b11101110, // A
  0b11011111, // B
  0b10011010, // C
  0b11011101, // D
  0b01010000, // E
  0b10001110, // F
  0b01000000, // G
  0b0101110,   // H
  0b01010000, // I
  0b01111000, // J
  0b10101110, // K
  0b01110000, // L
  0b10101100, // M
  0b00101100, // N
  0b11011101, // O
  0b11001110, // P 
  0b11111011, // Q
  0b00001100, // R
  0b10011011, // S
  0b00011110, // T
  0b01111010, // U
  0b111000,   // V
  0b1010110,   // W
  0b01101110, // X
  0b01110110, // Y
  0b11011100, // Z
  0b00000000, // empty 
};

void setup() {
    initPins();
    Serial.begin(9600);
    mode = digitalRead(PIN_TUMBLER) == HIGH ? TRANSMITTER : RECEIVER;
    Serial.println(mode == TRANSMITTER ? "TRANSMITTER" : "RECEIVER");
}

void loop() {
    updateMode();
    time = analogRead(PIN_POT);
    
    if (mode == RECEIVER) {
        fromMorse();
    } else {
        toMorse("EGO");
    }
}

void initPins() {
    pinMode(PIN_LATCH, OUTPUT);
    pinMode(PIN_DATA, OUTPUT);
    pinMode(PIN_CLOCK, OUTPUT);
    pinMode(PIN_TUMBLER, INPUT);
    pinMode(PIN_POT, INPUT);
    pinMode(PIN_TRANSMITTER, OUTPUT);
    pinMode(PIN_RECEIVER, INPUT);
}

void updateMode() {
    int currentMode = digitalRead(PIN_TUMBLER);
    if (currentMode != mode) {
        mode = currentMode;
        Serial.println(mode == TRANSMITTER ? "TRANSMITTER" : "RECEIVER");
    }
}

void setDisplay(int index) {
    Serial.println("Setting display...");
    digitalWrite(PIN_LATCH, LOW);
    shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, digits[index]);
    digitalWrite(PIN_LATCH, HIGH);
}

String decode(String morseMessage) {
  String message = ""; // Инициализация пустой строки для хранения декодированного сообщения
  String letter = "";  // Инициализация пустой строки для хранения текущего символа на основе кода Морзе
  for (int i = 0; i < morseMessage.length(); i++) {
    char current = i < morseMessage.length() ? morseMessage.charAt(i) : ' ';

    // Если текущий символ не пробел и не подчеркивание (разделитель)
    if (current != ' ' && current != '_') {
      letter += current;
    } else {
      char recognized; // распознанный символ
      for (int j = 0; j < 25; j++) {
        // Цикл по всем кодам Морзе
        if (letter == morse[j]) {
          recognized = letters[j];
          break;
        }
      }
      if (letter.length() != 0) {
        if (current == '_') {
        	message += " ";
      }
        else {
        	message += recognized;
        }
        letter = "";
      }

    }
  }

  return message;
}

char recognizeLetter(String letter) {
    for (int j = 0; j < sizeof(morse) / sizeof(morse[0]); j++) {
        if (letter == morse[j]) {
            return letters[j];
        }
    }
    return '0'; // Возвращаем пустой символ, если не найдено
}

void fromMorse() {
    int count = countSignalDuration(HIGH);
    
    if (count == 3) {
        morseMessage += " ";
    } else if (count == 7) {
        morseMessage += "_";
    } else if (count > 7) {
        processLongSignal(count);
    }

    int signal = countSignalDuration(LOW);
    
    if (signal == 1) {
        morseMessage += '.';
    } else if (signal == 3) {
        morseMessage += '-';
    }
    
    Serial.print("Message: ");
    Serial.println(morseMessage);
}

int countSignalDuration(int state) {
    int count = 0;

    while (digitalRead(PIN_RECEIVER) == state) {
        delay(time);
        count++;
    }

    return count;
}

void processLongSignal(int count) {
    textMessage += decode(morseMessage) + " ";
    
    for (int i = 0; i < textMessage.length(); i++) {
        for (int j = 0; j < sizeof(letters) / sizeof(letters[0]); j++) {
            if (letters[j] == textMessage[i]) {
                Serial.print("Letter: ");
                Serial.println(letters[j]);
                setDisplay(j);
                break;
            }
        }

        delay(1000);
        textMessage = "";
        break;
    }
}

void blink(int timeStop) {
    digitalWrite(PIN_TRANSMITTER, LOW);
    delay(timeStop * time);
    digitalWrite(PIN_TRANSMITTER, HIGH);
    delay(1 * time);
}

void toMorse(String message) {
    message.toUpperCase();

    for (char letter : message) {
        if (letter == ' ') {
            delay(7 * time);
        } else {
            String code = getMorseCode(letter);
            sendMorseCode(code);
        }

        delay(8 * time);
    }
}

String getMorseCode(char letter) {
    for (int j = 0; j < sizeof(letters) / sizeof(letters[0]); j++) {
        if (letters[j] == letter) {
            return morse[j];
        }
    }

    return "";
}

void sendMorseCode(String code) {
    for (char c : code) {
        if (c == '.') {
            blink(1);
        } else if (c == '-') {
            blink(3);
        } else if (c == ' ') {
            blink(7);
        }

        delay(3 * time); // пауза между символами
    }
}

#define DATA_PIN 2 

const unsigned long DOT_DURATION = 100;
const unsigned long DASH_DURATION = DOT_DURATION * 3;
const unsigned long SYMBOL_SPACE_DURATION = DOT_DURATION;
const unsigned long LETTER_SPACE_DURATION = DOT_DURATION * 3;
const unsigned long WORD_SPACE_DURATION = DOT_DURATION * 7;

const char morseLetters[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

const String morseCodes[] = {
  ".-",   // A
  "-...", // B
  "-.-.", // C
  "-..",  // D
  ".",    // E
  "..-.", // F
  "--.",  // G
  "....", // H
  "..",   // I
  ".---", // J
  "-.-",  // K
  ".-..", // L
  "--",   // M
  "-.",   // N
  "---",  // O
  ".--.", // P
  "--.-", // Q
  ".-.",  // R
  "...",  // S
  "-",    // T
  "..-",  // U
  "...-", // V
  ".--",  // W
  "-..-", // X
  "-.--", // Y
  "--.."  // Z
};

void setup() {
  Serial.begin(9600);

  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW);

  Serial.println("Введите сообщение (только буквы A-Z):");
}

void loop() {
  if (Serial.available() > 0) {
    String inputMessage = Serial.readStringUntil('\n');
    inputMessage.toUpperCase();
    Serial.println("Введенное сообщение: " + inputMessage);

    for (unsigned int i = 0; i < inputMessage.length(); i++) {
      char currentChar = inputMessage.charAt(i);
      bool found = false;
      for (int j = 0; j < sizeof(morseLetters) / sizeof(morseLetters[0]); j++) {
        if (currentChar == morseLetters[j]) {
          String morseCode = morseCodes[j];
          Serial.println("Код Морзе для '" + String(currentChar) + "': " + morseCode);

          for (unsigned int k = 0; k < morseCode.length(); k++) {
            if (morseCode[k] == '.') {
              digitalWrite(DATA_PIN, HIGH);
              delay(DOT_DURATION);
              digitalWrite(DATA_PIN, LOW);
              delay(SYMBOL_SPACE_DURATION);
            } 
                   
            else if (morseCode[k] == '-') {
              digitalWrite(DATA_PIN, HIGH);
              delay(DASH_DURATION);
              digitalWrite(DATA_PIN, LOW);
              delay(SYMBOL_SPACE_DURATION);
            }
          }

          delay(LETTER_SPACE_DURATION);
          found = true;
          break;
        }
      }

      if (!found && currentChar == ' ') {
        delay(WORD_SPACE_DURATION);
      }
      
      else if (!found && currentChar != ' ') {
        Serial.println("Символ '" + String(currentChar) + "' не поддерживается");
      }
    }

    Serial.println();
  }
}

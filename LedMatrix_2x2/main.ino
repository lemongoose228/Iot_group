#define LED_PIN3 6
#define LED_PIN4 9
#define LED_PIN5 10
#define LED_PIN6 11

#define BLINK_INTERVAL 5

unsigned long previousMillis = 0;
const long interval = 900;
int currentState = 0;  
bool isBlinking = false;
bool toggle = false;

const String combinationsOfLEDS[] = {
    "off", "on", "1", "2", "3", "4", 
    "12", "24", "34", "13", "14", 
    "23", "124", "234", "123", "134"
};

const String states[] = {
    "00000000", // off
    "11000000", // on
    "10010000", // 1
    "10100000", // 2
    "01010000", // 3
    "01100000", // 4
    "10000000", // 12
    "11100000", // 24
    "01000000", // 34
    "11010000", // 13
    "10010110", // 14
    "10100101", // 23
    "10000110", // 124
    "10100100", // 234
    "10000101", // 123
    "01001001"  // 134
};

void setup() {
    pinMode(LED_PIN5, OUTPUT);
    pinMode(LED_PIN6, OUTPUT);
    pinMode(LED_PIN3, OUTPUT);
    pinMode(LED_PIN4, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        startBlinking(input);
    }
    if (isBlinking) {
        blinkLEDs();
    }
}

void startBlinking(String input) {
    for (int i = 0; i < sizeof(combinationsOfLEDS) / sizeof(combinationsOfLEDS[0]); i++) {
        if (combinationMatches(input, combinationsOfLEDS[i])) {
            currentState = i;
            isBlinking = true;
            previousMillis = millis();
            break;
        }
    }
}

bool combinationMatches(String input, String combination) {
    return input.equalsIgnoreCase(combination);
}

void blinkLEDs() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= BLINK_INTERVAL) {
        previousMillis = currentMillis;
        String currentPattern = states[currentState];

        if (toggle) {
            digitalWrite(LED_PIN3, currentPattern[0] == '1' ? HIGH : LOW);
            digitalWrite(LED_PIN4, currentPattern[1] == '1' ? HIGH : LOW);
            digitalWrite(LED_PIN5, currentPattern[2] == '1' ? HIGH : LOW);
            digitalWrite(LED_PIN6, currentPattern[3] == '1' ? HIGH : LOW);
        } 
        
        else {
            digitalWrite(LED_PIN3, currentPattern[4] == '1' ? HIGH : LOW);
            digitalWrite(LED_PIN4, currentPattern[5] == '1' ? HIGH : LOW);
            digitalWrite(LED_PIN5, currentPattern[6] == '1' ? HIGH : LOW);
            digitalWrite(LED_PIN6, currentPattern[7] == '1' ? HIGH : LOW);
        }

        toggle = !toggle;
    }
}

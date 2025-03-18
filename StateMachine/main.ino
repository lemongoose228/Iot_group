#define LEFT_DIR_PIN 7
#define RIGHT_DIR_PIN 4
#define LEFT_SPEED_PIN 6
#define RIGHT_SPEED_PIN 5

#define LEFT_SIDE_FORWARD LOW
#define RIGHT_SIDE_FORWARD LOW

#define LEFT_SIDE_BACKWARD HIGH
#define RIGHT_SIDE_BACKWARD HIGH

void setup() {
  for (int i = 4; i <= 7; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

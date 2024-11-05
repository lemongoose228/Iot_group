#define LED_PIN3 6
#define LED_PIN4 9
#define LED_PIN5 10
#define LED_PIN6 11

#define BLINK_INTERVAL 500

int matrix[10][4] = {
  {0, 0, 0, 0}, // off
  {1, 1, 0, 0}, // on
  {1, 0, 0, 1}, // 1
  {1, 0, 1, 0}, // 2
  {0, 1, 0, 1}, // 3
  {0, 1, 1, 0}, // 4
  {1, 0, 0, 0}, // 1, 2
  {1, 1, 1, 0}, // 2, 4
  {0, 1, 0, 0}, // 3, 4
  {1, 1, 0, 1} // 1, 3
};

void setup() {
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(LED_PIN5, OUTPUT);
  pinMode(LED_PIN6, OUTPUT);
}

void loop() {
  //for (int i = 0; i < 10; i++) {
  //  digitalWrite(LED_PIN3, matrix[i][0]);
  //  digitalWrite(LED_PIN4, matrix[i][1]);
  //  digitalWrite(LED_PIN5, matrix[i][2]);
  //  digitalWrite(LED_PIN6, matrix[i][3]);

  //  delay(BLINK_INTERVAL);
  //}
  digitalWrite(LED_PIN5, 1); // d3
  digitalWrite(LED_PIN6, 0); // d4
  digitalWrite(LED_PIN3, 0); // d5
  digitalWrite(LED_PIN4, 1); // d6
}

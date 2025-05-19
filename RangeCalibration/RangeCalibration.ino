#define TRIG_PIN 4
#define ECHO_PIN 3
#define IR_SENSOR_PIN A0
#define LED_PIN 13

long duration;
float distance;
int irValue;

int dataCount = 0;
int maxDataCount = 50;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  distance = getDistance();
  irValue = analogRead(IR_PIN);
  
  Serial.print(distance);
  Serial.print(",");
  Serial.println(irValue);
  
  storeDistance(distance);
  
  if (enoughVariety()) {
    flashLED();
    sampleCount = 0;
  }

  delay(100);
}

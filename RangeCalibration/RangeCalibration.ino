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

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.0343 / 2.0;
}

void storeDistance(float d) {
  if (sampleCount < maxSamples) {
    lastDistances[sampleCount++] = d;
  }
}

bool enoughVariety() {
  float minD = 9999, maxD = 0;
  for (int i = 0; i < sampleCount; i++) {
    if (lastDistances[i] < minD) minD = lastDistances[i];
    if (lastDistances[i] > maxD) maxD = lastDistances[i];
  }
  
  return (maxD - minD >= 0.9f * (maxD > 0 ? maxD : 1));
}

void flashLED() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
}

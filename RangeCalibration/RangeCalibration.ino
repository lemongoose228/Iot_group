#define TRIG_PIN 4
#define ECHO_PIN 3
#define IR_SENSOR_PIN A0
#define LED_PIN 13

long duration;
float distance;
int irValue;

int dataCount = 0;
int maxDataCount = 50;

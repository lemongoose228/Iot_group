#define PHOTO_SENSOR_PIN  A0

void setup() {
    Serial.begin(9600);
}

void loop() {
    int photo_val = analogRead(PHOTO_SENSOR_PIN);
    Serial.println(photo_val);
    delay(500);

}

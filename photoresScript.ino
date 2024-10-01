#define PHOTO_SENSOR_PIN  A0

void setup() {
    Serial.begin(9600);
}

void loop() {
    int photo_val = analogRead(PHOTO_SENSOR_PIN);
    
    String formatted_val = String(photo_val);
    while (formatted_val.length() < 4) {
        formatted_val = "0" + formatted_val;
    }
  
    Serial.println(formatted_val);
    delay(500);
}

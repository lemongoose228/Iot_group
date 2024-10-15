#define PHOTO_SENSOR_PIN  A0

void setup() {
    Serial.begin(9600);
    pinMode(PHOTO_SENSOR_PIN, INPUT);
}

void loop() {
    if (Serial.available() != 0) {
        switch (Serial.read()) {
            case 'p':
                readPhotoSensor();
                break;
            default:
                break;
        }
    }
}

void readPhotoSensor() {
    int photo_val = analogRead(PHOTO_SENSOR_PIN);
    
    String formatted_val = String(photo_val);
    while (formatted_val.length() < 4) {
        formatted_val = "0" + formatted_val;
    }
  
    Serial.print(formatted_val);
} 

#include <Wire.h>

#define LED 13        
#define SENSOR_ADDR 0x53

void setup() { 
  Wire.begin(); 
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  Wire.beginTransmission(SENSOR_ADDR);
  Wire.write(0x2D);     
  Wire.write(0x08);    
  Wire.endTransmission();
}

void readAccel(float &x, float &y, float &z) {
  Wire.beginTransmission(SENSOR_ADDR);
  Wire.write(0x32); 
  Wire.endTransmission(false);
  Wire.requestFrom(SENSOR_ADDR, 6);

  int16_t rawX = Wire.read() | (Wire.read() << 8);
  int16_t rawY = Wire.read() | (Wire.read() << 8);
  int16_t rawZ = Wire.read() | (Wire.read() << 8);

  x = rawX / 256.0;
  y = rawY / 256.0;
  z = rawZ / 256.0;
}

void loop() {
  float ax, ay, az;
  readAccel(ax, ay, az);

  Serial.print("X: "); Serial.print(ax);
  Serial.print(" Y: "); Serial.print(ay);
  Serial.print(" Z: "); Serial.println(az);

  float total = abs(ax) + abs(ay) + abs(az);

  if (total < 0.21) {
    digitalWrite(LED, HIGH);
    Serial.println("Невесомость!");
  } 
  
  else {
    digitalWrite(LED, LOW);
  }

  delay(20);
}

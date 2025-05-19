void setup() { 
  Wire.begin(); 
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  Wire.beginTransmission(SENSOR_ADDR);
  Wire.write(0x2D);     
  Wire.write(0x08);    
  Wire.endTransmission();
}

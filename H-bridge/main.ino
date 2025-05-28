const int motorPinA = 3;
const int motorPinB = 5;

 void setup() {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  Serial.begin(9600);
  stopMotor();
}



const int motorPinA = 3;
const int motorPinB = 5;

 void setup() {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  Serial.begin(9600);
  stopMotor();
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() < 2) {
      Serial.println("Некорректная команда.");
      return;
    }

    char command = input.charAt(0);
    int speed = input.substring(1).toInt();

    switch (command) {
      case 'f':
        setMotorForward(speed);
        break;
      case 'b':
        setMotorBackward(speed);
        break;
      case 's':
        stopMotor();
        break;
      default:
        Serial.println("Неизвестная команда. Используйте f/b/s + скорость");
        break;
    }
  }
}

 void setMotorForward(int speed) {
  speed = constrain(speed, 0, 255);
  analogWrite(motorPinA, speed);
  analogWrite(motorPinB, 0);
  Serial.print("Вперёд со скоростью ");
  Serial.println(speed);
}


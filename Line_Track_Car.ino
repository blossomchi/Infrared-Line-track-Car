
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
volatile int Right;
volatile int Left;

void Infrared_Tracing() {
  int Left_Tra_Value = 0;
  int Center_Tra_Value = 0;
  int Right_Tra_Value = 0;
  int Black = 1;
  Left_Tra_Value = analogRead(A4);
  Center_Tra_Value = digitalRead(10);
  Right_Tra_Value = analogRead(A5);
  Right = (map(Right_Tra_Value, 1, 1023, 1, 100));
  Left = (map(Left_Tra_Value, 1, 1023, 1, 100));
  if (Left < 50 && (Center_Tra_Value == Black && Right < 50)) {
    //forward
     motor1.setSpeed(120);
     motor1.run(FORWARD);
     motor2.setSpeed(120);
     motor2.run(FORWARD);
     motor3.setSpeed(120);
     motor3.run(FORWARD);
     motor4.setSpeed(120);
     motor4.run(FORWARD);

  } else if (Left > 50 && (Center_Tra_Value == Black && Right < 50)) {
    //left
     motor1.setSpeed(80);
     motor1.run(FORWARD);
     motor2.setSpeed(80);
     motor2.run(FORWARD);
     motor3.setSpeed(10);
     motor3.run(FORWARD);
     motor4.setSpeed(10);
     motor4.run(FORWARD);
  } else if (Left > 50 && (Center_Tra_Value != Black && Right < 50)) {
    //left
     motor1.setSpeed(120);
     motor1.run(FORWARD);
     motor2.setSpeed(120);
     motor2.run(FORWARD);
     motor3.setSpeed(10);
     motor3.run(FORWARD);
     motor4.setSpeed(10);
     motor4.run(FORWARD);
  } else if (Left < 50 && (Center_Tra_Value != Black && Right > 50)) {
    //right
     motor1.setSpeed(10);
     motor1.run(FORWARD);
     motor2.setSpeed(10);
     motor2.run(FORWARD);
     motor3.setSpeed(120);
     motor3.run(FORWARD);
     motor4.setSpeed(120);
     motor4.run(FORWARD);
  } else if (Left < 50 && (Center_Tra_Value == Black && Right > 50)) {
    //right
     motor1.setSpeed(10);
     motor1.run(FORWARD);
     motor2.setSpeed(10);
     motor2.run(FORWARD);
     motor3.setSpeed(80);
     motor3.run(FORWARD);
     motor4.setSpeed(80);
     motor4.run(FORWARD);
  } else if (Left > 50 && (Center_Tra_Value == Black && Right > 50)) {
    //stop
     motor1.setSpeed(0);
     motor1.run(RELEASE);
     motor2.setSpeed(0);
     motor2.run(RELEASE);
     motor3.setSpeed(0);
     motor3.run(RELEASE);
     motor4.setSpeed(0);
     motor4.run(RELEASE);
  }
}

void setup(){
  pinMode(10, INPUT);
  Serial.begin(9600);
  Right = 0;
  Left = 0;
}

void loop(){
  Infrared_Tracing();

}

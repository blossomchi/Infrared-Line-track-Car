
#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
volatile int Right_IR_Value;
volatile int Left_IR_Value;
volatile int rightDistance;
volatile int leftDistance;
volatile int middleDistance;
volatile int D_min;
volatile int D_max;
Servo servo_9;

void Obstacle_Avoidance_Main() {
  Left_IR_Value = digitalRead(A1);
  Right_IR_Value = digitalRead(A2);
  Infrared_Obstacle_Avoidance();
  Ultrasonic_obstacle_avoidance();
}

void Move_forward() {
   motor1.setSpeed(200);
   motor1.run(FORWARD);
   motor2.setSpeed(200);
   motor2.run(FORWARD);
   motor3.setSpeed(200);
   motor3.run(FORWARD);
   motor4.setSpeed(200);
   motor4.run(FORWARD);
}

void Infrared_Obstacle_Avoidance() {
  if (Left_IR_Value == 1 && Right_IR_Value == 0) {
    MoveRight();
    delay(2000);

  } else if (Left_IR_Value == 0 && Right_IR_Value == 1) {
    Move_left();
    delay(2000);
  } else if (Left_IR_Value == 1 && Right_IR_Value == 1) {
    //default movement forward
    Move_forward();
  } else if (Left_IR_Value == 0 && Right_IR_Value == 0) {
    delay(500);
    Move_backward();
  }
}

void Move_backward() {
   motor1.setSpeed(200);
   motor1.run(BACKWARD);
   motor2.setSpeed(200);
   motor2.run(BACKWARD);
   motor3.setSpeed(200);
   motor3.run(BACKWARD);
   motor4.setSpeed(200);
   motor4.run(BACKWARD);
}

void Move_left() {
   motor1.setSpeed(255);
   motor1.run(FORWARD);
   motor2.setSpeed(255);
   motor2.run(FORWARD);
   motor3.setSpeed(12);
   motor3.run(FORWARD);
   motor4.setSpeed(12);
   motor4.run(FORWARD);
  delay(1000);
}

float checkdistance_A0_A3() {
  digitalWrite(A0, LOW);
  delayMicroseconds(2);
  digitalWrite(A0, HIGH);
  delayMicroseconds(10);
  digitalWrite(A0, LOW);
  float distance = pulseIn(A3, HIGH) / 58.00;
  delay(10);
  return distance;
}

void Ultrasonic_obstacle_avoidance() {
  middleDistance = checkdistance_A0_A3();
  if (middleDistance < 18) {
    Stop();
    delay(100);
    Move_backward();
    delay(50);

  }
  if (middleDistance <= D_min) {
    delay(500);
    servo_9.write(10);
    delay(500);
    rightDistance = checkdistance_A0_A3();
    delay(500);
    servo_9.write(100);
    delay(500);
    servo_9.write(180);
    delay(500);
    leftDistance = checkdistance_A0_A3();
    delay(500);
    servo_9.write(100);
    delay(500);
    //Movement code
    if (rightDistance >= leftDistance) {
      Move_backward();
      delay(100);
      MoveRight();
      delay(300);

    } else if (rightDistance < leftDistance) {
      Move_backward();
      delay(100);
      Move_left();
      delay(300);
    } else if (rightDistance < D_max && leftDistance < D_max) {
      Stop();
      delay(50);
      Move_backward();
      delay(50);
    }

  }
}

void MoveRight() {
   motor1.setSpeed(12);
   motor1.run(FORWARD);
   motor2.setSpeed(12);
   motor2.run(FORWARD);
   motor3.setSpeed(255);
   motor3.run(FORWARD);
   motor4.setSpeed(255);
   motor4.run(FORWARD);
  delay(1000);
}

void Stop() {
   motor1.setSpeed(0);
   motor1.run(RELEASE);
   motor2.setSpeed(0);
   motor2.run(RELEASE);
   motor3.setSpeed(0);
   motor3.run(RELEASE);
   motor4.setSpeed(0);
   motor4.run(RELEASE);
}

void setup(){
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Right_IR_Value = 1;
  Left_IR_Value = 1;
  rightDistance = 0;
  leftDistance = 0;
  middleDistance = 0;
  D_min = 30;
  D_max = 50;
  servo_9.attach(9);
  motor1.setSpeed(0);
   motor1.run(RELEASE);
   motor2.setSpeed(0);
   motor2.run(RELEASE);
   motor3.setSpeed(0);
   motor3.run(RELEASE);
   motor4.setSpeed(0);
   motor4.run(RELEASE);
  Stop();
  servo_9.write(100);
  delay(100);
  pinMode(A0, OUTPUT);
  pinMode(A3, INPUT);
}

void loop(){
  Obstacle_Avoidance_Main();

}

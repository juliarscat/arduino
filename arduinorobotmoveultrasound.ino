//Sample code for a robot that uses 2 servos and a ultrasonic module to avoid obstacles

#include <Servo.h>
#include <Ultrasonic.h>

Servo rightWheel;
Servo leftWheel;

Ultrasonic frontSensor(7, 6);
int distance;

void setup() {
  rightWheel.attach(9);
  leftWheel.attach(10);
  Serial.begin(9600);
}

void loop() {
  distance = frontSensor.read();
  if (distance > 20) {
    moveForward();
  }
  else {
    stopRobot();
    turnRight();
  }
}

void moveForward() {
  rightWheel.write(90);
  leftWheel.write(90);
}

void stopRobot() {
  rightWheel.write(0);
  leftWheel.write(0);
}

void turnRight() {
  rightWheel.write(0);
  leftWheel.write(90);
  delay(1000);
  stopRobot();
}

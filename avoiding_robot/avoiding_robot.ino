#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

#define trig A0
#define echo A1
#define max_distance 300
#define max_speed 160
#define max_speed_offset 40
#define coll_dist 30
#define turn_dist coll_dist+20
NewPing sonar(trig, echo, max_distance);

AF_DCMotor leftmotor1(1, MOTOR12_1KHZ);
AF_DCMotor leftmotor2(2, MOTOR12_1KHZ);
AF_DCMotor rightmotor1(3, MOTOR34_1KHZ);
AF_DCMotor rightmotor2(4, MOTOR34_1KHZ);
Servo myservo;

int leftdistance, rightdistance;
int curdist = 0;
String motorset = "";
int speedset = 0;

void setup(){
  myservo.attach(10);
  myservo.write(90);
  delay(1000);
}

void loop(){
  myservo.write(90);
  delay(90);
  curdist = redping();
  if (curdist < coll_dist){
    changepath();
  }
  moveforward();
  delay(500);
}

void changepath(){
  movestop();
  myservo.write(36);
  delay(500);
  rightdistance = redping();
  delay(700);
  myservo.write(144);
  delay(700);
  leftdistance = redping();
  delay(500);
  myservo.write(90);
  delay(100);
  comparedistance();
}

void comparedistance(){
  if (leftdistance > rightdistance){
    turnleft();
  } else if (rightdistance > leftdistance){
    turnright();
  }else {
    turnaround();
  }
}

int redping(){
  delay(70);
  unsigned int us = sonar.ping();
  int cm = us/US_ROUNDTRIP_CM;
  return cm;
}

void movestop(){
  leftmotor1.run(RELEASE);
  leftmotor2.run(RELEASE);
  rightmotor1.run(RELEASE);
  rightmotor2.run(RELEASE);
}

void moveforward(){
  motorset = "FORWARD";
  leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(FORWARD);
  rightmotor2.run(FORWARD);
  for (speedset = 0; speedset < max_speed; speedset +=2){
    leftmotor1.setSpeed(speedset);
    leftmotor2.setSpeed(speedset);
    rightmotor1.setSpeed(speedset);
    rightmotor2.setSpeed(speedset);
  delay(5);
  }
}

void movebackward(){
  motorset = "BACKWARD";
  leftmotor1.run(BACKWARD);
  leftmotor2.run(BACKWARD);
  rightmotor1.run(BACKWARD);
  rightmotor2.run(BACKWARD);
  for (speedset = 0; speedset < max_speed; speedset +=2){
    leftmotor1.setSpeed(speedset);
    leftmotor2.setSpeed(speedset);
    rightmotor1.setSpeed(speedset);
    rightmotor2.setSpeed(speedset);
  delay(5);
  }
}

void turnright(){
  motorset = "RIGHT";
  leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(BACKWARD);
  rightmotor2.run(BACKWARD);
  rightmotor1.setSpeed(speedset+max_speed_offset);
  rightmotor2.setSpeed(speedset+max_speed_offset);
  delay(1500);
  motorset = "FORWARD";
  leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(FORWARD);
  rightmotor2.run(FORWARD);
}

void turnleft(){
   motorset = "LEFT";
  leftmotor1.run(BACKWARD);
  leftmotor2.run(BACKWARD);
  leftmotor1.setSpeed(speedset+max_speed_offset);
  leftmotor2.setSpeed(speedset+max_speed_offset);
  rightmotor1.run(FORWARD);
  rightmotor2.run(FORWARD);
  delay(1500);
  motorset = "FORWARD";
  leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(FORWARD);
  rightmotor2.run(FORWARD);
}

void turnaround(){
  motorset = "RIGHT";
  leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(BACKWARD);
  rightmotor2.run(BACKWARD);
  rightmotor1.setSpeed(speedset+max_speed_offset);
  rightmotor2.setSpeed(speedset+max_speed_offset);
  delay(1500);
  motorset = "FORWARD";
  leftmotor1.run(FORWARD);
  leftmotor2.run(FORWARD);
  rightmotor1.run(FORWARD);
  rightmotor2.run(FORWARD);
}
  

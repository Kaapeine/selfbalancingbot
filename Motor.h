#include <AFMotor.h>

AF_DCMotor AMotor(1);
AF_DCMotor BMotor(2);

void motorsetup(int ivel) {
  AMotor.setSpeed(ivel);
  BMotor.setSpeed(ivel);
}

void setright(int vel, int dir) { // 1 is forward, 0 is backward
  AMotor.setSpeed(vel);
  if (dir == 1) AMotor.run(FORWARD);
  else if (dir == 0) AMotor.run(BACKWARD);
}

void setleft(int vel, int dir) { // 1 is forward, 0 is backward
  BMotor.setSpeed(vel);
  if (dir == 1) BMotor.run(FORWARD);
  else if (dir == 0) BMotor.run(BACKWARD);
}

void forward(int vel) {
  AMotor.setSpeed(vel);
  BMotor.setSpeed(vel);
  
  AMotor.run(FORWARD);
  BMotor.run(FORWARD);
}

void backward(int vel) {
  AMotor.setSpeed(vel);
  BMotor.setSpeed(vel);
  
  AMotor.run(BACKWARD);
  BMotor.run(BACKWARD);
}

void right(int vel) {
  AMotor.setSpeed(vel);
  BMotor.setSpeed(vel);
  
  AMotor.run(BACKWARD);
  BMotor.run(FORWARD);
}

void left(int vel) {
  AMotor.setSpeed(vel);
  BMotor.setSpeed(vel);
  
  AMotor.run(FORWARD);
  BMotor.run(BACKWARD);
}

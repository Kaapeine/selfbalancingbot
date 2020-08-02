#include "MPU.h"
#include "Motor.h"
//#include <PID_v1.h>

float y, p, r;
unsigned long nextTime = 0;
float lastTime = 0;
float iTerm = 0;
float maxPID = 150;
float oldValue = 0;

//PID
double originalSetpoint = 25;
double setpoint = originalSetpoint;
double movingAngleOffset = 0.1;
double input, output;
double Kp = 7;
double Kd = 0;
double Ki = 0;
//PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  mpusetup();
  motorsetup(150);
  p = 0;
//  pid.SetMode(AUTOMATIC);
}

void loop()
{
  //  MPU Part
  mpuloop(&y, &p, &r);
  //  Serial.print("ypr\t");
  //  Serial.print(y * 180/M_PI);
  //  Serial.print("\t");
  //  Serial.print(p * 180/M_PI);
  //  Serial.print("\t");
  //  Serial.print(r * 180/M_PI);
  //  Serial.print("\t");
  //  Serial.println(originalSetpoint);

  // PID Part
//  if (nextTime < millis())
//  {
    nextTime = millis() + 10; // Run every 10 milliseconds
    input = p * 180/M_PI;
    output = pid(originalSetpoint, input, Kp, Kd, Ki);
    if (output >= 0) {
      setright(output, 0);
      setleft(output, 0);
    }
    else {
      setright(output * -1, 1);
      setleft(output * -1, 1);
    }
//
  
  Serial.print(output);
  Serial.print("\t");
  Serial.print(input);
  Serial.print("\t");
  Serial.println(p * 180/M_PI);

}

double pid(double target, double current, double Kp, double Kd, double Ki) {
  // Calculate the time since function was last called
  double thisTime = millis();
  double dT = thisTime - lastTime;
  lastTime = thisTime;

  // Calculate error between target and current values
  double error = target - current;

  // Calculate the integral term
  iTerm += error * dT; 

  // Calculate the derivative term (using the simplification)
  double dTerm = (oldValue - current) / dT;

  // Set old variable to equal new ones
  oldValue = current;

  // Multiply each term by its constant, and add it all up
  double result = (error * Kp) + (iTerm * Ki) + (dTerm * Kd);

  // Limit PID value to maximum values
  if (result > maxPID) result = maxPID;
  else if (result < -maxPID) result = -maxPID;

  return result;
}

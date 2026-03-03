#include "Motor_Function.hpp"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *L_Motor = AFMS.getMotor(1);
Adafruit_DCMotor *R_Motor = AFMS.getMotor(4);


//Functions for object avoidance and motor tuning
void Go_Forward(int speed, int duration){
  
  L_Motor->setSpeed(speed);
  R_Motor->setSpeed(speed);

  L_Motor->run(FORWARD);
  R_Motor->run(FORWARD);

  delay(duration);

  L_Motor->run(RELEASE);
  R_Motor->run(RELEASE);

}

#ifndef MOTOR_FUNCTION_HPP
#define MOTOR_FUNCTION_HPP

#include <Adafruit_MotorShield.h>

extern Adafruit_MotorShield AFMS;

extern Adafruit_DCMotor *L_Motor;
extern Adafruit_DCMotor *R_Motor;

void Go_Forward(int speed, int duration);

#endif
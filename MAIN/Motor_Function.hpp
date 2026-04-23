#ifndef MOTOR_FUNCTION_HPP
#define MOTOR_FUNCTION_HPP

#include <Adafruit_MotorShield.h>

extern Adafruit_MotorShield AFMS;

extern Adafruit_DCMotor *L_Motor;
extern Adafruit_DCMotor *R_Motor;

void Go_Forward(int speed);
void Stop_Motors();
void Turn_Left(int speed, int duration);
void Turn_Right(int speed, int duration);
void RightTurn_90(int speed, int duration);
void LeftTurn_90(int speed, int duration);
void SetMotorSpeeds(int leftSpeed, int rightSpeed);
void Follow_Adjust(float angleError, float distanceError);

#endif
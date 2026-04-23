#include "Motor_Function.hpp"
#include "Ultrasonic_Function.hpp"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *L_Motor = AFMS.getMotor(1);
Adafruit_DCMotor *R_Motor = AFMS.getMotor(4);


//Functions for object avoidance and motor tuning
void Go_Forward(int speed){
  
  L_Motor->setSpeed(speed);
  R_Motor->setSpeed(speed);

  L_Motor->run(FORWARD);
  R_Motor->run(FORWARD);

}
void Stop_Motors(){

  L_Motor->run(RELEASE);
  R_Motor->run(RELEASE);

}
void Turn_Left(int speed, int duration){

  L_Motor->setSpeed(speed);
  R_Motor->setSpeed(speed);

  L_Motor->run(FORWARD);
  R_Motor->run(FORWARD);
}
void SetMotorSpeeds(int leftSpeed, int rightSpeed)
{
    if(leftSpeed < 0) leftSpeed = 0;
    if(leftSpeed > 255) leftSpeed = 255;

    if(rightSpeed < 0) rightSpeed = 0;
    if(rightSpeed > 255) rightSpeed = 255;

    L_Motor->setSpeed(leftSpeed);
    R_Motor->setSpeed(rightSpeed);

    L_Motor->run(FORWARD);
    R_Motor->run(FORWARD);
}

void Follow_Adjust(float angleError, float distanceError)
{
    int baseSpeed = 100;

    // Distance control
    if(distanceError > 1.25) {
        baseSpeed = 100;
    }
    else if(distanceError < 1.25) {
        baseSpeed = 0;
    }

    //Steering correction
    int correction = (int)(angleError * 0.4);
    Serial.print("correction: ");
    Serial.print(correction);
    int leftSpeed  = baseSpeed - correction;
    int rightSpeed = baseSpeed + correction;

    SetMotorSpeeds(leftSpeed, rightSpeed);
}


void Turn_Right(int speed, int duration){

  L_Motor->setSpeed(speed);
  R_Motor->setSpeed(speed);

  L_Motor->run(FORWARD);
  R_Motor->run(FORWARD);
}

void RightTurn_90(int speed, int duration){

  L_Motor->setSpeed(speed);
  R_Motor->setSpeed(speed/2);

  L_Motor->run(FORWARD);
  R_Motor->run(FORWARD);

  delay(duration);

  Stop_Motors();
}
void LeftTurn_90(int speed, int duration){

  L_Motor->setSpeed(speed/2);
  R_Motor->setSpeed(speed);

  L_Motor->run(FORWARD);
  R_Motor->run(FORWARD);

  delay(duration);

  Stop_Motors();
}

float Calc_Time(float left, float right){
  //rpm_r
  float vel_r = 0.55;
  //rpm_l
  float vel_l = .275;

  //CALCULATE ANGLE
  float theta = atan2(9.25, (left - right));
  //CONVERT TO DEGREES
  float theta_deg = theta * (180.0 / PI);
  //ARC LENGTH
  float arcLength = 2 * PI * vel_r * (theta_deg / 360.0);
  //SPEED CALC
  float velocity = (100 * PI * .105) / 60.0;
  //TIME = DISTANCE/SPEED
  float time = arcLength / velocity;
  
  return time; //seconds
  
}
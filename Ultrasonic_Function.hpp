#ifndef ULTRASONIC_FUNCTION_HPP
#define ULTRASONIC_FUNCTION_HPP

#include <Arduino.h>

//Sensor Clarification
#define LEFT_SENSOR   0
#define FRONT_SENSOR  2
#define RIGHT_SENSOR  1

//Public variables
extern int distances[3];

//Functions
void Ultrasonic_Init();
void Ultrasonic_ReadAll();
float  Ultrasonic_GetLeft();
float  Ultrasonic_GetFront();
float Ultrasonic_GetRight();
int  Ultrasonic_GetMin();

int readUltrasonic(int trigPin, int echoPin);

#endif
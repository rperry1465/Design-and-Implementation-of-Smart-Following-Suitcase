#include "Ultrasonic_Function.hpp"

//Pin definitions
#define trigPin0 9
#define echoPin0 8
#define trigPin1 A1
#define echoPin1 A0
#define trigPin2 A2
#define echoPin2 A3

//Distance storage
int distances[3];

int readUltrasonic(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    int distance = (duration / 2) / 29.1;

    return distance;
}
void Ultrasonic_Init()
{
    pinMode(trigPin0, OUTPUT);
    pinMode(echoPin0, INPUT);

    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);

    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
}
void Ultrasonic_ReadAll()
{
    distances[0] = readUltrasonic(trigPin0, echoPin0);
    distances[1] = readUltrasonic(trigPin1, echoPin1);
    distances[2] = readUltrasonic(trigPin2, echoPin2);
}

//Getters
float Ultrasonic_GetLeft()  { return distances[LEFT_SENSOR]; }
float Ultrasonic_GetFront() { return distances[FRONT_SENSOR]; }
float Ultrasonic_GetRight() { return distances[RIGHT_SENSOR]; }

//Minimum Distance
int Ultrasonic_GetMin()
{
    int minDistance = distances[0];

    for(int i = 1; i < 3; i++)
    {
        if(distances[i] < minDistance)
            minDistance = distances[i];
    }

    return minDistance;
}

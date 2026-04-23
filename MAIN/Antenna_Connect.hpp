#ifndef ANTENNA_CONNECT_HPP
#define ANTENNA_CONNECT_HPP

#include <Arduino.h>

//Call Antenna Init
void Antenna_Init();

//Declare Struct for Outputting Function as Array
struct TrackingData {
  float distance;
  float direction;
};

//Declare Get_Direction function
TrackingData Get_Antenna_Data();

#endif
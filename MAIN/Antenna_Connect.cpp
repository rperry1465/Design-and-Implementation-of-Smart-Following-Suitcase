#include "Antenna_Connect.hpp"

void Antenna_Init()
{
  //Init Antenna Serial Port (Port 1 @ 115200 Baud Rate)
  Serial1.begin(115200);
}

//Call Get_Direction as a "TrackingData function" storing it as array
TrackingData Get_Antenna_Data() {

//Store Last Values
static TrackingData lastData = {0.0, 0.0}; 
  
  //Check if Serial Port 1 active
  if (Serial1.available() > 0) {
    //If active read through string until "carriage return" found (this is the default end value for ANTB11)
    String input = Serial1.readStringUntil('\r');
    Serial.print(input);
    
    //Check for whether string is 0 or empty, then return last data to reduce continuity issues
    if (input.indexOf("+UUDF") == -1) {
      return lastData;
    }

    //Create buffer array for converting input string to Character Array
    char buf[input.length() + 1];
    input.toCharArray(buf, sizeof(buf));

    //Iterate through characters in string until comma is found, set each section as it's own token/array point
    float values[10];
    int i = 0;
    char* token = strtok(buf, ",");
    
    //Convert token characters to float for calculations/output
    while (token != NULL && i < 10) {
      if (i > 0) {
        values[i] = atof(token);
      }
      token = strtok(NULL, ",");
      i++;
    }

    //Calculate distance using n as environmental factor, and meter_strength as dB of antenna at 1m distance. (Environmental factor a scale of 1-4 with 1 being open environment and 4 being very busy or obstructed environment)
    float meter_strength = -50; 
    float envir_factor = 4.0;
    //RSSI to distance calculation is 10^((meter_strength-current_strength)/(10*envir_factor))
    float exponent = (meter_strength - values[1]) / (10.0 * envir_factor);
    lastData.distance = pow(10, exponent);//*39.3701;


    lastData.direction = values[2];
  }

  return lastData;

}


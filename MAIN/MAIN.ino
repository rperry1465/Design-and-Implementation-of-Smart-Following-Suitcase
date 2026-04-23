#include "Ultrasonic_Function.hpp"
#include "Antenna_Connect.hpp"
#include "Motor_Function.hpp"
#include "Behavior.hpp"

void setup() {

  Serial.begin(115200);
  SerialUSB.begin(9600);

  if(!AFMS.begin()){
    Serial.println("Motor Shield not detected");
    while(1);
  }

  Ultrasonic_Init();
  Behavior_Init();
  Antenna_Init();

  Serial.println("Suitcase Ready");
}

void loop(){

  Behavior_Update();

}



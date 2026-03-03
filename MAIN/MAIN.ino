#include "Motor_Function.hpp"

void setup() {
  Serial.begin(9600); // Serial for debugging

  if(!AFMS.begin()){ //Check Shield Connection
    Serial.println("Could not connect to Motorshield, reset program.");
    while(1);
  }

  //Motor tuning (Comment out when done)
  delay(2000);
  Go_Forward(130,1000);

}

void loop() {
  

}

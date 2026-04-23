#include "Behavior.hpp"
#include "Ultrasonic_Function.hpp"
#include "Antenna_Connect.hpp"
#include "Motor_Function.hpp"

#define OBSTACLE_THRESHOLD 80 //cm

static State currentState = STATE_FORWARD;
static int toggle_on = 0;

void Behavior_Init() {
    currentState = STATE_FORWARD;
}

void Behavior_Update() {

    if (SerialUSB.available() > 0) {
    String message = SerialUSB.readStringUntil('\n');
    message.trim();

        if(message == "1"){
            toggle_on = 1;
        } else if (message == "0") {
            toggle_on = 0;
        }
    }

    Ultrasonic_ReadAll();
    TrackingData antenna_data = Get_Antenna_Data();
    float left  = distances[LEFT_SENSOR];
    float front = distances[FRONT_SENSOR];
    float right = distances[RIGHT_SENSOR];

    switch(currentState) {

        //Forward/Follow State
        case STATE_FORWARD:
            
            if(toggle_on == 0) {
                currentState = WAIT_TOGGLE;

            }else if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            else if(left <= OBSTACLE_THRESHOLD && left >= 3) {
                currentState = STATE_AVOID_LEFT;
            }
            else if(right <= OBSTACLE_THRESHOLD && right >= 3) {
                currentState = STATE_AVOID_RIGHT;
            }
            else {
                currentState = STATE_FORWARD;
            }
            
            
            Serial.print("-------------");
            Serial.print("Distance: ");
            Serial.print(antenna_data.distance);
            Serial.print(" m ");
            Serial.print("\n");
            Serial.print("Direction: ");
            Serial.print(antenna_data.direction);
            Serial.println(" deg");

            Serial.print("\n");
            Serial.print("State Forward");
            Serial.print("\n");
            Serial.print("Left Array");
            Serial.print("\n");
            Serial.print(left);
            Serial.print("\n");
            Serial.print("Right Array");
            Serial.print("\n");
            Serial.print(right);
            Serial.print("\n");
            Serial.print("Center Array");
            Serial.print("\n");
            Serial.print(front);
            Serial.print("\n");
            
            Follow_Adjust(antenna_data.direction, antenna_data.distance);

            break;

        //AVOID STATE
        case STATE_AVOID_RIGHT:

            LeftTurn_90(100, 1000);
            if(toggle_on == 0) {
                currentState = WAIT_TOGGLE;

            }else if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            Go_Forward(130);
            RightTurn_90(100, 1000);
            if(toggle_on == 0) {
                currentState = WAIT_TOGGLE;

            }else if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            Go_Forward(130);
            LeftTurn_90(100, 500);
            if(toggle_on == 0) {
                currentState = WAIT_TOGGLE;

            }else if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            Go_Forward(130);
            delay(500);

            Serial.print("-------------");
            Serial.print("\n");
            Serial.print("State Avoid");
            Serial.print("\n");
            Serial.print("Left Array");
            Serial.print("\n");
            Serial.print(left);
            Serial.print("\n");
            Serial.print("Right Array");
            Serial.print("\n");
            Serial.print(right);
            Serial.print("\n");
            Serial.print("Center Array");
            Serial.print("\n");
            Serial.print(front);
            Serial.print("\n");

            currentState = STATE_FORWARD;

            break;

        //Avoid Left State    
        case STATE_AVOID_LEFT:

            RightTurn_90(100, 1000);
            if(toggle_on == 0) {
                currentState = WAIT_TOGGLE;

            }else if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            Go_Forward(130);

            LeftTurn_90(100, 1000);
            if(toggle_on == 0) {
                currentState = WAIT_TOGGLE;

            }else if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            Go_Forward(130);
            RightTurn_90(100, 500);

            Go_Forward(130);
            if(toggle_on == 0) {
                currentState = WAIT_TOGGLE;

            }else if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            delay(500);

            Serial.print("-------------");
            Serial.print("\n");
            Serial.print("State Avoid");
            Serial.print("\n");
            Serial.print("Left Array");
            Serial.print("\n");
            Serial.print(left);
            Serial.print("\n");
            Serial.print("Right Array");
            Serial.print("\n");
            Serial.print(right);
            Serial.print("\n");
            Serial.print("Center Array");
            Serial.print("\n");
            Serial.print(front);
            Serial.print("\n");

            currentState = STATE_FORWARD;

            break;

        //Complete Stop
        case STATE_STOP:

            Stop_Motors();

            Serial.print("-------------");
            Serial.print("\n");
            Serial.print("State Stop");
            Serial.print("\n");
            Serial.print("Left Array");
            Serial.print("\n");
            Serial.print(left);
            Serial.print("\n");
            Serial.print("Right Array");
            Serial.print("\n");
            Serial.print(right);
            Serial.print("\n");
            Serial.print("Center Array");
            Serial.print("\n");
            Serial.print(front);
            Serial.print("\n");
                        
            Serial.print("-------------");
            Serial.print("Distance: ");
            Serial.print(antenna_data.distance);
            Serial.print(" m ");
            Serial.print("\n");
            Serial.print("Direction: ");
            Serial.print(antenna_data.direction);
            Serial.println(" deg");

            delay(1000);
            
            if((front <= 40 && front >= 3) || antenna_data.distance < 1) {
                currentState = STATE_STOP;
            }
            else if(left <= OBSTACLE_THRESHOLD && left >= 3) {
                currentState = STATE_AVOID_LEFT;
            }
            else if(right <= OBSTACLE_THRESHOLD && right >= 3) {
                currentState = STATE_AVOID_RIGHT;
            }
            else {
                currentState = STATE_FORWARD;
            }

            break;

        case WAIT_TOGGLE:

            if(toggle_on == 1) {
                currentState = STATE_FORWARD;
            }            

            break;
    }
}
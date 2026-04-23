#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

// States
enum State {
    STATE_FORWARD,
    STATE_AVOID_LEFT,
    STATE_AVOID_RIGHT,
    STATE_STOP,
    WAIT_TOGGLE
};

// Functions
void Behavior_Init();
void Behavior_Update();

#endif
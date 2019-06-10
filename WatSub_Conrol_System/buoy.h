/*
  Buoy.h
*/

#ifndef Buoy_h
#define Buoy_h
#include <Servo.h>

#define RELEASE_BUFFER 900

class Buoy
{
  public:
    Buoy(int deadMans, int magnetpin, int servo);
    void deploy();
    void retract();
    void initialize(int servoPin);
    //releases buoy if too long since pin has been pressed
    bool check_dead_mans_switch();
  private:
    int deadMansPin, releasePin, servoPin;
    int releaseTime;
    bool buoyReleased;
    Servo buoyServo;
};

#endif

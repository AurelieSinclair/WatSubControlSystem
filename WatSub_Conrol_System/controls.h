#ifndef CONTROLS_H
#define CONTROLS_H

#include "Arduino.h"
#include <Servo.h>

#define INSTANT_PITCH_AMOUNT 20
#define INSTANT_YAW_AMOUNT 20
#define PITCH_RATE 0.05
#define YAW_RATE 0.05
#define INVERT_PITCH 1 // set to -1 to invert pitch controls
#define INVERT_YAW 1 // set to -1 to invert yaw controls
#define PITCH_CENTER_POS 90
#define YAW_CENTER_POS 90

class Controls {
	private:
      Servo pitchServo;
      Servo yawServo;
      int pitch, currently_pitching, pitch_start_time;
      int yaw, currently_yawing, yaw_start_time;
      int left_button, right_button, up_button, down_button;
      
	public:

	 Controls(int left_pin, int right_pin, int up_pin, int down_pin);
   void initialize(int pitch_pin, int yaw_pin);
   void update();
   int get_pitch();
   int get_yaw();
};


#endif

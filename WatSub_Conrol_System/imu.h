#ifndef IMU_H
#define IMU_H
#define RX_SIZE 19
#include "Arduino.h"

class Imu {
	private:
    int yaw, pitch, roll;
    int counter;
    char rx[RX_SIZE];
    char data;
     
	public:
   Imu() {
    yaw = 0;
    pitch = 0;
    roll = 0;
    counter = 0;
   }
   void initialize();
   void update();
   int get_pitch();
   int get_yaw();
   int get_roll();
};


#endif

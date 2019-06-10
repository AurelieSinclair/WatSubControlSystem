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
    HardwareSerial &serial;
     
	public:
   Imu(HardwareSerial &stream);
   void update();
   int get_pitch();
   int get_yaw();
   int get_roll();
};


#endif

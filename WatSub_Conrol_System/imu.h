#ifndef IMU_H
#define IMU_H

#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h"

class Imu {
	private:
    uint16_t yaw = 0, pitch = 0, roll = 0;
    uint16_t i = 0;
    float offsetX = 0, offsetY = 0, offsetZ = 0, offsetW = 0;
    BNO080 myIMU;
    void offsetOrientation();
    
	public:
   void initialize();
   void Update();
   float get_pitch();
   float get_yaw();
   float get_roll();
};


#endif

#include "Imu.h"

void Imu::initialize() {
  Wire.begin(); // Initiate the Wire library
}

void Imu::Update(){
 
}

int Imu::get_pitch(){
  return pitch/100;
}
int Imu::get_yaw(){
  return yaw/100;
}
int Imu::get_roll(){
  return roll/100;
}
